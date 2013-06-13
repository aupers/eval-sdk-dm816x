/*
 * GStreamer
 *
 * Copyright (C) 2012 RidgeRun
 *
 * Author:
 *  Michael Gruner <michael.gruner@ridgerun.com>
 */

/**
 * SECTION:element-gstrtspsink
 *
 * This element provides a RidgeRun implementation of a rtsp sink.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch v4l2src ! video/x-raw-yuv, format=\(fourcc\)NV12, width=640, height=480\
 *  ! rtsp_sink text="Hello overlay!" text-offseth=40 text-offsetv=100\
 *  text-font-height=70  text-color=0x800040 ! TIDmaiVideoSink
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <gst/gst.h>
#include "gstrtspsink.h"

GST_DEBUG_CATEGORY_STATIC (gst_rtsp_sink_debug);
#define GST_CAT_DEFAULT gst_rtsp_sink_debug

enum
{
  PROP_0,
  PROP_MAPPING,
  PROP_SERVICE,
  PROP_PIPELINE
};

/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    /*TODO*/
    GST_STATIC_CAPS ("ANY")
    );

GST_BOILERPLATE(GstRtspSink, gst_rtsp_sink, GstBin, GST_TYPE_BIN);

/* Object declarations */
static void gst_rtsp_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_rtsp_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);
static GstFlowReturn gst_rtsp_sink_chain(GstPad * pad, GstBuffer * buf);
static GstStateChangeReturn gst_rtsp_sink_change_state(GstElement * element, 
    GstStateChange transition);
static gboolean gst_rtsp_sink_set_caps(GstPad *pad, GstCaps *caps);
static void gst_rtsp_sink_reset_all (GstRtspSink * sink);
static gboolean gst_rtsp_sink_start (GstRtspSink *sink);
static void gst_rtsp_sink_finalize (GObject *object);
static GstBuffer *
gst_rtsp_sink_clone_buffer (GstBuffer *buf);

/*RTSP specific */
static GstRTSPFilterResult 
filter_session_poll_callback (GstRTSPSessionPool *pool, GstRTSPSession *session, 
                              gpointer user_data);

/* GObject vmethod implementations */

static void
gst_rtsp_sink_base_init (gpointer gclass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (gclass);

  gst_element_class_set_details_simple (element_class,
      "RR Rtsp sink element",
      "Sink",
      "RR Rtsp sink element",
      "Michael Gruner <michael.gruner@ridgerun.com>");

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_factory));
}

static void
gst_rtsp_sink_class_init (GstRtspSinkClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;
  
  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_rtsp_sink_set_property;
  gobject_class->get_property = gst_rtsp_sink_get_property;

  gstelement_class->change_state = gst_rtsp_sink_change_state;

  g_object_class_install_property (gobject_class, PROP_MAPPING,
      g_param_spec_string ("mapping", "Mapping",
          "Where the stream is mapped to. Must start with a \"/\"", "/test",
          G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_SERVICE,
      g_param_spec_string ("service", "Port",
          "Service or port of the connection", "554",
          G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_PIPELINE,
      g_param_spec_string ("pipeline", "Pipe",
          "Pipeline to pass to gst_rtsp_server. It must end in\n"
	  "\t\t\ta proper payloader named pay0. If this property is not\n"
          "\t\t\tset then an automatic pipeline will tried to be generated.",
	  NULL,
          G_PARAM_READWRITE));

  gobject_class->finalize = gst_rtsp_sink_finalize;

  GST_DEBUG_CATEGORY_INIT (gst_rtsp_sink_debug, "rtspsink", 0,
      "RR Rtsp sink plugin");
}

/* initialize the new element
 * instantiate pads and add them to element
 * set pad calback functions
 * initialize instance structure
 */
static void
gst_rtsp_sink_init (GstRtspSink * sink, GstRtspSinkClass * gclass)
{
  sink->server = gst_rtsp_server_new ();

  /* Create a sink pad based on templates */
  sink->sinkpad =
    gst_pad_new_from_static_template(&sink_factory, "sink");

  /* Add a chain function to grab buffer and push it to rtsp server */
  gst_pad_set_chain_function(
    sink->sinkpad, GST_DEBUG_FUNCPTR(gst_rtsp_sink_chain));
  /* Need to get the caps to choose payloader if not entered by user. */
  gst_pad_set_setcaps_function(
    sink->sinkpad, GST_DEBUG_FUNCPTR(gst_rtsp_sink_set_caps));

  /* Install te pad */
  gst_element_add_pad(GST_ELEMENT(sink), sink->sinkpad);

  /* Default values */
  sink->mapping = g_malloc (6);
  sprintf (sink->mapping, "/test");
  sink->service = "554";
  /* Let set caps choose automatically the payloader
   * if the user doesnt specify a pipe
   */
  sink->pipeline = NULL;

  sink->new_stream = TRUE;
  sink->stream_time = 0;
  sink->attached = FALSE;
  return;
}

#define APPSRC "appsrc name=src ! "
static void
gst_rtsp_sink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{

  GstRtspSink *sink = GST_RTSP_SINK (object);
  switch (prop_id) {
    case PROP_SERVICE:
      sink->service = g_value_dup_string (value);
      break;
    case PROP_MAPPING:
      if (sink->mapping)
	g_free(sink->mapping);

      /* Add the / if it doesnt exist */
      if ('/' == g_value_get_string(value)[0]) {
	/* Grab a copy instead of the stack value to be consistent on the free phase*/
        sink->mapping = g_malloc (strlen(g_value_get_string(value)));
	strcpy(sink->mapping, g_value_dup_string (value));
      } else {
        sink->mapping = g_malloc (strlen(g_value_get_string(value))+1);
	sprintf (sink->mapping,"/%s",
	    g_value_get_string(value));
      }
      break;
    case PROP_PIPELINE: {
      if (sink->pipeline)
	g_free(sink->pipeline);

      /* Prepend the appsrc automatically so its invisible for users */
      sink->pipeline = g_malloc (strlen(g_value_get_string(value)) +
          strlen(APPSRC));
      sprintf (sink->pipeline, "%s%s",APPSRC,
          g_value_get_string(value));
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_rtsp_sink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstRtspSink *sink = GST_RTSP_SINK (object);
  switch (prop_id) {
    case PROP_SERVICE:
      g_value_set_string (value,sink->service);
      break;
    case PROP_MAPPING:
      g_value_set_string (value, sink->mapping);
      break;
    case PROP_PIPELINE:
      g_value_set_string (value, sink->pipeline);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}


#define PIPEPROLOG "appsrc name=src ! queue ! "
#define PIPEEPILOG " name=pay0"
static gboolean gst_rtsp_sink_set_caps(GstPad *pad, GstCaps *caps)
{
  GstRtspSink *sink = GST_RTSP_SINK(GST_PAD_PARENT(pad)); 
  /* If user specified a payloader then theres no need to do anything */
  if (sink->pipeline) {
    goto pipeline_configured;
  }

  /* Allocate mem for worst case scenario */
  sink->pipeline = g_malloc (strlen(PIPEPROLOG) +
      strlen(PIPEEPILOG) + 10);

  /* We assume the caps are already fixed, if not choose the first one */
  GstStructure *structure = gst_caps_get_structure (caps, 0);
  /* Grab the name the mimetype */
  const gchar *name = gst_structure_get_name (structure);

  if (!strcmp (name, "video/x-h264")) {
    sprintf(sink->pipeline, "%srtph264pay%s", PIPEPROLOG, PIPEEPILOG);
  } else if (!strcmp (name, "video/mpeg")) {
    sprintf(sink->pipeline, "%srtpmp4vpay%s", PIPEPROLOG, PIPEEPILOG);
  } else if (!strcmp (name, "image/jpeg")) {
    sprintf(sink->pipeline, "%srtpjpegpay%s", PIPEPROLOG, PIPEEPILOG);
  } else {
    GST_ERROR ("Unable to select payloader. Automatic detection "\
        "works for h264, mpeg4 and mjpeg. For additional formats "\
	"please enter it manually on the \"pipeline\" property");
    sink->pipeline = NULL;
    return FALSE;
  } 
 pipeline_configured:
  GST_INFO ("Pipeline being used: %s", sink->pipeline);

  return gst_rtsp_sink_start(sink);
}

static GstFlowReturn gst_rtsp_sink_chain(GstPad * pad, GstBuffer * buf)
{
  GstRtspSink *sink = GST_RTSP_SINK (GST_PAD_PARENT(pad)); 
  /* Grab the pointer to the appsrc */
  GstAppSrc *appsrc = sink->factory->appsrc;

  /* Push the buffer to the server */
  if (appsrc) {
    /* GstRTSPServer doest like incoming streams with 
     * advanced running time. Simply take the first buffer as
     * the new base time and manually fix timestamps
     */
    if (sink->new_stream) {
      GST_INFO("Starting new stream");
      sink->stream_time = GST_BUFFER_TIMESTAMP(buf);
      sink->new_stream = FALSE;
    }
    
    /* We cant overwrite current buffer's timestamp or we will corrupt
       other streams. We just create another buffer and assign data */
    GstBuffer *compensation_buffer = gst_rtsp_sink_clone_buffer (buf);
    GST_BUFFER_TIMESTAMP(compensation_buffer)-=sink->stream_time;

    /* In order to avoid dealing with special kind of memories frees
       that the original buffer might have, unref the buffer until the
       compensation buffer is being destroyed */

    if (GST_FLOW_OK != gst_app_src_push_buffer ((GstAppSrc *)appsrc, compensation_buffer)) {
      /* Probably client closed connection */
      GST_WARNING("Unable to push buffer, probably stream is closing.");
    }
  } else {
    if (!sink->new_stream) {
      GST_INFO("Stopping current stream");
      sink->stream_time = 0;
      sink->new_stream = TRUE;
    }
    gst_buffer_unref(buf);
  }
  return  GST_FLOW_OK;
}

static void
gst_rtsp_sink_free_clone (gpointer data)
{
  GstBuffer *original_buffer = GST_BUFFER (data);
  
  GST_DEBUG ("Freeing original buffer");
  gst_buffer_unref (original_buffer);
}

static GstBuffer *
gst_rtsp_sink_clone_buffer (GstBuffer *buf)
{
  GstBuffer *cloned_buffer = gst_buffer_new();

  /* Copy all the metadata */
  gst_buffer_copy_metadata (cloned_buffer, buf, GST_BUFFER_COPY_ALL);

  /* Assign the data */
  GST_BUFFER_DATA(cloned_buffer) = GST_BUFFER_DATA(buf);

  /* According to documentation size isn't assigned */
  GST_BUFFER_SIZE(cloned_buffer) = GST_BUFFER_SIZE(buf);

  /* We can't just free this memory, it might be a special kind of
     memory, let it be handled by the original buffer free
     function. To do this, we provide a custom free function in which
     the original buffer is unrefed. Malloc data is the argument
     passed to the free function
  */
  GST_BUFFER_FREE_FUNC(cloned_buffer) = gst_rtsp_sink_free_clone;
  GST_BUFFER_MALLOCDATA(cloned_buffer) = (guint8 *)buf;
  
  return cloned_buffer;
}

static void
gst_rtsp_sink_reset_all (GstRtspSink * sink)
{
  return;
}

static gboolean
gst_rtsp_sink_start (GstRtspSink *sink)
{
  if (sink->attached || !sink->pipeline) {
    GST_INFO ("Already attached or pipeline is not defined yet");
    return TRUE;
  }
  
  /* make a media factory for a test stream. The default media factory can use
   * gst-launch syntax to create pipelines.
   * any launch line works as long as it contains elements named pay%d. Each
   * element with pay%d names will be a stream */
  sink->factory = rr_rtsp_media_factory_new ();

  /* This is the same as set port. Defaults to 554 */
  gst_rtsp_server_set_service (sink->server,sink->service);
  
  
  /* get the mapping for this server, every server has a default mapper object
   * that be used to map uri mount points to media factories */
  GstRTSPMediaMapping *mapping = gst_rtsp_server_get_media_mapping (sink->server);
 
  /* If many clients connect, make them use our same pipeline instead of
   * creating a new one for each */
  gst_rtsp_media_factory_set_shared(GST_RTSP_MEDIA_FACTORY(sink->factory), 
      TRUE);
  gst_rtsp_media_factory_set_launch (GST_RTSP_MEDIA_FACTORY(sink->factory), 
      sink->pipeline);

  /* attach the test factory to the /test url */
  gst_rtsp_media_mapping_add_factory (mapping, sink->mapping,
      GST_RTSP_MEDIA_FACTORY(sink->factory));

  /* don't need the ref to the mapper anymore */
  g_object_unref (mapping);

  /* attach the server to the default maincontext */
  sink->source = gst_rtsp_server_attach (sink->server, NULL);
  if (sink->source == 0){
    GST_ERROR ("failed to attach the server");
    return FALSE;
  }

  GST_INFO ("Started service at port %s mapping %s", 
          sink->service, sink->mapping);
  sink->attached = TRUE;
  return TRUE;
}

static void
gst_rtsp_sink_stop (GstRtspSink *sink)
{
  GstRTSPSessionPool *session_pool = NULL;
  GstRTSPMediaMapping *mapping = NULL;

  if (!sink->attached) {
    GST_INFO ("Not attached");
    return;
  }

  /* Check for active sessions */
  session_pool = gst_rtsp_server_get_session_pool(sink->server);

  /* We get a list of the active sessions */
  gst_rtsp_session_pool_filter (session_pool, 
      filter_session_poll_callback, NULL);
  
  g_object_unref (session_pool);

  /* get the mapping for this server, every server has a default mapper object
   * that be used to map uri mount points to media factories */
  mapping = gst_rtsp_server_get_media_mapping (sink->server);

  /* remove the test factory to the /test url */
  gst_rtsp_media_mapping_remove_factory (mapping, sink->mapping);

  /* don't need the ref to the mapper anymore */
  g_object_unref (mapping);

  /* Remove the source from the main context to release the socket */
  g_source_remove (sink->source);
  sink->source = 0;
  
  GST_INFO ("Stopped service at port %s mapping %s", 
          sink->service, sink->mapping);
  sink->attached = FALSE;
}

GstStateChangeReturn gst_rtsp_sink_change_state (GstElement *element, GstStateChange transition)
{
  GstRtspSink *sink = GST_RTSP_SINK(element);
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;

  switch (transition) {
  case GST_STATE_CHANGE_READY_TO_PAUSED:
    gst_rtsp_sink_start (sink);
    break;
  default:
    break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  switch (transition) {
  case GST_STATE_CHANGE_PAUSED_TO_READY:
    gst_rtsp_sink_stop (sink);
    break;
  default:
    break;
  }
  return ret;
}

/* Object destructor
 */
static void
gst_rtsp_sink_finalize (GObject *object)
{
  GstRtspSink *sink = GST_RTSP_SINK(object);

  /* free up used heap */
  g_free (sink->mapping);
  g_free (sink->pipeline);

  gst_object_unref (sink->server);
  /* Chain up to the parent class */
  G_OBJECT_CLASS (parent_class)->finalize;
}

/*
 * filter_session_poll_callback
 * 
 * This is a callback function which always returns GST_RTSP_FILTER_REF
 * in order to add all the existent sessions to the GList
 * 
 * \param pool  The session poll.
 * \param session Each existent session.
 * \param user_data Any user data sent by the callback.
 */
GstRTSPFilterResult 
filter_session_poll_callback (GstRTSPSessionPool *pool, GstRTSPSession *session, 
                              gpointer user_data)
{
        return GST_RTSP_FILTER_REMOVE;
}

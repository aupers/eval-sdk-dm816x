/*
 * GStreamer
 *
 * Copyright (C) 2012 RidgeRun
 *
 * Author:
 *  Michael Gruner <michael.gruner@ridgerun.com>
 */


#ifndef __GST_RTSP_SINK_H__
#define __GST_RTSP_SINK_H__

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/rtsp-server/rtsp-server.h>
#include "rtspmediafactory.h"

G_BEGIN_DECLS
#define GST_TYPE_RTSP_SINK                                             \
  (gst_rtsp_sink_get_type())
#define GST_RTSP_SINK(obj)				                \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_RTSP_SINK,GstRtspSink))
#define GST_RTSP_SINK_CLASS(klass)                                     \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_RTSP_SINK,GstRtspSinkClass))
#define GST_IS_RTSP_SINK(obj)                                          \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_RTSP_SINK))
#define GST_IS_RTSP_SINK_CLASS(klass)                                  \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_RTSP_SINK))

typedef struct _GstRtspSink GstRtspSink;
typedef struct _GstRtspSinkClass GstRtspSinkClass;

struct _GstRtspSink
{
  /* Gstreamer infrastructure */
  GstBin parent;
  GstPad *sinkpad;

  /* Rtsp server interface */
  GstRTSPServer *server;
  RrRtspMediaFactory *factory;
  gboolean attached;
  guint source;

  /* Properties */
  gchar *service;
  gchar *mapping;
  gchar *pipeline;

  /* Internal usage */
  gboolean new_stream;
  GstClockTime stream_time;
  
};

struct _GstRtspSinkClass
{
  GstBinClass parent_class;
};


GType gst_rtsp_sink_get_type (void);

G_END_DECLS
#endif /* __GST_RTSP_SINK_H__ */

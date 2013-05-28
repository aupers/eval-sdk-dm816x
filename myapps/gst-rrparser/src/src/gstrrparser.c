/*
 * Ridgerun
 * 	2012 larce luis.arce@ridgerun.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gst/gst.h>
#include <string.h>

#include "gstrrparser.h"

GST_DEBUG_CATEGORY_STATIC (gst_rrparser_debug);
#define GST_CAT_DEFAULT gst_rrparser_debug
#define NAL_LENGTH 4

/* Filter signals and args */
enum
{
  PROP_0,
};

/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("video/x-h264, "
						"stream-format = (string) byte-stream,"
						"width = (int) [ 1, MAX ],"
						"height = (int) [ 1, MAX ],"
						"framerate=(fraction)[ 0, MAX ];"
	)
);

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("video/x-h264, "
						"stream-format = (string) avc,"
						"width = (int) [ 1, MAX ],"
						"height = (int) [ 1, MAX ],"
						"framerate=(fraction)[ 0, MAX ];"
	)
    );

GST_BOILERPLATE (GstRRParser, gst_rrparser, GstElement,
    GST_TYPE_ELEMENT);

static void gst_rrparser_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_rrparser_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static gboolean gst_rrparser_set_caps (GstPad * pad, GstCaps * caps);
static GstFlowReturn gst_rrparser_chain (GstPad * pad, GstBuffer * buf);


static void
gst_rrparser_base_init (gpointer gclass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (gclass);

  gst_element_class_set_details_simple(element_class,
    "rr_h264parser",
    "Plugin that improve the parser process",
    "Plugin that improve the parser process",
    "Luis Fernando Arce; RidgeRun Engineering");

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_factory));
}

static void
gst_rrparser_class_init (GstRRParserClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_rrparser_set_property;
  gobject_class->get_property = gst_rrparser_get_property;

  /*g_object_class_install_property (gobject_class, PROP_SILENT,
      g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE));*/
}

static void
gst_rrparser_init (GstRRParser * rrparser,
    GstRRParserClass * gclass)
{
  
  rrparser->set_codec_data = FALSE;	
		
  rrparser->sinkpad = gst_pad_new_from_static_template (&sink_factory, "sink");
  gst_pad_set_setcaps_function (rrparser->sinkpad,
                                GST_DEBUG_FUNCPTR(gst_rrparser_set_caps));
  gst_pad_set_getcaps_function (rrparser->sinkpad,
                                GST_DEBUG_FUNCPTR(gst_pad_proxy_getcaps));
  gst_pad_set_chain_function   (rrparser->sinkpad,
                              GST_DEBUG_FUNCPTR(gst_rrparser_chain));

  rrparser->srcpad = gst_pad_new_from_static_template (&src_factory, "src");
  gst_pad_set_getcaps_function (rrparser->srcpad,
                                GST_DEBUG_FUNCPTR(gst_pad_proxy_getcaps));

  gst_element_add_pad (GST_ELEMENT (rrparser), rrparser->sinkpad);
  gst_element_add_pad (GST_ELEMENT (rrparser), rrparser->srcpad);

}

static void
gst_rrparser_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  switch (prop_id) {
    default:
      break;
  }
}

static void
gst_rrparser_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  switch (prop_id) {
    default:
      break;
  }
}

GstCaps*
gst_rrparser_fixate_src_caps(GstRRParser *rrparser, GstCaps *filter_caps){
	
  GstCaps *caps, *othercaps;

  GstStructure *structure;
  GstStructure *filter_structure;
  const gchar *stream_format;
  
  int filter_width = 0;
  int filter_height = 0;
  int filter_framerateN = 0;
  int filter_framerateD = 0;
  
  GST_DEBUG_OBJECT (rrparser, "Enter fixate_src_caps");

  /* Obtain the intersec between the src_pad and this peer caps */
  othercaps = gst_pad_get_allowed_caps(rrparser->srcpad); 

  if (othercaps == NULL ||
      gst_caps_is_empty (othercaps) || gst_caps_is_any (othercaps)) {
    /* If we got nothing useful, user our template caps */
    caps =
        gst_caps_copy (gst_pad_get_pad_template_caps (rrparser->srcpad));
  } else {
    /* We got something useful */
    caps = othercaps;
  }
  
  /* Ensure that the caps are writable */
  caps = gst_caps_make_writable (caps);

  structure = gst_caps_get_structure (caps, 0);
  if (structure == NULL) {
    GST_ERROR_OBJECT (rrparser, "Failed to get src caps structure");
    return NULL;
  }
  
  /* Force to use avc and nal in case of null */
  stream_format = gst_structure_get_string (structure, "stream-format");
  if (stream_format == NULL) {
    stream_format = "avc";
    gst_structure_set (structure, "stream-format", G_TYPE_STRING, stream_format, (char *)NULL);
  }
  
  /* Get caps filter fields */
  filter_structure = gst_caps_get_structure (filter_caps, 0);
  gst_structure_get_fraction(filter_structure, "framerate", &filter_framerateN,
							&filter_framerateD);
  gst_structure_get_int(filter_structure, "height", &filter_height);
  gst_structure_get_int(filter_structure, "width", &filter_width);
  
  /* Set the width, height and framerate */
  gst_structure_set (structure, "width", G_TYPE_INT,
					 filter_width, (char *)NULL);
  gst_structure_set (structure, "height", G_TYPE_INT, 
					 filter_height, (char *)NULL);
  gst_structure_set (structure, "framerate", GST_TYPE_FRACTION, filter_framerateN,
					 filter_framerateD, (char *)NULL);
  
	
  GST_DEBUG_OBJECT (rrparser, "Leave fixate_src_caps");
  return caps;	
}

static gboolean
gst_rrparser_set_caps (GstPad * pad, GstCaps * caps)
{
  const gchar *mime;
  const gchar *stream_format;
  GstCaps *src_caps;
  GstStructure *structure = gst_caps_get_structure (caps, 0);
  GstRRParser *rrparser = (GstRRParser *)gst_pad_get_parent(pad);

  mime = gst_structure_get_name (structure);
  stream_format = gst_structure_get_string (structure, "stream-format");
  
  /* Check mime type */
  if ((mime != NULL) && (strcmp (mime, "video/x-h264") != 0)) {
	GST_WARNING ("Wrong mimetype %s provided, we only support %s",
			    mime, "video/x-h264");

	goto refuse_caps;
  }
  
  /* Check for the stream format */
  if((stream_format != NULL) && (strcmp (stream_format, "byte-stream") != 0)) {
	GST_WARNING ("Wrong stream-format %s provided, we only support %s",
			    stream_format, "byte-stream");
	
	goto refuse_caps;
  }
  
  /* Obtain a fixed src caps and set it for the src pad */
  src_caps = gst_rrparser_fixate_src_caps(rrparser, caps);
  if(NULL == src_caps) {
	GST_WARNING("Can't fixate src caps");
	goto refuse_caps;
  }
  
  if(!gst_pad_set_caps (rrparser->srcpad, src_caps)) {
	GST_WARNING("Can't setc src pad");
	goto refuse_caps;
  }		
  
  return TRUE;
  
    /* ERRORS */
refuse_caps:
{
  GST_ERROR ("refused caps %" GST_PTR_FORMAT, caps);
	
  return FALSE;
}
  
}


GstBuffer*
gst_rrparser_fetch_nal(GstBuffer *buffer, gint type)
{
    
	gint i;
    guchar *data = GST_BUFFER_DATA(buffer);
    GstBuffer *nal_buffer;
    gint nal_idx = 0;
    gint nal_len = 0;
    gint nal_type = 0;
    gint found = 0;
    gint done = 0;

    GST_DEBUG("Fetching NAL, type %d", type);
    for (i = 0; i < GST_BUFFER_SIZE(buffer) - 5; i++) {
        if (data[i] == 0 && data[i + 1] == 0 && data[i + 2] == 0
            && data[i + 3] == 1) {
            if (found == 1) {
                nal_len = i - nal_idx;
                done = 1;
                break;
            }

            nal_type = (data[i + 4]) & 0x1f;
            if (nal_type == type)
            {
                found = 1;
                nal_idx = i + 4;
                i += 4;
            }
        }
    }

    /* Check if the NAL stops at the end */
    if (found == 1 && done != 0 && i >= GST_BUFFER_SIZE(buffer) - 4) {
        nal_len = GST_BUFFER_SIZE(buffer) - nal_idx;
        done = 1;
    }

    if (done == 1) {
        GST_DEBUG("Found NAL, bytes [%d-%d] len [%d]", nal_idx, nal_idx + nal_len - 1, nal_len);
        nal_buffer = gst_buffer_new_and_alloc(nal_len);
        memcpy(GST_BUFFER_DATA(nal_buffer),&data[nal_idx],nal_len);
        return nal_buffer;
    } else {
        GST_DEBUG("Did not find NAL type %d", type);
        return NULL;
    }
}


GstBuffer*
gst_rrparser_generate_codec_data(GstBuffer *buffer) {
	
	GstBuffer *avcc = NULL;
    guchar *avcc_data = NULL;
    gint avcc_len = 7;  // Default 7 bytes w/o SPS, PPS data
    gint i;

    GstBuffer *sps = NULL;
    guchar *sps_data = NULL;
    gint num_sps=0;

    GstBuffer *pps = NULL;
    gint num_pps=0;

    guchar profile;
    guchar compatibly;
    guchar level;

    sps = gst_rrparser_fetch_nal(buffer, 7); // 7 = SPS
    if (sps){
        num_sps = 1;
        avcc_len += GST_BUFFER_SIZE(sps) + 2;
        sps_data = GST_BUFFER_DATA(sps);

        profile     = sps_data[1];
        compatibly  = sps_data[2];
        level       = sps_data[3];

        GST_DEBUG("SPS: profile=%d, compatibly=%d, level=%d",
                    profile, compatibly, level);
    } else {
        GST_WARNING("No SPS found");

        profile     = 66;   // Default Profile: Baseline
        compatibly  = 0;
        level       = 30;   // Default Level: 3.0
    }
    pps = gst_rrparser_fetch_nal(buffer, 8); // 8 = PPS
    if (pps){
        num_pps = 1;
        avcc_len += GST_BUFFER_SIZE(pps) + 2;
    }

    avcc = gst_buffer_new_and_alloc(avcc_len);
    avcc_data = GST_BUFFER_DATA(avcc);
    avcc_data[0] = 1;               // [0] 1 byte - version
    avcc_data[1] = profile;       // [1] 1 byte - h.264 stream profile
    avcc_data[2] = compatibly;    // [2] 1 byte - h.264 compatible profiles
    avcc_data[3] = level;         // [3] 1 byte - h.264 stream level
    avcc_data[4] = 0xfc | (NAL_LENGTH-1);  // [4] 6 bits - reserved all ONES = 0xfc
                                  // [4] 2 bits - NAL length ( 0 - 1 byte; 1 - 2 bytes; 3 - 4 bytes)
    avcc_data[5] = 0xe0 | num_sps;// [5] 3 bits - reserved all ONES = 0xe0
                                  // [5] 5 bits - number of SPS
    i = 6;
    if (num_sps > 0){
        avcc_data[i++] = GST_BUFFER_SIZE(sps) >> 8;
        avcc_data[i++] = GST_BUFFER_SIZE(sps) & 0xff;
        memcpy(&avcc_data[i],GST_BUFFER_DATA(sps),GST_BUFFER_SIZE(sps));
        i += GST_BUFFER_SIZE(sps);
    }
    avcc_data[i++] = num_pps;      // [6] 1 byte  - number of PPS
    if (num_pps > 0){
        avcc_data[i++] = GST_BUFFER_SIZE(pps) >> 8;
        avcc_data[i++] = GST_BUFFER_SIZE(pps) & 0xff;
        memcpy(&avcc_data[i],GST_BUFFER_DATA(pps),GST_BUFFER_SIZE(pps));
        i += GST_BUFFER_SIZE(sps);
    }

    return avcc;
}

/* Function for convert the content of the buffer from bytestream to packetized convertion */
gboolean
gst_rrparser_set_codec_data(GstRRParser *rrparser, GstBuffer *buf){
  
  GstBuffer *codec_data;
  GstCaps *src_caps;
  
  /* Generate the codec data with the SPS and the PPS */
  codec_data = gst_rrparser_generate_codec_data(buf);
    
  /* Update the caps with the codec data */
  src_caps = GST_PAD_CAPS(rrparser->srcpad);
  gst_caps_set_simple (src_caps, "codec_data", GST_TYPE_BUFFER, codec_data, (char *)NULL);
  if (!gst_pad_set_caps (rrparser->srcpad, src_caps)) {
	  GST_WARNING_OBJECT (rrparser, "Src caps can't be update");
  }
	
  gst_buffer_unref (codec_data);
  
  return TRUE;
}

/* Function that change the content of the buffer to packetizer */
GstBuffer*
gst_rrparser_to_packetized(GstBuffer *out_buffer) {
  
	gint i, mark = 0, nal_type = -1;
    gint size = GST_BUFFER_SIZE(out_buffer);
    guchar *dest;
	
	dest = GST_BUFFER_DATA(out_buffer);
	
	for (i = 0; i < size - 4; i++) {
        if (dest[i] == 0 && dest[i + 1] == 0 &&
            dest[i+2] == 0 && dest[i + 3] == 1) {
            /* Do not copy if current NAL is nothing (this is the first start code) */
            if (nal_type == -1) {
                nal_type = (dest[i + 4]) & 0x1f;
            } else if (nal_type == 7 || nal_type == 8) {
                /* Discard anything previous to the SPS and PPS */
                GST_BUFFER_DATA(out_buffer) = &dest[i];
                GST_BUFFER_SIZE(out_buffer) = size - i;
                
            } else {
                /* Replace the NAL start code with the length */
                gint length = i - mark ;
                gint k;
                for (k = 1 ; k <= 4; k++){
                    dest[mark - k] = length & 0xff;
                    length >>= 8;
                }

                nal_type = (dest[i + 4]) & 0x1f;
            }
            /* Mark where next NALU starts */
            mark = i + 4;

            nal_type = (dest[i + 4]) & 0x1f;
        }
    }
    if (i == (size - 4)){
        /* We reach the end of the buffer */
        if (nal_type != -1){
            /* Replace the NAL start code with the length */
            gint length = size - mark ;
            gint k;
            for (k = 1 ; k <= 4; k++){
                dest[mark - k] = length & 0xff;
                length >>= 8;
            }
        }
    }
		
    return out_buffer;
}

static GstFlowReturn
gst_rrparser_chain (GstPad *pad, GstBuffer *buf)
{
  GstRRParser *rrparser = GST_RRPARSER (GST_OBJECT_PARENT (pad));
  
  /* Obtain and set codec data */
  if(!rrparser->set_codec_data) {
	if(!gst_rrparser_set_codec_data(rrparser, buf)) {
		GST_WARNING("Problems for generate codec data");
	}  
	rrparser->set_codec_data = TRUE;
  }

  /* Change the buffer content to packetizer */
  gst_rrparser_to_packetized(buf);
  
  return gst_pad_push (rrparser->srcpad, buf);
}


static gboolean
rrparser_init (GstPlugin * rrparser)
{
  /* debug category for fltering log messages
   */
  GST_DEBUG_CATEGORY_INIT (gst_rrparser_debug, "rr_h264parser",
      0, "Plugin that improve the parser process");

  return gst_element_register (rrparser, "rr_h264parser", GST_RANK_NONE,
      GST_TYPE_RRPARSER);
}

/* gstreamer looks for this structure to register myfilters
 *
 * exchange the string 'Template myfilter' with your myfilter description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "rr_h264parser",
    "Plugin that improve the parser process",
    rrparser_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)

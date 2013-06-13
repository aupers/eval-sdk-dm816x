#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gstrtspsink.h>

static gboolean
plugin_init (GstPlugin * plugin)
{
  gst_element_register (plugin, "rtspsink", GST_RANK_NONE,
      GST_TYPE_RTSP_SINK);

  return TRUE;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR, GST_VERSION_MINOR, "rtspsinkplugin",
    "RTSP sink plugin", plugin_init, VERSION,
    "Proprietary", "Ridgerun elements", "http://www.ridgerun.com"
)

#include <gst/rtsp-server/rtsp-media-factory.h>
#include <gst/app/gstappsrc.h>
#include <gst/rtsp-server/rtsp-media.h>
#include <gst/gst.h>

G_BEGIN_DECLS
#define TYPE_RR_RTSP_MEDIA_FACTORY (rr_rtsp_media_factory_get_type ())
#define RR_RTSP_MEDIA_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RR_RTSP_MEDIA_FACTORY, RrRtspMediaFactory))
#define RR_RTSP_MEDIA_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RR_RTSP_MEDIA_FACTORY, RrRtspMediaFactoryClass))
#define IS_RR_RTSP_MEDIA_FACTORY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RR_RTSP_MEDIA_FACTORY))
#define IS_RR_RTSP_MEDIA_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RR_RTSP_MEDIA_FACTORY))
#define RR_RTSP_MEDIA_FACTORY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RR_RTSP_MEDIA_FACTORY, RrRtspMediaFactoryClass))

typedef struct _RrRtspMediaFactory RrRtspMediaFactory;
typedef struct _RrRtspMediaFactoryClass RrRtspMediaFactoryClass;

struct _RrRtspMediaFactory {
  GstRTSPMediaFactory parent;
  GstAppSrc* appsrc;
};

struct _RrRtspMediaFactoryClass {
  GstRTSPMediaFactoryClass parent_class;
};

RrRtspMediaFactory* rr_rtsp_media_factory_new (void);

G_END_DECLS

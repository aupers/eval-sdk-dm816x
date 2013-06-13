/*
 * GStreamer
 *
 * Copyright (C) 2012 RidgeRun
 *
 * Author:
 *  Michael Gruner <michael.gruner@ridgerun.com>
 */

#include "rtspmediafactory.h"

/* This will create rr_rtsp_factory_get_type and 
 * set rr_rtsp_factory_parent_class */
G_DEFINE_TYPE (RrRtspMediaFactory, rr_rtsp_media_factory, GST_TYPE_RTSP_MEDIA_FACTORY);

/* VTable */
static GstElement* rr_rtsp_media_factory_create_pipeline (GstRTSPMediaFactory* base, 
    GstRTSPMedia* media);

static void rr_rtsp_media_factory_unprepared (GstRTSPMedia *media,
    gpointer data);

static void rr_rtsp_media_factory_prepared (GstRTSPMedia *media,
    gpointer data);

RrRtspMediaFactory* rr_rtsp_media_factory_new (void) {
  return g_object_new (TYPE_RR_RTSP_MEDIA_FACTORY, NULL);
}

static void rr_rtsp_media_factory_class_init (RrRtspMediaFactoryClass * klass) {
  GstRTSPMediaFactoryClass *rtsp_class;
  rtsp_class = GST_RTSP_MEDIA_FACTORY_CLASS(klass);
  /* Override the function */
  rtsp_class->create_pipeline = 
    rr_rtsp_media_factory_create_pipeline;
}

/* Constructor */
static void rr_rtsp_media_factory_init (RrRtspMediaFactory * this) {
  this->appsrc = NULL;
}

/* Override function */
static GstElement* rr_rtsp_media_factory_create_pipeline (GstRTSPMediaFactory* base, 
    GstRTSPMedia* media) {
  
  RrRtspMediaFactory * this = (RrRtspMediaFactory*) base;  
  GstElement *pipeline = NULL;
  /* If the elements in the configured pipe are null then
     we cant do anything yet */
  if (media->element == NULL) {
    return pipeline;
  }
  /* Create the pipeline with the elements and grab the source */
  pipeline = gst_pipeline_new ("media-pipeline");
  gst_bin_add ((GstBin*)pipeline, media->element);
  /* If it already exist unref it*/
  if (this->appsrc) {
    gst_object_unref (this->appsrc);
    this->appsrc = NULL;
  }
  this->appsrc = (GstAppSrc *)gst_bin_get_by_name((GstBin *)pipeline,"src"); 

  /* We also need a reference to the media to 
     connect to the signals */
  /* Connect to the media signals */
  g_signal_connect(media, "unprepared", 
      G_CALLBACK(rr_rtsp_media_factory_unprepared), (gpointer)this);
  g_signal_connect(media, "prepared", 
      G_CALLBACK(rr_rtsp_media_factory_prepared), (gpointer)this);

  return pipeline;
}

/* Callbacks to rtsp media */

/* No more clients */
static void rr_rtsp_media_factory_unprepared (GstRTSPMedia *media,
    gpointer data)
{
  RrRtspMediaFactory *this = RR_RTSP_MEDIA_FACTORY(data);
  GST_INFO ("Connections closed");
  this->appsrc = NULL;
}

/* Prepared to stream */
static void rr_rtsp_media_factory_prepared (GstRTSPMedia *media,
    gpointer data)
{
  RrRtspMediaFactory *this = RR_RTSP_MEDIA_FACTORY(data);
  GST_INFO ("Prepared to stream");
}

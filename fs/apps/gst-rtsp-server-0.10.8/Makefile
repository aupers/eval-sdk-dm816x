#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://people.freedesktop.org/~wtay/
PKG_TARBALL=gst-rtsp-0.10.8.tar.bz2
PKG_SHA1SUM=b2dc8c4e8e2a669f2f7a5f1cd71fb11e18fff521

export LDFLAGS=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib

LIBRARIES= /usr/lib/libgstrtspserver-0.10.so.0.0.0
VALA_BINDINGS = /usr/share/vala/vapi/gst-rtsp-server-0.10.{deps,vapi}

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


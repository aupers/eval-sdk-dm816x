#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=git://people.freedesktop.org/~ensonic/gst-tracelib
PKG_REVISION=f7a1ef8a898650226b2a4ab971eec29f96ea29a0

include ../../../bsp/classes/rrsdk.class

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib 
AUTOTOOLS_PARAMS=  LDFLAGS="$(APPS_LDFLAGS)" CFLAGS="$(APPS_CFLAGS)" 

LIBRARIES= /usr/lib/gst-tracelib/libgsttracelib.so

include $(CLASSES)/autotools.class

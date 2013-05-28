#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://gstreamer.freedesktop.org/src/gst-plugins-bad/
PKG_TARBALL=gst-plugins-bad-0.10.23.tar.bz2
PKG_SHA1SUM=46208d7bcebaac31310e2a884cc840c51034781a

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -Wl,--no-undefined

# We disable SDL because if you have installed sdl-config on the host, it will mess up
AUTOTOOLS_PARAMS = --enable-experimental LDFLAGS="$(APPS_LDFLAGS)" \
   --disable-sdl --disable-colorspace --disable-fieldanalysis

LIBRARIES = /usr/lib/{libgstbasevideo-0.10.so.23.0.0,libgstphotography-0.10.so.23.0.0,libgstsignalprocessor-0.10.so.23.0.0}
LIBRARIES_OPTIONAL = /usr/lib/{libgstbasecamerabinsrc-0.10.so.23.0.0,libgstcodecparsers-0.10.so.23.0.0}

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/gstreamer-plugin.class

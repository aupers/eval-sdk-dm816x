#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/gstreamer-plugin.class


PKG_URL=http://gstreamer.freedesktop.org/src/gst-plugins-ugly/
PKG_TARBALL=gst-plugins-ugly-0.10.19.tar.bz2
PKG_SHA1SUM=a28e4e8962f1fe385a098b13249a2b817c44fe63

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -Wl,--no-undefined

AUTOTOOLS_PARAMS = --disable-rpath --disable-valgrind --disable-nls \
--disable-examples  --disable-gtk-doc --disable-a52dec --disable-amrnb --disable-dvdread \
--disable-lame --disable-mpeg2dec --disable-sidplay LDFLAGS="$(APPS_LDFLAGS)"



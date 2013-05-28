#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://gstreamer.freedesktop.org/src/gst-ffmpeg/
PKG_TARBALL=gst-ffmpeg-0.10.13.tar.bz2
PKG_SHA1SUM=8de5c848638c16c6c6c14ce3b22eecd61ddeed44

#space :=
#space +=
#APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib
AUTOTOOLS_PARAMS = --prefix=$(DEVDIR)/fs/fsdev/usr 
#LDFLAGS="$(APPS_LDFLAGS)"  --with-ffmpeg-extra-configure="$(subst $(space), --extra-cflags=,$(subst ",, $(CONFIG_TOOLCHAIN_ARCH_FLAGS)))"

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/gstreamer-plugin.class


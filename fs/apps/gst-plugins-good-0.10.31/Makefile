#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://gstreamer.freedesktop.org/src/gst-plugins-good/
PKG_TARBALL=gst-plugins-good-0.10.31.tar.bz2
PKG_SHA1SUM=b45fc01b133fc23617fa501dd9307a90f467b396

include ../../../bsp/classes/rrsdk.class

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -Wl,--no-undefined

AUTOTOOLS_PARAMS=--enable-soup=yes --disable-annodex --disable-gdk_pixbuf --disable-libpng --disable-shout2  --disable-x --disable-xvideo \
--without-x --disable-rpath --disable-valgrind --disable-nls --disable-schemas-install --disable-examples \
--disable-gconf --disable-aalib --disable-esd LDFLAGS="$(APPS_LDFLAGS)" CFLAGS="$(APPS_CFLAGS)"

APPS_CFLAGS+=-I$(DEVDIR)/kernel/$(KERNEL)/include/

ifeq ($(CONFIG_ARCH_DAVINCI_DM365),y)
    APPS_CFLAGS+=-DPlatform_dm365
endif

ifeq ($(CONFIG_ARCH_DAVINCI),y)
    APPS_CFLAGS+=-DDAVINCI_LSP_WORKAROUND
endif

ifeq ($(CONFIG_FS_APPS_GSTREAMER_PLUGINS_GOOD_V4L2),y)
    APPS_CFLAGS+=-I$(DEVDIR)/kernel/$(KERNEL)/include/
    AUTOTOOLS_PARAMS+=--enable-experimental --enable-gst_v4l2 
endif
ifeq ($(CONFIG_FS_APPS_GSTREAMER_PLUGINS_GOOD_FLAC),y)
    AUTOTOOLS_PARAMS+=--enable-flac
else
    AUTOTOOLS_PARAMS+=--disable-flac
endif

include $(CLASSES)/gstreamer-plugin.class


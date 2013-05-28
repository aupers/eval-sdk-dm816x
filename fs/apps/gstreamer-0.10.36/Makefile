#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://gstreamer.freedesktop.org/src/gstreamer/
PKG_TARBALL=gstreamer-0.10.36.tar.bz2
PKG_SHA1SUM=ff95b5316b920e7c2836588bba18fa61395fbd03

DESTDIR=$(FSDEVROOT)
APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -Wl,--no-undefined

AUTOTOOLS_PARAMS=--disable-nls --disable-valgrind \
--disable-rpath --disable-alloc-trace --disable-failing-tests \
--disable-examples --disable-tests ac_cv_func_register_printf_function=no \
--prefix=/usr LDFLAGS="$(APPS_LDFLAGS)"

ifeq ($(CONFIG_FS_APPS_GSTEAMER_DISABLE_DEBUG),y)
AUTOTOOLS_PARAMS+=--disable-debug --disable-trace --disable-gst-debug
endif

BINARIES= /usr/bin/{gst-feedback,gst-inspect,gst-launch,gst-typefind,gst-xmlinspect,gst-xmllaunch} \
	/usr/bin/{gst-feedback-0.10,gst-inspect-0.10,gst-launch-0.10,gst-typefind-0.10,gst-xmlinspect-0.10,gst-xmllaunch-0.10} \
	/usr/libexec/gstreamer-0.10/gst-plugin-scanner
LIBRARIES= /usr/lib/gstreamer-0.10/{libgstcoreelements.so,libgstcoreindexers.so} \
	/usr/lib/{libgstbase-0.10.so.0.30.0,libgstcheck-0.10.so.0.30.0,libgstcontroller-0.10.so.0.30.0} \
	/usr/lib/{libgstdataprotocol-0.10.so.0.30.0,libgstnet-0.10.so.0.30.0,libgstreamer-0.10.so.0.30.0}
CORRECT_LA=/usr/lib/{libgstreamer-0.10.la,libgstnet-0.10.la,libgstdataprotocol-0.10.la} \
	/usr/lib/{libgstcontroller-0.10.la,libgstcheck-0.10.la,libgstbase-0.10.la} \
	/usr/lib/gstreamer-0.10/{libgstcoreelements.la,libgstcoreindexers.la}
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/{gstreamer-0.10.pc,gstreamer-base-0.10.pc,gstreamer-check-0.10.pc}\
	/usr/lib/pkgconfig/{gstreamer-controller-0.10.pc,gstreamer-dataprotocol-0.10.pc,gstreamer-net-0.10.pc}

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


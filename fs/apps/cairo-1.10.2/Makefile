#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.cairographics.org/releases/
PKG_TARBALL=cairo-1.10.2.tar.gz
PKG_SHA1SUM=ccce5ae03f99c505db97c286a0c9a90a926d3c6e

AUTOTOOLS_PARAMS=ac_cv_lib_z_compress=yes ac_cv_header_zlib_h=yes \
--enable-xlib=no  --disable-some-floating-point

ifeq ($(CONFIG_FS_APPS_DIRECTFB),y)
AUTOTOOLS_PARAMS+=--enable-directfb=yes
endif

BINARIES= /usr/bin/cairo-trace
LIBRARIES= /usr/lib/cairo/libcairo-trace.so.0.0.0 \
	/usr/lib/{libcairo-script-interpreter.so.2.11000.2,libcairo.so.2.11000.2}
LIBRARIES_OPTIONAL= /usr/lib/libcairo-gobject.so.2.11000.2

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com).
##$L$

PKG_URL=http://curl.haxx.se/download/
PKG_TARBALL=curl-7.21.3.tar.gz
PKG_SHA1SUM=df896fcdf49266f06fe65b31b3f73f709a855e37

export LDFLAGS=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib
AUTOTOOLS_PARAMS=--with-random=/dev/urandom

LIBRARIES= /usr/lib/libcurl.so.4.2.0

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

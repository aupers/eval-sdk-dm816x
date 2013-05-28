#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://liboil.freedesktop.org/download/
PKG_TARBALL=liboil-0.3.17.tar.gz
PKG_SHA1SUM=f9d7103a3a4a4089f56197f81871ae9129d229ed

export LDFLAGS=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib

BINARIES= /usr/bin/oil-bugreport
LIBRARIES= /usr/lib/liboil-0.3.so.0.3.0
include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


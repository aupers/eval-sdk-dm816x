#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.ijg.org/files/
PKG_TARBALL=jpegsrc.v8c.tar.gz
PKG_SHA1SUM=f0a3b88ac4db19667798bee971537eeed552bce9

ifeq ($(MAKECMDGOALS),sim)
  JPEG_PREFIX:=$(SIMROOT)/usr
else
  JPEG_PREFIX:=$(FSDEVROOT)/usr
endif

AUTOTOOLS_PARAMS=--enable-shared --enable-static  

BINARIES= /usr/bin/{cjpeg,djpeg,jpegtran,rdjpgcom,rdjpgcom}
LIBRARIES= /usr/lib/libjpeg.so.8.3.0

sim: build install

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


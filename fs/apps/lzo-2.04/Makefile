#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.oberhumer.com/opensource/lzo/download/
PKG_TARBALL=lzo-2.04.tar.gz
PKG_SHA1SUM=f5bf5c7ae4116e60513e5788d156ef78946677e7

DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr CFLAGS=-I$(FSDEVROOT)/usr/include

CORRECT_LA=/usr/lib/liblzo2.la

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


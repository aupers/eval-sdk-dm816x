#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://sourceforge.net/projects/flac/files/flac-src/flac-1.2.1-src/
PKG_TARBALL=flac-1.2.1.tar.gz
PKG_SHA1SUM=bd54354900181b59db3089347cc84ad81e410b38

AUTOTOOLS_PARAMS=--disable-xmms-plugin --disable-ogg --disable-rpath

BINARIES = /usr/bin/{flac,metaflac}
LIBRARIES = /usr/lib/{libFLAC++.so.6.2.0,libFLAC.so.8.2.0}
include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


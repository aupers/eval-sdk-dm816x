#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://downloads.xiph.org/releases/theora/
PKG_TARBALL=libtheora-1.1.1.tar.bz2
PKG_SHA1SUM=8dcaa8e61cd86eb1244467c0b64b9ddac04ae262

AUTOTOOLS_PARAMS=ac_cv_path_SDL_CONFIG="no" --disable-asm --disable-float \
--disable-encode --disable-sdltest --disable-oggtest --disable-vorbistest

LIBRARIES= /usr/lib/{libtheora.so.0.3.10,libtheoradec.so.1.1.4,libtheoraenc.so.1.1.2}
include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


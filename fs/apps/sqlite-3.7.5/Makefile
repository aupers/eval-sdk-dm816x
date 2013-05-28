#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.sqlite.org/
PKG_TARBALL=sqlite-autoconf-3070500.tar.gz
PKG_SHA1SUM=4e1338497b8da50b84307191bb3418e9ec5715d7
AUTOTOOLS_PARAMS=--enable-threadsafe REAL_BUILD_CC=gcc LDFLAGS="-L$(FSDEVROOT)"

BINARIES=   /usr/bin/sqlite3 
LIBRARIES=  /usr/lib/libsqlite3.so.0.8.6 

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


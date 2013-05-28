#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com).
##$L$

PKG_URL=http://lttng.org/files/lttng/
PKG_TARBALL=ltt-control-0.89-05122011.tar.gz
PKG_SHA1SUM=7acdd86d081056b444a7a23e8b8d9b7eac78321c

BINARIES = /usr/bin/{ltt-armall,ltt-disarmall,lttctl,lttd}
LIBRARIES = /usr/lib/{liblttctl.so.0.0.0,liblttd.so.0.0.0}

DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


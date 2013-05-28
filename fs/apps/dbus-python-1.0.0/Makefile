#$L$
# Copyright (C) 2012-2013 Ridgerun (http://www.ridgerun.com). 
#$L$

PKG_URL=http://dbus.freedesktop.org/releases/dbus-python/
PKG_TARBALL=dbus-python-1.0.0.tar.gz
PKG_SHA1SUM=96e1abe10769931cd8c640e359e695c1a99286d8

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

DESTDIR=$(FSDEVROOT)

AUTOTOOLS_PARAMS= --build=$(HOST_ARCH) --enable-shared --prefix=/usr PYTHON_INCLUDES=-I$(FSDEVROOT)/usr/include/python${PYTHON_VERSION}

LIBRARIES=/usr/lib/python${PYTHON_VERSION}/site-packages/_dbus{_glib_bindings,_bindings}.so
LIBRARIES_OPTIONAL=$(shell find $(FSDEVROOT)/usr/lib/python${PYTHON_VERSION}/site-packages/dbus -type f -name '*.pyo' | sed 's!.*fsdev!!')

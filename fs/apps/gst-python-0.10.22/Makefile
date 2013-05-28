#$L$
# Copyright (C) 2012-2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://gstreamer.freedesktop.org/src/gst-python/
PKG_TARBALL=gst-python-0.10.22.tar.bz2
PKG_SHA1SUM=7012445d921ae1b325c162500750c9b0e777201f

include ../../../bsp/classes/rrsdk.class

DESTDIR=$(FSDEVROOT)

AUTOTOOLS_PARAMS=--build=$(HOST_ARCH) --enable-shared --enable-gcov --prefix=/usr PYGOBJECT_CFLAGS=-I$(FSDEVROOT)/usr/include/pygtk-2.0 PYTHON_INCLUDES=-I$(FSDEVROOT)/usr/include/python$(PYTHON_VERSION)

OTHERS=/usr/include/gstreamer-0.10/gst/{pygst.h,pygstexception.h,pygstminiobject.h,pygstvalue.h} /usr/lib/python${PYTHON_VERSION}/site-packages/pygst.pth 
LIBRARIES=/usr/lib/gstreamer-0.10/libgstpython.so /usr/lib/python${PYTHON_VERSION}/site-packages/{gst-0.10/gst/{audio,interfaces,pbutils,video,tag,_gst}.so,gstoption.so}
LIBRARIES_OPTIONAL=$(shell find $(FSDEVROOT)/usr/lib/python${PYTHON_VERSION}/site-packages -type f -name '*.pyo' -or -name pygst.py | sed 's!.*fsdev!!')

include $(CLASSES)/autotools.class


#$L$
# Copyright (C) 2012-2013 Ridgerun (http://www.ridgerun.com). 
#$L$

PKG_URL=http://ftp.gnome.org/pub/GNOME/sources/pygobject/2.28/
PKG_TARBALL=pygobject-2.28.6.tar.bz2
PKG_SHA1SUM=4eda7d2b97f495a2ad7d4cdc234d08ca5408d9d5

include ../../../bsp/classes/rrsdk.class

DESTDIR=$(FSDEVROOT)

build:: rrfetched rrpatched configuration autotools_build$(ARCH_SUFFIX) 

AUTOTOOLS_PARAMS=--disable-introspection --enable-shared --enable-thread --prefix=/usr \
		 PYTHON_INCLUDES=-I$(FSDEVROOT)/usr/include/python${PYTHON_VERSION} 
BINARIES=/usr/bin/pygobject-codegen-2.0
OTHERS=/usr/include/pygtk-2.0/{pyglib.h,pygobject.h} /usr/lib/python${PYTHON_VERSION}/site-packages/pygtk.pth
LIBRARIES=/usr/lib/libpyglib-2.0-python.{so,so.0,so.0.0.0} /usr/lib/python${PYTHON_VERSION}/site-packages/{glib/_glib.so,gobject/_gobject.so,gtk-2.0/gio/{_gio.so,unix.so}}
LIBRARIES_OPTIONAL=$(shell find $(FSDEVROOT)/usr/lib/python${PYTHON_VERSION}/site-packages -name *.pyo -type f | sed 's!.*fsdev!!')

AUTOTOOLS_AUTOGEN_GENERATION_RULE=rrreconf

$(AUTOTOOLS_AUTOGEN_GENERATION_RULE):
	@$(ECHO) "Forcing autogen.sh"
	$(V)chmod 544 src/autogen.sh
	$(V)touch $@

clean:: 
	$(V)rm -f autogen_patch $(AUTOTOOLS_AUTOGEN_GENERATION_RULE)


include $(CLASSES)/autotools.class


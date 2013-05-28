#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

include ../../../bsp/classes/rrsdk.defs
include $(CLASSES)/autotools.class

PKG_URL=http://ftp.gnu.org/pub/gnu/gettext/
PKG_TARBALL=gettext-0.18.1.1.tar.gz
PKG_SHA1SUM=5009deb02f67fc3c59c8ce6b82408d1d35d4e38f

AUTOTOOLS_PARAMS=--disable-openmp --disable-java --disable-native-java --without-emacs

ifneq ($(CONFIG_FS_APPS_GETTEXT_NLS),y)
    AUTOTOOLS_PARAMS=--disable-nls
endif

LIBRARIES_OPTIONAL= /usr/lib/libasprintf.so.0.0.0 \
	    /usr/lib/libintl.so.8.0.1

LIBRARIES=  /usr/lib/libgettextsrc-0.18.1.so \
	    /usr/lib/libgettextpo.so.0.5.1 \
	    /usr/lib/libgettextlib-0.18.1.so

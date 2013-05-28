#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://ftp.gnome.org/pub/gnome/sources/glib/2.35/
PKG_TARBALL=glib-2.35.7.tar.xz
PKG_SHA1SUM=8fb734e88d30fa50c73421be89fc90b2a99b38de
include ../../../bsp/classes/rrsdk.defs

# The gvariant on ARM has a bug with double floating values if the compiler has optimizations
CFLAGS:=$(patsubst -O%,,$(APPS_CFLAGS))

# Prevent autogen.sh from running configure script
export NOCONFIGURE=yes

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib

AUTOTOOLS_PARAMS= glib_cv_stack_grows=no --with-gio-module-dir=$(DEVDIR)/bsp/local/lib/gio/modules \
glib_cv_uscore=no ac_cv_func_posix_getpwuid_r=yes GLIB_GENMARSHAL=$(LOCALDIR)/bin/glib-genmarshal \
ac_cv_func_posix_getgrgid_r=yes --disable-rpath --enable-xattr \
--disable-fam --with-threads=posix CFLAGS="$(CFLAGS)" CPPFLAGS="$(CFLAGS)" LDFLAGS="$(APPS_LDFLAGS)"

BINARIES = /usr/bin/{gsettings,gdbus}
#gio-querymodules,glib-compile-schemas,glib-compile-resources,gsettings,gdbus,gresource}

LIBRARIES=  /usr/lib/libgio-2.0.so.0.3507.0 \
	/usr/lib/libglib-2.0.so.0.3507.0 \
	/usr/lib/libgmodule-2.0.so.0.3507.0 \
	/usr/lib/libgobject-2.0.so.0.3507.0 \
	/usr/lib/libgthread-2.0.so.0.3507.0

include $(CLASSES)/autotools.class


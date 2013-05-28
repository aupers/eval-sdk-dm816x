#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$


PKG_URL=http://dbus.freedesktop.org/releases/dbus-glib/
PKG_TARBALL=dbus-glib-0.92.tar.gz
PKG_SHA1SUM=69aa860251a2c916907ac7b34d5a40196cf073ff

LDFLAGS=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -L$(FSDEVROOT)/usr/lib
AUTOTOOLS_PARAMS=   ac_cv_func_posix_getpwnam_r=yes \
                    ac_cv_have_abstract_sockets=no \
                    --with-dbus-binding-tool=$(shell which dbus-binding-tool) \
                    LDFLAGS="$(LDFLAGS)"

# Fill the spaces with the software components you'll need on the FSROOT
LIBRARIES=  /usr/lib/libdbus-glib-1.so.2.1.0 

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

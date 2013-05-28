#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://download.gnome.org/sources/dconf/0.7/
PKG_TARBALL=dconf-0.7.5.tar.bz2
PKG_SHA1SUM=f40dec58d6ff3cbc8e753de48f2fe0f014a6196d

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib
AUTOTOOLS_PARAMS=--prefix=/usr --disable-editor LDFLAGS="$(APPS_LDFLAGS)"
DESTDIR=$(FSDEVROOT)

BINARIES= /usr/bin/dconf /usr/libexec/dconf-service
LIBRARIES= /usr/lib/{libdconf-dbus-1.so.0.0.0,libdconf.so.0.0.0,gio/modules/libdconfsettings.so}
OTHERS= /usr/share/dbus-1/{services/ca.desrt.dconf.service,system-services/ca.desrt.dconf.service}
CORRECT_PKGCONFIG= /usr/lib/pkgconfig/{dconf.pc,dconf-dbus-1.pc}

INIT_SCRIPT=dconf.init
INIT_SCRIPT_LEVEL=50

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

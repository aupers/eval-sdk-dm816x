#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://dbus.freedesktop.org/releases/dbus/
PKG_TARBALL=dbus-1.4.20.tar.gz
PKG_SHA1SUM=9761eca23c0e6ea4ad822d92748703f9a0f58858

DEFAULT_FILE=$(FSROOT)/etc/default/dbus
# Clone the code to avoid having a wrong dbus-arch-deps.h
AUTOTOOLS_CLONE_SOURCE=yes
DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--disable-doxygen-docs --disable-xml-docs --disable-tests \
		--with-x=no --disable-selinux ac_cv_have_abstract_sockets=yes \
		--prefix=/usr --sysconfdir=/etc --localstatedir=/var

ifeq ($(CONFIG_FS_APPS_DBUS_USE_LIBXML2),yes)
    AUTOTOOLS_PARAMS+=--with-xml=libxml
else
    AUTOCONF_FLAGS = --with-xml=expat
endif


CORRECT_PKGCONFIG_SED_EXPRESSION?=s?prefix=/usr?prefix=$(FSDEVROOT)/usr?g;\
	s?sysconfdir=/etc?sysconfdir=$(FSDEVROOT)/etc?g;\
	s?session_bus_services_dir=/usr?session_bus_services_dir=$(FSDEVROOT)/usr?g
CORRECT_LA=/usr/lib/libdbus-1.la
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/dbus-1.pc

INIT_SCRIPT=dbus.init
INIT_SCRIPT_DEPENDENCIES=mountall
INIT_SCRIPT_LEVEL=40

BINARIES=   /usr/bin/{dbus-daemon,dbus-cleanup-sockets,dbus-launch,dbus-monitor,dbus-send,dbus-uuidgen}
LIBRARIES= /usr/lib/libdbus-1.so.3.5.9
OTHERS= /usr/libexec/dbus-daemon-launch-helper\
	/etc/dbus-1/{session.conf,system.conf}
DIRECTORIES= /usr/share/dbus-1/{services,system-services}\
	    /etc/dbus-1/{session.d,system.d}\
	    /var/run/dbus

install::
	$(V) mkdir -p $(FSROOT)/etc/dbus-1
	$(V) install -t $(FSROOT)/etc/dbus-1 -m 644 system-local.conf

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


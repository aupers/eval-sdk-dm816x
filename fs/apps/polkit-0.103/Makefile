#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.freedesktop.org/software/polkit/releases/
PKG_TARBALL=polkit-0.103.tar.gz
PKG_SHA1SUM=024e213dde0b96e1fc94524e21e0706462a87892

DESTDIR=$(FSDEVROOT)

AUTOTOOLS_PARAMS= \
	--with-authfw=shadow \
	--with-os-type=unknown \
	--disable-man-pages \
	--disable-examples \
	--prefix=/usr \
	CFLAGS="$(APPS_CFLAGS)" \
	--sysconfdir=$(FSDEVROOT)/etc \
	--libexecdir=/usr/lib/polkit-1 \
	--disable-static

CORRECT_DBUS_SERVICE=/usr/share/dbus-1/system-services/org.freedesktop.PolicyKit1.service
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/{polkit-agent-1.pc,polkit-backend-1.pc,polkit-gobject-1.pc}
CORRECT_LA=/usr/lib/{libpolkit-agent-1.la,libpolkit-backend-1.la,libpolkit-gobject-1.la}

APPS_CFLAGS+=-I$(DEVDIR)/kernel/$(KERNEL)/include/

INIT_SCRIPT=polkit.init
INIT_SCRIPT_DEPENDENCIES=mountall

BINARIES=   /usr/lib/polkit-1/polkitd
LIBRARIES = /usr/lib/{libpolkit-gobject-1.so.0.0.0,libpolkit-agent-1.so.0.0.0,libpolkit-backend-1.so.0.0.0}

OTHERS=	/usr/share/dbus-1/system-services/org.freedesktop.PolicyKit1.service \
	/etc/dbus-1/system.d/org.freedesktop.PolicyKit1.conf \
	/usr/share/polkit-1/actions/org.freedesktop.policykit.policy

DIRECTORIES= /etc/polkit-1/{localauthority,localauthority.conf.d,nullbackend.conf.d} \
	/usr/var/lib/polkit-1/{localauthority,localauthority.conf.d,nullbackend.conf.d} \
	 /etc/polkit-1/localauthority/{10-vendor.d,20-org.d,30-site.d,50-local.d,90-mandatory.d}

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

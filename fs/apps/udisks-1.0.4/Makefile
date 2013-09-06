#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://hal.freedesktop.org/releases/
PKG_TARBALL=udisks-1.0.4.tar.gz
PKG_SHA1SUM=10d2acfd6e6ff4c8d9d962af1fb1856a885e3219

DESTDIR=$(FSDEVROOT)

AUTOTOOLS_PARAMS=\
	--disable-remote-access \
	--prefix=/usr \
	--disable-man-pages \
	--sysconfdir=$(FSDEVROOT)/etc 

#TODO check if necessary
CORRECT_DBUS_SERVICE=/usr/share/dbus-1/system-services/org.freedesktop.UDisks.service

INIT_SCRIPT=udisks.init
INIT_SCRIPT_DEPENDENCIES=mountall,udev,dbus,polkit
INIT_SCRIPT_LEVEL=99

BINARIES= /usr/bin/udisks \
	/usr/libexec/{udisks-daemon,udisks-helper-mkfs,udisks-helper-delete-partition,udisks-helper-create-partition} \
	/usr/libexec/{udisks-helper-modify-partition,udisks-helper-create-partition-table} \
	/usr/libexec/{udisks-helper-change-filesystem-label,udisks-helper-linux-md-remove-component} \
	/usr/libexec/{udisks-helper-fstab-mounter,udisks-helper-ata-smart-collect} \
	/usr/libexec/{udisks-helper-ata-smart-selftest,udisks-helper-drive-detach,udisks-helper-drive-poll} \
	/usr/libexec/{udisks-helper-linux-md-check,udisks-helper-drive-benchmark}
	
OTHERS= /etc/dbus-1/system.d/org.freedesktop.UDisks.conf \
	/usr/share/dbus-1/system-services/org.freedesktop.UDisks.service \
	/usr/share/polkit-1/actions/org.freedesktop.udisks.policy

DIRECTORIES= /usr/var/lib/udisks
	    
include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

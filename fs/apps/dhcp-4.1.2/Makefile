#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://ftp.isc.org/isc/dhcp/
PKG_TARBALL=dhcp-4.1.2-P1.tar.gz
PKG_SHA1SUM=d682f8d1d2905432550864c3cd79eeb29607d6b5

AUTOTOOLS_BUILD_DIR=src
AUTOTOOLS_PARAMS=--sysconfdir=$(FSDEVROOT)/etc ac_cv_file__dev_random=no

# So we can select based on the menu
include ../../../bsp/mach/Make.conf

BINARIES=/usr/bin/omshell
ifeq ($(CONFIG_FS_APPS_DHCP_SERVER),y)
BINARIES+=/usr/sbin/{dhcpd,dhcrelay}
OTHERS=/etc/dhcpd.conf
endif
ifeq ($(CONFIG_FS_APPS_DHCP_CLIENT),y)
BINARIES+=/usr/sbin/dhclient
endif

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

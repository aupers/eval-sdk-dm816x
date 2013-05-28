#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
#$L$

PKG_URL=http://matt.ucc.asn.au/dropbear/releases/
PKG_TARBALL=dropbear-0.53.tar.gz
PKG_SHA1SUM=e17b611d71d407a8e584aab584322c903ffe2847

include ../../../bsp/classes/rrsdk.class

PROGRAMS=dropbear dbclient dropbearkey dropbearconvert

ifeq ($(CONFIG_FS_APPS_DROPBEAR_DBCLIENT),y) 
BINARIES+=/usr/bin/dbclient
endif

ifeq ($(CONFIG_FS_APPS_DROPBEAR_SCP),y) 
BINARIES+=/usr/bin/scp
PROGRAMS+=scp
endif 

export PROGRAMS
export DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr 

INIT_SCRIPT=dropbear.init
INIT_SCRIPT_LEVEL=99

DIRECTORIES= /etc/dropbear
BINARIES+=/usr/sbin/dropbear /usr/bin/dropbearkey

include $(CLASSES)/autotools.class


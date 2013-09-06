#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://sources.redhat.com/pub/lvm2/releases
PKG_TARBALL=LVM2.2.02.79.tgz
PKG_SHA1SUM=7d5e1c5cb7e0c856d7802d141e26bcaa362464ce

AUTOTOOLS_PARAMS=\
	--enable-write_install \
	--enable-pkgconfig \
	--disable-readline \
	--disable-applib \
	ac_cv_func_malloc_0_nonnull=yes \
	ac_cv_func_realloc_0_nonnull=yes

export CC=$(TOOLCHAIN_ENVIRONMENT)

#TODO check destdir and binaries in sbin
DESTDIR=$(FSDEVROOT)

LIBRARIES=  /usr/lib/libdevmapper.so
BINARIES= /usr/sbin/{dmsetup,fsadm,lvm,lvmconf,lvmdump,vgimportclone,lvchange,lvconvert,lvcreate,lvdisplay,lvextend} \
	  /usr/sbin/{lvmchange,lvmdiskscan,lvmsadc,lvmsar,lvreduce,lvremove,lvrename,lvresize,lvs,lvscan,pvchange} \
	  /usr/sbin/{pvck,pvcreate,pvdisplay,pvmove,pvremove,pvresize,pvs,pvscan,vgcfgbackup,vgcfgrestore,vgchange} \
	  /usr/sbin/{vgck,vgconvert,vgcreate,vgdisplay,vgexport,vgextend,vgimport,vgmerge,vgmknodes,vgreduce,vgremove} \
	  /usr/sbin/{vgrename,vgs,vgscan,vgsplit}
EXTRA_FILES = /etc/lvm

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

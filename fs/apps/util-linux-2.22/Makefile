#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.kernel.org/pub/linux/utils/util-linux/v2.22
PKG_TARBALL=util-linux-2.22.tar.bz2
PKG_SHA1SUM=fdabf80d3104a0d61455d31d74f0de629fa926a6

LIBRARIES= usr/lib/{libblkid.so.1.1.0,libmount.so.1.1.0,libuuid.so.1.3.0}
AUTOTOOLS_PARAMS= \
	--disable-makeinstall-chown \
	--without-ncurses \
	--disable-agetty \
	--disable-cramfs \
	--disable-eject \
	--disable-fallocate \
	--disable-fsck \
	--disable-kill \
	--disable-login \
	--disable-losetup \
	--disable-mount \
	--disable-mountpoint \
	--disable-partx \
	--disable-pivot_root \
	--disable-rename \
	--disable-schedutils \
	--disable-su \
	--disable-sulogin \
	--disable-switch_root \
	--disable-unshare \
	--disable-wall

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


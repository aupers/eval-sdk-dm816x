#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.kernel.org/pub/linux/utils/kernel/hotplug/
PKG_TARBALL=udev-182.tar.xz
PKG_SHA1SUM=ad226ca222ada889621aae9bdb50fb6e90e77fd9

AUTOTOOLS_PARAMS=\
  --prefix=/ \
  --exec-prefix=/usr \
  --with-usb-ids-path=no \
  --with-pci-ids-path=no \
  --disable-gtk-doc-html \
  --disable-introspection \
  --disable-manpages \
  --disable-gudev \
  --disable-keymap \
  --disable-extras

DESTDIR=$(FSDEVROOT)

BINARIES = /usr/libexec/udev/udevd /usr/bin/udevadm
LIBRARIES = /usr/lib/libudev.so.0.13.1
EXTRA_FILES = /etc/udev

INIT_SCRIPT=udev.init
INIT_SCRIPT_DEPENDENCIES=mountall
NIT_SCRIPT_LEVEL=99

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$

PKG_URL=http://www.freedesktop.org/software/fontconfig/release/
PKG_TARBALL=fontconfig-2.8.0.tar.gz
PKG_SHA1SUM=570fb55eb14f2c92a7b470b941e9d35dbfafa716

include ../../../bsp/classes/rrsdk.class

DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr --disable-docs CC_FOR_BUILD=cc --with-arch=$(ARCH) \
--with-freetype-config=$(FSDEVROOT)/usr/bin/freetype-config CPPFLAGS=" " CFLAGS=" "\
--with-default-fonts=/usr/share/fonts --with-cache-dir=/usr/var/cache/fontconfig

CORRECT_LA= /usr/lib/libfontconfig.la
CORRECT_PKGCONFIG= /usr/lib/pkgconfig/fontconfig.pc

BINARIES= /usr/bin/{fc-cache,fc-cat,fc-list,fc-match,fc-query,fc-scan}
LIBRARIES= /usr/lib/libfontconfig.so.1.4.4
DIRECTORIES= var/cache/fontconfig
EXTRA_FILES = usr/etc/fonts

include $(CLASSES)/autotools.class


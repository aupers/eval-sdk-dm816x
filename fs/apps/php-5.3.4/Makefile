#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://museum.php.net/php5/
PKG_TARBALL=php-5.3.4.tar.bz2
PKG_SHA1SUM=0b33926e78e1683e3383b3b5c840ee60ba669b0b

export LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -L$(FSDEVROOT)/usr/lib -ldl
AUTOTOOLS_PARAMS=--without-iconv \
            --enable-discard-path \
            --enable-sockets \
            --enable-shared \
            --enable-memory-limit \
            --enable-wddx \
            --enable-embedded-mysqli \
            --enable-magic-quotes \
            --enable-fastcgi \
            --disable-phar \
            --without-pear \
            --sysconfdir=/etc \
            --with-config-file-path=/etc \
            --with-config-file-scan-dir=/etc/php.d \
	    --with-libxml-dir=$(FSDEVROOT)/usr \
            --prefix=/usr

AUTOTOOLS_CLONE_SOURCE=yes
export INSTALL_ROOT=$(FSDEVROOT)

BINARIES=/usr/bin/php /usr/bin/php-cgi

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://museum.php.net/php5/
PKG_TARBALL=php-5.3.4.tar.bz2
PKG_SHA1SUM=0b33926e78e1683e3383b3b5c840ee60ba669b0b

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
            --sysconfdir=/etc

AUTOTOOLS_CLONE_SOURCE=yes

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools_local.class

install::
	$(V) sed -i -e "s?extension_dir='$(LOCALDIR)\(.*\)?extension_dir='$(FSDEVROOT)/usr\1?" $(LOCALDIR)/bin/php-config
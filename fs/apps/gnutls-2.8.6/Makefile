#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.gnu.org/gnu/gnutls/
PKG_TARBALL=gnutls-2.8.6.tar.bz2
PKG_SHA1SUM=bff911d4fd7389aa6698a644b3748eb2d23715bc

DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr
export LDFLAGS=-L$(FSDEVROOT)/usr/lib
export LIBS=-lgpg-error -lgcrypt

CORRECT_PKGCONFIG=/usr/lib/pkgconfig/{gnutls.pc,gnutls-extra.pc}
CORRECT_LA=/usr/lib/{libgnutls-extra.la,libgnutls-openssl.la,libgnutls.la,libgnutlsxx.la}

BINARIES = /usr/bin/{certtool,gnutls-cli,gnutls-cli-debug,gnutls-serv,psktool,srptool}
LIBRARIES = /usr/lib/{libgnutls-extra.so.26.14.12,libgnutls-openssl.so.26.14.12}\
	    /usr/lib/{libgnutlsxx.so.26.14.12,libgnutls.so.26.14.12}

build: built autotools_build

built: rrfetched rrpatched configuration
	$(V) cp arm/lib/includes/gnutls/gnutls.h src/lib/includes/gnutls/gnutls.h

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


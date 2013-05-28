#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$

PKG_URL=http://sourceforge.net/projects/dejavu/files/dejavu/2.32/
PKG_TARBALL=dejavu-fonts-ttf-2.32.tar.bz2
PKG_SHA1SUM=30865ca2c5c0b983eff6fe32d75aacc32d08a5a2

DIRECTORIES=/usr/share/fonts/truetype/ttf-dejavu/

FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched

installed:
	$(V) install -m 755 src/ttf/* $(FSROOT)/usr/share/fonts/truetype/ttf-dejavu $(QOUT)

install: rrsdk_install installed

uninstall:
	$(V) rm -Rf $(FSROOT)/usr/share/fonts/truetype/ttf-dejavu/*

clean:
	$(V) rm -Rf installed built configured

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include ../../../bsp/classes/fetcher.defs

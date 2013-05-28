#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.gnu.org/gnu/mtools/
PKG_TARBALL=mtools-4.0.15.tar.gz
PKG_SHA1SUM=d714a6fd82c4f8195518926ef9ffe6b5c22332ee

APPS_LDFLAGS=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib
export LIBS=$(APPS_LIBS)
export LD_FLAGS=$(APPS_LDFLAGS)
export ac_cv_func_setpgrp_void=yes
export ac_cv_have_x=no

LINKS = /usr/bin/{mattrib,mcat,mcd,mclasserase,mcopy,mdel,mdeltree,mdir,mdu,mformat}\
	/usr/bin/{minfo,mlabel,mmd,mmount,mmove,mpartition,mrd,mren,mtype,mtoolstest}\
	/usr/bin/{mshowfat,mbadblocks,mzip}
BINARIES = /usr/bin/mtools

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


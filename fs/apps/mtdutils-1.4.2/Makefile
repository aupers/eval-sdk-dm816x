#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.infradead.org/pub/mtd-utils/
PKG_TARBALL=mtd-utils-1.4.2.tar.bz2
PKG_SHA1SUM=a15b8eb5d20ef27ce785cd83412f4bd6770d8a90

BINARIES= usr/sbin/{doc_loadbios,docfdisk,flash_erase,flash_eraseall,flash_info,flash_lock}\
	usr/sbin/{flash_otp_dump,flash_otp_info,flash_unlock,flashcp,ftl_check,ftl_format,ubiupdatevol}\
	usr/sbin/{jffs2dump,mkfs.jffs2,mkfs.ubifs,mtd_debug,mtdinfo,nanddump,nandtest,nandwrite}\
	usr/sbin/{nftl_format,nftldump,recv_image,rfddump,rfdformat,serve_image,sumtool,ubiattach}\
	usr/sbin/{ubicrc32,ubidetach,ubiformat,ubimkvol,ubinfo,ubinize,ubirename,ubirmvol,ubirsvol}

CCACHE_ENABLE=no

APPS_CFLAGS+=-I$(FSDEVROOT)/usr/include
FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched built

installed:
	$(MAKE) -C src DESTDIR=$(FSDEVROOT) install $(QOUT)

install: installed rrsdk_install

uninstall:
	$(MAKE) -C src DESTDIR=$(FSDEVROOT) uninstall $(QOUT)

clean:
	$(V) rm -Rf installed built

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs

built: 
	$(MAKE) -C src CC="$(CC)" WITHOUT_XATTR=1  CFLAGS="$(APPS_CFLAGS)" LDFLAGS+="$(APPS_LDFLAGS)" $(QOUT)



#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$

PKG_URL=http://dosfstools.sourcearchive.com/downloads/3.0.11-1/
PKG_TARBALL=dosfstools_3.0.11.orig.tar.gz
PKG_SHA1SUM=29dc6fc65619fc2f45849d249a6d9c6fa20937ec

BINARIES= /usr/local/sbin/{mkdosfs,dosfsck,dosfslabel}
LINKS=	/usr/local/sbin/{fsck.msdos,fsck.vfat,mkfs.msdos,mkfs.vfat}

CFLAGS += -D_FILE_OFFSET_BITS=64

FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched built

built: 
	$(MAKE) -C src $(TOOLCHAIN_ENVIRONMENT) $(QOUT)

installed:
	$(MAKE) -C src DESTDIR=$(FSDEVROOT) install $(QOUT)
install: installed rrsdk_install 

uninstall:

clean:
	$(V) if [ -d src ] ; then \
		 $(MAKE) -C src clean $(TOOLCHAIN_ENVIRONMENT) $(QOUT) ; \
	fi ; 
	$(V) rm -Rf installed built configured

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs

#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

# Note: The following package revision is not the official 1.5.0 release,
# but a later revision needed for fixup-space for mkfs.ubifs

PKG_URL=git://git.infradead.org/mtd-utils.git
PKG_REVISION=7df62e8e9bb1f77ca0890cc757bd20a6f33a7fbc

FETCHER_EXTRACT_DIRECTORY_NAME=src

build: rrfetched built

built: 
	$(V)$(MAKE) -C src CC=$(CC) PREFIX= WITHOUT_XATTR=1 $(QOUT)

installed:
	$(V)$(MAKE) -C src DESTDIR=$(LOCALDIR) PREFIX= install $(QOUT)

install: installed rrsdk_install

clean:
	$(V) rm -Rf installed built

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk_local.class
include $(CLASSES)/fetcher.defs

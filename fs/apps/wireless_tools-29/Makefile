#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.hpl.hp.com/personal/Jean_Tourrilhes/Linux/
PKG_TARBALL=wireless_tools.29.tar.gz
PKG_SHA1SUM=22040ac1497f4c5f8ddeca365591b01ae3475710

LIBRARIES= /lib/libiw.so.29
BINARIES= /sbin/{ifrename,iwconfig,iwevent,iwgetid,iwlist,iwpriv,iwspy}

FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched built

built: rrpatched

	$(V) $(MAKE) -C src $(TOOLCHAIN_ENVIRONMENT) $(QOUT)
	$(V) touch $@

installed:
	$(V) $(MAKE) -C src $(TOOLCHAIN_ENVIRONMENT) PREFIX=$(FSDEVROOT) install $(QOUT)
	$(V) touch $@

install: installed rrsdk_install

uninstall:
	$(V) $(MAKE) -C src $(TOOLCHAIN_ENVIRONMENT) PREFIX=$(FSDEVROOT) uninstall $(QOUT)


clean: unpatch
	$(V) rm -Rf installed built configured

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs

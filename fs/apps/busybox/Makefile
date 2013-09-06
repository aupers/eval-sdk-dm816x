#$L$
# Copyright (C) 2013 Ridgerun
##$L$

PKG_URL=http://busybox.net/downloads/
PKG_TARBALL=busybox-1.20.2.tar.bz2
PKG_SHA1SUM=dd2e3684b13c0071d480e97b569041e69538e798

include ../../../bsp/classes/rrsdk.class

.PHONY: build chkconfig preconfig buildfs install clean

# IPV6 support on busybox has optimization problems
# with some ARM compilers. Do not optimize here
CFLAGS:=$(patsubst -O%,,$(CFLAGS))
CPPFLAGS:=$(patsubst -O%,,$(CPPFLAGS))

#export EXTRA_CFLAGS=$(CFLAGS)
export CROSS_COMPILE := $(subst ",,$(TOOLCHAIN_PREFIX))-

build: src rrpatched
	$(V) # We backup the .config file to avoid rebuilding busybox
	$(V) # completely in case nothing has changed for it
	$(V) if [ -f src/.config ] ; then \
	 cd src ; \
	 sed "s/# ... ... .. ..:..:.. ....//" .config > .config.backup ; \
	 ln -sf $(DEVDIR)/bsp/mach/bspconfig .config ; \
	 $(MAKE) silentoldconfig $(QOUT) $(ERRQOUT) ; \
	 sed "s/# ... ... .. ..:..:.. ....//" .config > .config.new ; \
	 if ! diff -q .config.backup .config.new $(QOUT) ; then \
	   $(MAKE) -j $(BSP_NCPU) KBUILD_VERBOSE=$(VERBOSE) $(if $(VERBOSE:0=),V=1) $(QOUT) $(ERRQOUT) ; \
	 fi \
	else \
	 ln -sf $(DEVDIR)/bsp/mach/bspconfig src/.config ; \
	 $(MAKE) -j $(BSP_NCPU) -C src KBUILD_VERBOSE=$(VERBOSE) $(if $(VERBOSE:0=),V=1) $(QOUT) $(ERRQOUT) ; \
	fi ; \

src: rrfetched

preconfig: src src/libbb/Config.in

patched: src rrpatched

src/libbb/Config.in: rrpatched
	$(V)$(MAKE) -C src gen_build_files $(if $(VERBOSE:0=),V=1) $(QOUT) $(ERRQOUT)

install:
	$(V)$(MAKE) -C src install $(if $(VERBOSE:0=),V=1) $(QOUT)
ifneq ($(CONFIG_PREFIX),"../../../fs")
	$(V)cp -RPp src/$(CONFIG_PREFIX)/* $(FSROOT)
endif
#	if lsusb was selected, copy over the helper file
	$(V)if [ -r  $(FSDEVROOT)/usr/share/usb.ids ] ; then \
	    cp $(FSDEVROOT)/usr/share/usb.ids $(FSROOT)/usr/share/usb.ids ; \
	fi

clean:
	$(V)if [ -d src ] ; then $(MAKE) -C src distclean ; fi
	$(V)$(MAKE) unpatch

distclean: clean rrfetched_clean
	$(V) rm -rf src

FETCHER_EXTRACT_DIRECTORY_NAME=src
include $(CLASSES)/fetcher.defs

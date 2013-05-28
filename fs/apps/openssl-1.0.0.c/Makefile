#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.openssl.org/source/
PKG_TARBALL=openssl-1.0.0c.tar.gz
PKG_SHA1SUM=5a2d74fa7fe90c80915332404b9700044ef676a1

BINARIES=/usr/bin/openssl
LIBRARIES=/usr/lib/{libcrypto.so.1.0.0,libssl.so.1.0.0} \
          /usr/lib/engines/{libcswift.so,libatalla.so,libchil.so,libaep.so} \
          /usr/lib/engines/{libnuron.so,libubsec.so,libsureware.so,libgmp.so} \
          /usr/lib/engines/{libpadlock.so,libgost.so,libcapi.so,lib4758cca.so}
OTHERS=/usr/ssl/openssl.cnf
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/{libcrypto.pc,openssl.pc,libssl.pc}

# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class

FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched built

# On recent toolchains (codesourcery) we may came across problems if we don't use -fPIC to compile the shared libs
#CFLAGS+=-fpic
# If we have ocf-linux support, force support for cryptodev
ifeq ($(CONFIG_OCF_CRYPTODEV),y)
OTHER_OPTIONS=-DHAVE_CRYPTODEV
CFLAGS+=-I$(KERNELDIR)/crypto/
endif

CFLAGS+=-I$(FSDEVROOT)/usr/include

built: configured
	$(V) touch $(ARCH)/Makefile
	$(V) $(MAKE) -C $(ARCH) CC="$(CC)" AR="$(AR) r" LD=$(LD) INSTALLTOP=/usr OPENSSLDIR=/usr/ssl $(QOUT)
	$(V) touch $@

configured: patch
	$(V) cp -R src $(ARCH)
	$(V) cd $(ARCH) ; ./config shared zlib-dynamic no-asm --libdir=/lib --prefix=/usr $(OTHER_OPTIONS) $(CFLAGS) $(QOUT)
	$(V) touch $@

CORRECT_PKGCONFIG_SED_EXPRESSION?=s?prefix=/usr?prefix=$(FSDEVROOT)/usr?g
installed:
	$(V)$(MAKE) -C $(ARCH) install INSTALL_PREFIX=$(FSDEVROOT) $(QOUT)
	$(V) for pc_file in $(CORRECT_PKGCONFIG) ; do \
	    sed -i -e "$(CORRECT_PKGCONFIG_SED_EXPRESSION)" $(FSDEVROOT)/$$pc_file ; \
	done
	$(V) touch $@

install: installed rrsdk_install

uninstall:
	$(V)$(MAKE) -C $(ARCH) uninstall INSTALL_PREFIX=$(FSDEVROOT) $(QOUT)
	$(V) touch $@

clean: unpatch
	$(V) rm -Rf installed built configured $(ARCH)

distclean: clean rrfetched_clean

include $(CLASSES)/fetcher.defs

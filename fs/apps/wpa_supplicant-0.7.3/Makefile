#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://w1.fi/releases/
PKG_TARBALL=wpa_supplicant-0.7.3.tar.gz
PKG_SHA1SUM=ca51db8931fabf386352c87422f3e62fb44c3fe3

BINARIES= /usr/bin/{wpa_cli,wpa_passphrase,wpa_supplicant}
# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class

FETCHER_EXTRACT_DIRECTORY_NAME=src
build: rrfetched built

built: configured
	$(V) touch $(ARCH)/Makefile
	$(V) $(MAKE) -C $(ARCH)/wpa_supplicant CC="$(CC)"\
	 CPPFLAGS="-I$(FSDEVROOT)/usr/include" $(QOUT)
	$(V) touch $@

configured:
	$(V) cp -R src $(ARCH)
	$(V) cp config $(ARCH)/wpa_supplicant/.config
	$(V) echo "CFLAGS+=$(CFLAGS) -I$(FSDEVROOT)/usr/include" >> $(ARCH)/wpa_supplicant/.config
	$(V) echo "LDFLAGS+=-L$(FSDEVROOT)/usr/lib" >> $(ARCH)/wpa_supplicant/.config

installed:
	$(V)$(MAKE) -C $(ARCH)/wpa_supplicant install \
	    DESTDIR=$(FSDEVROOT) BINDIR=/usr/bin LIBDIR=/usr/lib $(QOUT)

install: installed rrsdk_install

uninstall:
	$(V)$(MAKE) -C $(ARCH)/wpa_supplicant uninstall \
	    DESTDIR=$(FSDEVROOT) BINDIR=/usr/bin LIBDIR=/usr/lib $(QOUT)

clean:
	$(V) rm -Rf installed built configured $(ARCH)

distclean: clean rrfetched_clean

include $(CLASSES)/fetcher.defs

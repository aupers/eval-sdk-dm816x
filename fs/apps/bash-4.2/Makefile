#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://ftp.gnu.org/gnu/bash/
PKG_TARBALL=bash-4.1.tar.gz
PKG_SHA1SUM=3bd1ec9c66f3689f6b3495bdaaf9077b2e5dc150

BINARIES= /usr/bin/{bash,bashbug}
FETCHER_EXTRACT_DIRECTORY_NAME=src

build: rrfetched built

built: configured
	$(V) $(MAKE) -C src $(TOOLCHAIN_ENVIRONMENT) CXX_FLAGS="--verbose" $(QOUT)

configured:
	$(V) cd src && \
	rm -rf config.cache && \
	export $(EXPORT_TOOLCHAIN_ENVIRONMENT) && \
	./configure --disable-nls \
	--host=$(ARCH)-linux --prefix=/usr 
	$(V) touch configured $(QOUT)

installed:
	$(V) $(MAKE) -C src install DESTDIR=$(FSDEVROOT) $(TOOLCHAIN_ENVIRONMENT) $(QOUT)
	$(V) touch $@

install: installed rrsdk_install

uninstall:
	$(V) $(MAKE) -C src uninstall DESTDIR=$(FSDEVROOT) $(TOOLCHAIN_ENVIRONMENT) $(QOUT)
	$(V) touch $@

clean:
	$(V) if [ -d src ] ; then \
		$(MAKE) -C src clean $(TOOLCHAIN_ENVIRONMENT) $(QOUT) ; \
	fi ; 
	$(V) rm -Rf installed built configured

distclean: clean rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs
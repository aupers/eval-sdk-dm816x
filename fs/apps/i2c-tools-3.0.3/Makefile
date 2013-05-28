#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://dl.lm-sensors.org/i2c-tools/releases/
PKG_TARBALL=i2c-tools-3.0.3.tar.bz2
PKG_SHA1SUM=8619c7d42d0ae3e7c4e368d911b59dd4fbe825f1

BINARIES = /usr/local/bin/{ddcmon,decode-dimms,decode-edid,decode-vaio}\
	    /usr/local/sbin/{i2c,i2c-stub-from-dump,i2cdetect,i2cdump,i2cget,i2cset}
APPS_CFLAGS+=-I$(KERNELDIR)/include -DI2C_FUNC_SMBUS_HWPEC_CALC=8
FETCHER_EXTRACT_DIRECTORY_NAME=src

build: rrfetched rrpatched built

src: rrfetched

built: 
	$(V) $(MAKE) -C src CC="$(CC)" CFLAGS="$(APPS_CFLAGS)" LDFLAGS="$(APPS_LDFLAGS)" \
	 INCLUDE_DIR="$(KERNEL_INCLUDE)" $(QOUT) $(ERRQOUT)

installed:
	$(V) $(MAKE) -C src INCLUDE_DIR="$(KERNELDIR)/include" DESTDIR=$(FSDEVROOT) \
	 install $(QOUT) $(ERRQOUT)

install: installed rrsdk_install

uninstall:
	$(MAKE) -C src DESTDIR=$(FSDEVROOT) uninstall $(QOUT)

clean:
	$(V) if [ -d src ] ; then \
		$(MAKE) -C src clean $(QOUT) ; \
	fi ; 
	$(V) rm -Rf installed built configured

distclean: clean unpatch rrfetched_clean

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs

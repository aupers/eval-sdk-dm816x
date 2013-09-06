#$L$
# Copyright (C) 2011,2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://sourceforge.net/projects/libpng/files/zlib/1.2.5/
PKG_TARBALL=zlib-1.2.5.tar.gz
PKG_SHA1SUM=8e8b93fa5eb80df1afe5422309dca42964562d7e

LIBRARIES=/usr/lib/libz.so.1.2.5

CFLAGS += -fPIC
# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/flags.defs

ifeq ($(MAKECMDGOALS),sim)
  ZLIB_PREFIX:=$(SIMROOT)/usr
else
  ZLIB_PREFIX:=$(FSDEVROOT)/usr
endif

FETCHER_EXTRACT_DIRECTORY_NAME=src
build$(ARCH_SUFFIX): rrfetched $(BUILT_FLAG)$(ARCH_SUFFIX)

sim: build$(ARCH_SUFFIX) install$(ARCH_SUFFIX)

$(BUILT_FLAG)$(ARCH_SUFFIX): configured$(ARCH_SUFFIX)
	$(V) $(MAKE) -C $(ARCH) $(QOUT)
	$(V) touch $(BUILT_FLAG)$(ARCH_SUFFIX)

configured$(ARCH_SUFFIX):
	$(V) $(RM) -rf $(ARCH) $(QOUT)
	$(V) cp -r src $(ARCH) $(QOUT)
	$(V) cd $(ARCH) && \
	$(RM) -rf config.cache && \
	export $(EXPORT_TOOLCHAIN_ENVIRONMENT) && \
	./configure \
	--shared \
	--prefix=$(ZLIB_PREFIX) 
	$(V) touch $@

$(INSTALLED_FLAG)$(ARCH_SUFFIX):
	$(V)$(MAKE) -C $(ARCH) install $(QOUT)
	$(V) touch $@ $(QOUT)

install$(ARCH_SUFFIX): $(INSTALLED_FLAG)$(ARCH_SUFFIX) rrsdk_install

uninstall$(ARCH_SUFFIX):
	$(V)$(MAKE) -C $(ARCH) uninstall $(QOUT)
	$(V) rm $(INSTALLED_FLAG)$(ARCH_SUFFIX)

clean$(ARCH_SUFFIX):
	$(V) rm -Rf $(INSTALLED_FLAG)* $(BUILT_FLAG)* configured* sim $(ARCH)

distclean: clean$(ARCH_SUFFIX) rrfetched_clean

include $(CLASSES)/fetcher.defs

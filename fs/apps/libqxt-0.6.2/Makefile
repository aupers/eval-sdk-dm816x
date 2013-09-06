#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

QXT_VERSION=0.6.2
PKG_URL=http://dev.libqxt.org/libqxt/get
PKG_TARBALL=v$(QXT_VERSION).tar.bz2
PKG_SHA1SUM=4cc514d725afe29bf4e1b165bbdf9a997703b46f

LIBRARIES= \
  /usr/lib/libQxtCore.so.$(QXT_VERSION) \
  /usr/lib/libQxtGui.so.$(QXT_VERSION) \
  /usr/lib/libQxtNetwork.so.$(QXT_VERSION) \
  /usr/lib/libQxtWeb.so.$(QXT_VERSION)

# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class

QXT_CONF_LOG=$(CURDIR)/$(ARCH)/configure.log
FETCHER_EXTRACT_DIRECTORY_NAME=src

build: rrfetched rrpatched built$(ARCH_SUFFIX)

sim: build install

built$(ARCH_SUFFIX): configured$(ARCH_SUFFIX)
	#$(V) $(MAKE) -C $(ARCH) -j $(BSP_NCPU) $(QOUT) $(ERRQOUT)
	$(V) $(MAKE) -C $(ARCH) $(QOUT) $(ERRQOUT)
	$(V) touch $@

CONFIG_OPTIONS= \
  -verbose \
  -qmake-bin $(DEVDIR)/fs/apps/qt-*/$(ARCH)/bin/qmake \
  -nomake designer \
  -nomake docs \
  -nomake berkley \
  -nomake sql \
  -nomake zeroconf \
  -l z

ifeq ($(MAKECMDGOALS),sim)
  CONFIG_OPTIONS+=-prefix $(SIMROOT)/usr
  CONFIG_OPTIONS+=-I $(SIMROOT)/usr/include -I $(SIMROOT)/include
  CONFIG_OPTIONS+=-L $(SIMROOT)/usr/lib -L $(SIMROOT)/lib
else
  CONFIG_OPTIONS+=-prefix $(FSDEVROOT)/usr
  CONFIG_OPTIONS+=-qws
endif

ifeq ($(CONFIG_FS_APPS_LIBQXT_DEBUG),y)
  CONFIG_OPTIONS+=-debug
else
  CONFIG_OPTIONS+=-release
endif

configured$(ARCH_SUFFIX): rrpatched
	$(V) [ -d $(ARCH) ] || mkdir $(ARCH)
	$(V) cd $(ARCH) && ../src/configure $(CONFIG_OPTIONS) &> $(QXT_CONF_LOG)
	$(V) touch $@

installed$(ARCH_SUFFIX):
	$(V) $(MAKE) -C $(ARCH) install $(QOUT) $(ERRQOUT)
	$(V) touch $@

install: installed$(ARCH_SUFFIX) rrsdk_install

clean: unpatch
	$(V) rm -Rf installed* built* configured* $(ARCH) $(QXT_CONF_LOG) sim

distclean: clean rrfetched_clean

include $(CLASSES)/fetcher.defs


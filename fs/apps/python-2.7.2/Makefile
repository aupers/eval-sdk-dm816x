#$L$
# Copyright (C) 2012-2013 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://www.python.org/ftp/python/2.7.2/
PKG_TARBALL=Python-2.7.2.tar.bz2
PKG_SHA1SUM=417bdeea77abfaf1b9257fc6b4a04aaa209f4547

RRSDK_PREPATCH_TARGETS=host-built

include ../../../bsp/classes/rrsdk.class

DESTDIR=$(FSDEVROOT)

HEADERS=$(shell find $(FSDEVROOT)/usr/include/python${PYTHON_VERSION}/* -printf "%f,"  | sed 's/.\{1\}$$//')

BINARIES=/usr/bin/python{,${PYTHON_VERSION}{,-config},-config}
LIBRARIES=/usr/lib/libpython${PYTHON_VERSION}.so{,.1.0}
OTHERS=/usr/include/python${PYTHON_VERSION}/{${HEADERS}}
LIBRARIES_OPTIONAL=$(shell find $(FSDEVROOT)/usr/lib/python${PYTHON_VERSION}/*  -type f -not -path '*/*test*/*' \
  -not -path '*/idlelib/*' -not -path '*/lib2to3/*' -not -path '*/lib-tk/*' -name '*.pyo' -or -name '*.so' -or ! -name '*.*' | sed 's!.*fsdev!!')

AUTOTOOLS_PARAMS=--build=$(HOST_ARCH) --prefix=/usr \
  --with-threads  \
  --with-pymalloc \
  --with-signal-module \
  --with-wctype-functions \
  --enable-unicode=ucs4 \
  --enable-shared

include $(CLASSES)/autotools.class

PYTHON_HOST_BIN=$(HOSTAPPSDIR)/python*/$(HOST_ARCH)/python
PYTHON_HOST_PGEN=$(HOSTAPPSDIR)/python*/$(HOST_ARCH)/Parser/pgen

clean::
	$(V) rm -f host-built

host-built:
	$(V) \
	if [ ! -e $(PYTHON_HOST_BIN) ] ; then \
	  $(ECHO) "$(ERROR_COLOR)Error:$(NORMAL_COLOR) Can't find $(PYTHON_HOST_BIN)" ; \
	  $(ECHO) "Please make sure that python for the host is built first.\n" ; \
	  exit -1 ; \
	fi ; \
	if [ ! -e $(PYTHON_HOST_PGEN) ] ; then \
	  $(ECHO) "$(ERROR_COLOR)Error:$(NORMAL_COLOR) Can't find $(PYTHON_HOST_PGEN)" ; \
	  $(ECHO) "Please make sure that python for the host is built first.\n" ; \
	  exit -1 ; \
	fi 
	$(V) touch $@

autotools_built$(ARCH_SUFFIX): 
	$(V) $(MAKE) -j $(BSP_NCPU) -C $(AUTOTOOLS_BUILD_DIR) \
	HOSTPYTHON=$(PYTHON_HOST_BIN) HOSTPGEN=$(PYTHON_HOST_PGEN) BLDSHARED="$(CC) -shared" \
	 CROSS_COMPILE=$(ARCH)- CROSS_COMPILE_TARGET=yes HOSTARCH=$(ARCH) \
	BUILDARCH=$(HOST_ARCH) $(if $(VERBOSE:1=),,V=1) $(QOUT) $(ERRQOUT)
	$(V) $(MAKE) install HOSTPYTHON=$(PYTHON_HOST_BIN) BLDSHARED="$(CC) -shared" \
	CROSS_COMPILE=$(ARCH)- CROSS_COMPILE_TARGET=yes 
	$(V) touch $@


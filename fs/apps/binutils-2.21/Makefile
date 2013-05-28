#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://ftp.gnu.org/gnu/binutils/
PKG_TARBALL=binutils-2.21.1a.tar.bz2
PKG_SHA1SUM=525255ca6874b872540c9967a1d26acfbc7c8230

AUTOTOOLS_PARAMS= --disable-nls --build=i686-linux

BINARIES=/usr/bin/addr2line /usr/bin/ar /usr/bin/as /usr/bin/c++filt \
	 /usr/bin/gprof /usr/bin/ld /usr/bin/nm /usr/bin/objcopy \
	 /usr/bin/objdump /usr/bin/ranlib /usr/bin/readelf \
	 /usr/bin/size /usr/bin/strings /usr/bin/strip

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

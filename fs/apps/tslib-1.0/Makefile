#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=https://github.com/kergoth/tslib.git
PKG_TYPE=git
PKG_REVISION=412d99d8b92c12545f939972146a38c5074f3dcb

# Since tslib uses modules, we cross-compile with prefix=/usr and setup the DESTDIR
DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr --sysconfdir=/etc ac_cv_func_malloc_0_nonnull=yes

CORRECT_LA=/usr/lib/libts.la
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/tslib-1.0.pc /usr/lib/pkgconfig/tslib.pc

BINARIES=   /usr/bin/ts_calibrate \
	    /usr/bin/ts_harvest \
	    /usr/bin/ts_print \
	    /usr/bin/ts_print_raw \
	    /usr/bin/ts_test
LIBRARIES=  /usr/lib/libts-1.0.so.0.0.0 \
	    /usr/lib/ts/arctic2.so \
	    /usr/lib/ts/collie.so \
	    /usr/lib/ts/corgi.so \
	    /usr/lib/ts/dejitter.so \
	    /usr/lib/ts/h3600.so \
	    /usr/lib/ts/input.so \
	    /usr/lib/ts/linear.so \
	    /usr/lib/ts/linear_h2200.so \
	    /usr/lib/ts/mk712.so \
	    /usr/lib/ts/pthres.so \
	    /usr/lib/ts/tatung.so \
	    /usr/lib/ts/ucb1x00.so \
	    /usr/lib/ts/variance.so

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


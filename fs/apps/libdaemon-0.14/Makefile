#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$
PKG_URL=http://0pointer.de/lennart/projects/libdaemon/
PKG_TARBALL=libdaemon-0.14.tar.gz
PKG_SHA1SUM=78a4db58cf3a7a8906c35592434e37680ca83b8f

AUTOTOOLS_PARAMS= ac_cv_func_getpgrp_void=no ac_cv_func_setpgrp_void=yes \
ac_cv_func_memcmp_working=yes rb_cv_binary_elf=no rb_cv_negative_time_t=no \
--disable-lynx

LIBRARIES= /usr/lib/libdaemon.so.0.5.0

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


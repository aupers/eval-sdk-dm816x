#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$

PKG_URL=git://github.com/RidgeRun/libOMX_Core-DM81xx.git
PKG_TYPE=git
PKG_REVISION=5_03_01_15

include ../../fs/Apps.defs

AUTOTOOLS_PARAMS=--with-ezsdkdir=$(subst ",,$(EZSDK))

LIBRARIES= /usr/lib/libOMX_Core.so
include ../../bsp/classes/rrsdk.class

ifeq ($(CONFIG_BSP_ARCH_DM8148),y)
AUTOTOOLS_PARAMS+=--with-platform=ti814x-evm
endif
ifeq ($(CONFIG_BSP_ARCH_DM8168),y)
AUTOTOOLS_PARAMS+=--with-platform=ti816x-evm
endif

include $(CLASSES)/autotools.class
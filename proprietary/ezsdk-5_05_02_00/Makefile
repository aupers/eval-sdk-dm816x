#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).
##$L$

-include patches/arch/Makefile
-include patches/mach/Makefile
include ../../bsp/classes/rrsdk.class

#Fetcher definition
PKG_TARBALL=$(EZSDK_NAME)-trimmed.tar.gz

#====================================================================================================
# DM8148 Platforms
#====================================================================================================
ifeq ($(CONFIG_PROPRIETARY_TI_CODECENGINE_DM8148),y)
EZSDK_PLATFORM=dm8148
EZSDK_NAME=ti-ezsdk_dm814x-evm_5_05_02_00
EZSDK_PATHINSDK=$(DEVDIR)/proprietary/ezsdk-5_02_02_60/
EZSDK_EXTRA_CMDLINE_ARGS=notifyk.vpssm3_sva=0xBF900000
export EZSDK_SYSLINK_PLATFORM=TI81XX
export EZSDK_SYSLINK_VARIANT=TI814X
export EZSDK_CONFIG=TI814x_config
export EZSDK_PLATFORM_LOWERCASE=ti814x
# This is the file we test to see if we have the right EZSDK
EZSDK_VERIFICATION_FILE=component-sources/omx_05_02_00_48

#Firmware to be loaded into the M3, this must be located in /lib/firmware/
#Needed by V4L2 capture driver
ifeq ($(CONFIG_PROPRIETARY_EZSDK_ENABLE_V4L2_CAPTURE),y)
VPSS_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm814x-firmware_05_02_00_48/dm814x_hdvpss_v4l2.xem3
else
VPSS_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm814x-firmware_05_02_00_48/dm814x_hdvpss.xem3
endif
HDVICP2_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm814x-firmware_05_02_00_48/dm814x_hdvicp.xem3
DSP_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm814x-firmware_05_02_00_48/dm814x_c6xdsp.xe674
endif

#====================================================================================================
# DM8168 Platforms
#====================================================================================================
ifeq ($(CONFIG_PROPRIETARY_TI_CODECENGINE_DM8168),y)
EZSDK_PLATFORM=dm8168
EZSDK_NAME=ti-ezsdk_dm816x-evm_5_05_02_00
EZSDK_PATHINSDK=$(DEVDIR)/proprietary/ezsdk-5_05_02_00/
EZSDK_EXTRA_CMDLINE_ARGS=notifyk.vpssm3_sva=0xBF900000
export EZSDK_SYSLINK_PLATFORM=TI81XX
export EZSDK_SYSLINK_VARIANT=TI816X
export EZSDK_CONFIG=TI816x_config
export EZSDK_PLATFORM_LOWERCASE=ti816x
# This is the file we test to see if we have the right EZSDK
EZSDK_VERIFICATION_FILE=component-sources/omx_05_02_00_48

#Firmware to be loaded into the M3, this must be located in /lib/firmware/
#Needed by V4L2 capture driver
ifeq ($(CONFIG_PROPRIETARY_EZSDK_ENABLE_V4L2_CAPTURE),y)
VPSS_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm816x-firmware_05_02_00_48/dm816x_hdvpss_v4l2.xem3
else
VPSS_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm816x-firmware_05_02_00_48/dm816x_hdvpss.xem3
endif
HDVICP2_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm816x-firmware_05_02_00_48/dm816x_hdvicp.xem3
DSP_FIRMWARE?=ezsdk/board-support/prebuilt-images/dm816x-firmware_05_02_00_48/dm816x_c6xdsp.xe674
endif

INIT_SCRIPT=coprocessors.init
INIT_SCRIPT_LEVEL=00

# We are an ezsdk 5
include $(CLASSES)/ezsdk5.class

cmdline: ezsdk_cmdline

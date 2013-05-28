#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
#$L$

#! \mainpage RidgeRun SDK API Documentation
#! \section introsec  Introduction
#! RidgeRun SDK provides a coherent and compresive enviroment for predictable configuration and build of
#! embedded Linux solutions.
#!
#! This documentation provides details regarding internal implementation of the SDK and the API to interact
#! with his components.
#!
#! For more information regarding specific functionality please check the modules tab and the specific area 
#! of interest.
#!
#!
#! You can find more information at http://developer.ridgerun.com
#!
#! Or contact RidgeRun for support at inquiries@ridgerun.com

#! \defgroup core SDK Core
#! \section Introduction
#! The core of the SDK consist of a several components:
#! - The build system: handles the cross-compilation logic
#! - The configuration system: handles configuration of the SDK
#! - The oscheck: handles depedency checking with build host machine
#! - The installer: handles transferring images build by the SDK to the target hardware

#! \defgroup config Configuration System
#! \ingroup core
#! \section Introduction
#! This SDK core component provides the logic neccesary for the configuration and general settings of the SDK.

#! \defgroup build Build System (cross compilation)
#! \ingroup core
#! \section Introduction
#! This SDK subsystem is responsible for and contains the logic required for handling the cross-compilation process that applications that will eventually be present in the target platform will use during installation, as well as other related tasks such as code fetching. 

#! \defgroup classes SDK Classes
#! \ingroup build
#! \section Introduction
#! Provides a collection of definition and class files that are used for automated and unificated procedures used during application installation and integration, in order to ease adaptation and porting of applications to the target platform within the SDK.

#! \defgroup oscheck System Checker (oscheck)
#! \ingroup core
#! \section Introduction
#! Contains a collection of files that determine system and package requirements for different Linux distributions required to make use of the RidgeRun SDK and its features. An automated script will try to detect the underlying Unix distribution and if possible its version, then check for packages in an automated way for this specific distribution.

#! \defgroup kernel Kernel
#! \section Introduction
#! Contains a verion of the Linux kernel tested to work well on the target processor.

#! \defgroup bootloader Bootloader
#! \section Introduction
#! Contains a verion of das u-boot bootloader tested to work well on the target processor.

#! \defgroup installer Installer

#! \defgroup installer Installer System
#! \ingroup core
#! \section Introduction
#! Contains perl scripts which interacts with u-boot or build an SD card image so that the images built by the SDK can be easily transferred to the target hardware.

#! \defgroup toolchain Toolchain
#! \section Introduction
#! Contains a version of the GNU toolchain tested to work well on the source code provided in the SDK.

.PHONY: all tools preconfig config menuconfig gconfig clean

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

all:
	@$(ECHO) "There is not default target for this BSP component"

preconfig:
	@rm -f ConfigExtra
	@if [ -d $(DEVDIR)/fs/rrapps ] ; then \
	    echo "source fs/rrapps/Config" >> ConfigExtra ; \
	fi
	@if [ -d $(DEVDIR)/proprietary ] ; then \
	    echo "source proprietary/Config" >> ConfigExtra ; \
	fi
	touch ConfigExtra
	@cp mach/bspconfig $(DEVDIR)

tools:
	$(MAKE) -C bspc

config: preconfig tools
	@cd $(DEVDIR); export srctree=$(BSPC_SRCTREE) ; bsp/bspc/conf bsp/Config
	@if [ -f $(DEVDIR)/bspconfig ] ; then \
	    mv $(DEVDIR)/bspconfig mach/; \
	    rm -rf $(DEVDIR)/bspconfig.old; \
	fi
	@cp $(DEVDIR)/bsp/mach/bspconfig $(BSPCONFIGFILE)

menuconfig: preconfig tools
	@cd $(DEVDIR); export srctree=$(BSPC_SRCTREE) ; bsp/bspc/mconf bsp/Config
	@if [ -f $(DEVDIR)/bspconfig ] ; then \
	    mv $(DEVDIR)/bspconfig mach/; \
	    rm -rf $(DEVDIR)/bspconfig.old; \
	fi
	@cp $(DEVDIR)/bsp/mach/bspconfig $(BSPCONFIGFILE)

gconfig: preconfig tools
	$(MAKE) -C bspc gconf
	@cd $(DEVDIR); export srctree=$(BSPC_SRCTREE) ; ./bsp/bspc/gconf bsp/Config
	@if [ -f $(DEVDIR)/bspconfig ] ; then \
	    mv $(DEVDIR)/bspconfig mach/; \
	    rm -rf $(DEVDIR)/bspconfig.old; \
	fi
	@cp $(DEVDIR)/bsp/mach/bspconfig $(BSPCONFIGFILE)

clean:
	$(V)$(MAKE) -C bspc clean
	$(V) rm -Rf local/*


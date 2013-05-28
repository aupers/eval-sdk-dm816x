#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
#$L$

.PHONY: build clean scripts relflags real_build

include ../../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs

include arch/Makefile.rules
include mach/Makefile.rules

MKIMAGE = ./src/tools/mkimage -A arm -O linux 
IMAGES = $(DEVDIR)/images/

BOOTLOADER_TARBALL?=$(BOOTLOADER).tar.bz2
PKG_TARBALL=$(BOOTLOADER_TARBALL)
FETCHER_EXTRACT_DIRECTORY_NAME=src
PKG_URL=$(BOOTLOADER_URL)

ifeq ($(CONFIG_BSP_ARCH_KERNEL_COMPRESS),y)
KERNEL_LOAD_ADDRESS=$(CONFIG_BSP_ARCH_SDRAM_BASE)
else
KERNEL_LOAD_ADDRESS=$(CONFIG_BSP_ARCH_KERNEL_LOAD_ADDRESS)
endif

ifeq ($(CONFIG_UBOOT_NAND_FLASH_MEMORY),y)
CPPFLAGS+= -DCONFIG_SYS_USE_NAND
endif

ifeq ($(CONFIG_UBOOT_NOR_FLASH_MEMORY),y)
CPPFLAGS+= -DCONFIG_SYS_USE_NOR -DCONFIG_SYS_FLASH_SECT_SZ=$(CONFIG_UBOOT_FLASH_BLK_SIZE) -DPHYS_FLASH_SIZE=$(CONFIG_UBOOT_FLASH_SIZE)
endif

build: $(BOOTLOADER) rrpatched arch_build mach_build relflags uboot_built copy_images arch_post_build mach_post_build scripts

relflags:
	$(V) echo $(CPPFLAGS) > relflags.tmp
	$(V) if [ -f relflags ] && ! diff relflags relflags.tmp >/dev/null ; then \
	    $(ECHO) "Rebuilding $(BOOTLOADER) since compile flags changed..." ; \
	    $(MAKE) real_build ; \
	else \
	    mv relflags.tmp relflags ; \
	fi

uboot_configured:
	$(V) $(MAKE) -C src $(UBOOT_BOARD_CONFIG) CROSS_COMPILE=$(TOOLCHAIN_PREFIX)- RELFLAGS="$(CFLAGS)"
	$(V) touch $@

#Some platforms like the DM8148 needs an extra parameter with the uboot name when uboot will be built,
#in this cases, the variable TI_NAME must be set properly in mach/Makefile.rules
real_build:
	$(V) $(MAKE) -C src -j $(BSP_NCPU) CROSS_COMPILE=$(TOOLCHAIN_PREFIX)- \
		CONFIG_SYS_TEXT_BASE=$(CONFIG_UBOOT_RAM_ADDRS) EXTRA_CPPFLAGS="$(CPPFLAGS)" $(TI_NAME) $(QOUT) $(ERRQOUT)

copy_images::
	$(V) if [ -e src/u-boot.img ] ; then \
	     cp src/u-boot.img $(BOOTLOADERIMAGE) ; \
	     cp src/u-boot*img $(IMAGES) ; \
	else \
	     cp src/u-boot.bin $(BOOTLOADERIMAGE) ; \
	fi
	$(V) cp src/u-boot*bin* $(IMAGES)

uboot_built: uboot_configured
	$(V) $(ECHO) "Building $(BOOTLOADER)..."
	$(V) $(MAKE) real_build
	$(V) touch $@

ifneq ($(BOOTLOADER_TARBALL),)
BOOTLOADER_URL?=https://$(DOWNLOAD_SERVER)/packages/
endif

ifneq ($(BOOTLOADER_URL),)
$(BOOTLOADER): rrfetched
else
$(BOOTLOADER):
	$(V)$(ECHO) "\n$${ERROR_COLOR}Error:$${NORMAL_COLOR} no BOOTLOADER_URL or BOOTLOADER_TARBALL defined, and bootloader code not found... aborting\n";
	$(V) exit -1;
endif

src: $(BOOTLOADER)

preconfig: Config

Config: Config.template
	$(V) cp $< $@
	$(V) echo "source bootloader/$(BOOTLOADER)/arch/Config" >> $@
	$(V) echo "source bootloader/$(BOOTLOADER)/mach/Config" >> $@

buildfs:

clean: arch_clean mach_clean unpatch
	$(V) if ! [ -f src/.svn ] ; then \
	    rm -Rf src rrfetched ; \
	else \
	    if [ -d src ] ; then \
		$(MAKE) -C src CROSS_COMPILE=$(TOOLCHAIN_PREFIX)- distclean ; \
	    fi ; \
	fi
	$(V) find . -name .depend | xargs rm -f {}
	$(V) rm -f *.o *.d uboot_configured \
	uboot_built relflags relflags.tmp .fsloadhex


#################################################################
#			Scripts Section				#
#################################################################

scripts:
ifeq ($(CONFIG_BSP_ARCH_KERNEL_COMPRESS),y)
	@$(ECHO) Building bootloader compressed uImage
	@# Build the kernel image
	$(V)$(MKIMAGE) -T kernel -C none -a $(CONFIG_BSP_ARCH_KERNEL_ZTEXTADDR) \
	-e $(CONFIG_BSP_ARCH_KERNEL_ZTEXTADDR) \
	-n "\"RR Compressed Linux Kernel\"" -d $(KERNELIMAGE) $(KERNELIMAGE).uImage > /dev/null
else
	@$(ECHO) Building bootloader uncompressed uImage
	@# Build the kernel image
	$(V)$(MKIMAGE) -T kernel -C none -a $(CONFIG_BSP_ARCH_KERNEL_LOAD_ADDRESS) \
	-e $(CONFIG_BSP_ARCH_KERNEL_ENTRY_ADDRESS) \
	-n "\"RR Linux Kernel\"" -d $(KERNELIMAGE) $(KERNELIMAGE).uImage > /dev/null
endif
	@# Load the file system image after the kernel image (dirty calcs)
	$(V)declare -i KEND=0x`tail -1 $(DEVDIR)/kernel/$(KERNEL)/System.map | cut -f1 -d\ ` ; \
	KEND=$$KEND/4096 ; \
	KEND=$$KEND+4 ; \
	KEND=$$KEND*4096 ; \
	declare -i FSLOAD=$$KEND-1073741824 ; # convert from 0xC.. to 0x8... \
	FSLOADHEX=`echo $$FSLOAD 16o p | dc` ; \
	echo $$FSLOADHEX >.fsloadhex 
ifeq ($(CONFIG_FS_TARGET_INITRD),y)
	$(V)$(MKIMAGE) -T ramdisk -C none -a `cat .fsloadhex` \
	-n "\"RR File System Image\"" -d $(IMAGES)fsimage $(FSIMAGE).uImage $(QOUT) ;
else
ifneq ($(CONFIG_FS_TARGET_NFSROOT),y)
	@# Other file systems that are not NFS or initrd live directly on flash
	@# so we don't build a uImage for them, only load the raw file
ifneq ($(CONFIG_FS_TARGET_SD),y)
	$(V)if [ -e $(IMAGES)fsimage ] ; then \
	    cp $(IMAGES)fsimage $(FSIMAGE).uImage $(QOUT) ; \
	fi

else
	@# Empty fs image file for SD FS
	$(V)rm -f $(FSIMAGE).uImage $(QOUT)
	$(V)touch $(FSIMAGE).uImage $(QOUT)
endif
else
	@# Empty fs image file for NFS
	$(V)rm -f $(FSIMAGE).uImage $(QOUT)
	$(V)touch $(FSIMAGE).uImage $(QOUT)
endif
endif

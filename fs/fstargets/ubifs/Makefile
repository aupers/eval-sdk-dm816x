#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
#$L$


.PHONY: build cmdline

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

ifeq ($(MAKECMDGOALS),build)
 ifeq ($(PAGESIZE),)
  $(error ====== PAGESIZE is not defined, are you invoking from the installer? =====)
 endif
 ifeq ($(BLOCKSIZE),)
  $(error ====== BLOCKSIZE is not defined, are you invoking from the installer? =====)
 endif
endif

ifeq ($(CONFIG_FS_TARGET_UBIFS_SUBPAGESIZE),)
  SUBPAGESIZE=$(PAGESIZE)
else
  SUBPAGESIZE=$(CONFIG_FS_TARGET_UBIFS_SUBPAGESIZE)
endif

build: ubi.cfg
	$(V) ubinize $(if $(VERBOSE:1=),,-v) -o $(FSIMAGE) \
	  -p $(BLOCKSIZE) -m $(PAGESIZE) -s $(SUBPAGESIZE) -O $(SUBPAGESIZE) \
	  ubi.cfg
	$(V) rm ubifs.img ubi.cfg

.PHONY: ubifs.img

# LEB size is calculated based on the support for subpages, we need to reserve two
# pages/subpages per PEB to store the EC and VID headers
# For more information see (includes information on LEB calculation): 
# http://www.linux-mtd.infradead.org/faq/ubi.html#L_find_min_io_size
ubifs.img:
	$(V) if [ $$(( $(SUBPAGESIZE) * 2 )) -le $(PAGESIZE) ] ; then \
	    LEB_SIZE=$$(( $(BLOCKSIZE) - $(PAGESIZE) )) ; \
	else \
	    LEB_SIZE=$$(( $(BLOCKSIZE) - ($(PAGESIZE) * 2) )) ; \
	fi ; \
 	mkfs.ubifs $(if $(VERBOSE:1=),,-v) -r $(FSROOT) -m $(PAGESIZE) \
	  -e $$LEB_SIZE -c 4096 -U --space-fixup \
	  -o ubifs.img

# The image needs to be slightly bigger than the generated fs (by 1MB), we setup the volume for autoresize anyway
ubi.cfg: ubi.cfg.in ubifs.img
	$(V) sed -e "s/@SIZE@/$$(( `du -sDb ubifs.img | cut -f1` + 1048576 ))/" ubi.cfg.in > ubi.cfg

cmdline:
	$(V) echo -n "ubi.mtd=FS root=ubi0:rootfs rootfstype=ubifs " >>$(CMDLINEFILE)

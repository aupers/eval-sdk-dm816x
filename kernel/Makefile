#$L$
# Copyright (C) 2010 Ridgerun (http://www.ridgerun.com). 
##$L$

export USE_KERNEL_TOOLCHAIN=y

include ../bsp/classes/rrsdk.class
include $(CLASSES)/fetcher.defs
include $(CLASSES)/flags.defs

.PHONY: build real_build preconfig patch buildfs headers_install soft_clean clean

build: real_build headers_install
	$(V) $(ECHO) "Build complete"
	$(V)touch $(BUILT_FLAG)

real_build: $(KERNEL) preconfig patch
	$(V) ln -sf $(DEVDIR)/bsp/mach/bspconfig $(KERNEL)/.config
	$(V) cat /dev/zero | $(MAKE) -C $(KERNEL) $(KFLAGS) oldconfig $(QOUT) 2>/dev/null
	$(V) $(MAKE) -j $(BSP_NCPU) -C $(KERNEL) $(KFLAGS)
	$(V) if [ -d $(FSROOT) ] ; then \
	    $(MAKE) -j $(BSP_NCPU) -C $(KERNEL) modules_install $(KFLAGS) INSTALL_MOD_PATH="$(FSROOT)" $(QOUT) ; \
	fi
	$(ARCH_KERNEL_RULES)
ifeq ($(CONFIG_BSP_ARCH_KERNEL_COMPRESS),y)
	$(Q)cp $(KERNEL)/arch/$(ARCH)/boot/zImage $(DEVDIR)/images/vmlinuz
	$(Q)ln -sf vmlinuz $(KERNELIMAGE)
else
	$(Q)cp $(KERNEL)/arch/$(ARCH)/boot/Image $(DEVDIR)/images/vmlinux
	$(Q)ln -sf vmlinux $(KERNELIMAGE)
endif

src: $(KERNEL)
	$(V) if [ ! -L src ] ; then \
	    ln -s $(KERNEL) src ; \
	fi

preconfig: rrpreconfig patch

rrpreconfig: $(KERNEL)
	$(V) cd $(KERNEL); \
	if [ ! -L include/asm ] ; then \
	    ln -s asm-$(ARCH) include/asm ; \
	fi ;
	touch $@

patch: $(KERNEL) rrpreconfig
	$(V)$(MAKE) rrpatched

ifneq (x$(KERNEL_TARBALL),x)
KERNEL_URL?=https://$(DOWNLOAD_SERVER)
endif

ifneq (x$(KERNEL_URL),x)
$(KERNEL): rrfetched
else
$(KERNEL):
	$(V)$(ECHO) "\n$${ERROR_COLOR}Error:$${NORMAL_COLOR} no KERNEL_URL or KERNEL_TARBALL defined, and kernel code not found... aborting\n";
	$(V) exit -1;
endif

KERNEL_TARBALL?=$(KERNEL).tar.bz2
PKG_TARBALL=$(KERNEL_TARBALL)
FETCHER_EXTRACT_DIRECTORY_NAME=$(KERNEL)
PKG_URL=$(KERNEL_URL)

buildfs:
	$(V) $(MAKE) -C $(KERNEL) $(KFLAGS) modules_install INSTALL_MOD_PATH="$(FSROOT)" $(QOUT)

headers_install: $(KERNEL)
	$(V) $(MAKE) -C $(DEVDIR)/fs $(FSDEVROOT) $(QOUT)
	$(V) $(MAKE) -C $(KERNEL) $@ $(KFLAGS) $(QOUT)
	$(V) mkdir -p $(KERNEL_INCLUDE)
	$(V) cp -R $(KERNEL)/usr/include/* $(KERNEL_INCLUDE)

soft_clean: unpatch
	$(V) if [ -d $(KERNEL) ] ; then \
		$(MAKE) -C $(KERNEL) $(KFLAGS) distclean ; \
	fi;

clean: unpatch
	$(V) if ! [ -d $(KERNEL)/.svn ] ; then \
	    rm -Rf $(KERNEL) rrfetched src rrpreconfig ; \
	else \
	    if [ -d $(KERNEL) ] ; then \
		$(MAKE) -C $(KERNEL) $(KFLAGS) distclean ; \
	    fi ; \
	fi

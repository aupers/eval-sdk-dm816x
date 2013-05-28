#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
#$L$

include ../../../bsp/classes/rrsdk_local.class

PKG_VERSION=0.12.0
PKG_URL=http://download.gnome.org/sources/vala/0.12/
PKG_TARBALL=vala-0.12.0.tar.bz2
PKG_SHA1SUM=3799a1cdda63b40b7aa031bca7da6bf1baf000b1

# We do not include $(CLASSES)/autotools_local.class but instead
# replicate the code here since we need to add our custom rules
# for the config.site definitions
# You only do this if you really know what you are doing

AUTOTOOLS_BUILD_DIR=$(HOST_ARCH)
AUTOTOOLS_PARAMS+=--prefix=$(LOCALDIR)
AUTOTOOLS_HOST=
CONFIG_SITE=

include $(CLASSES)/autotools.defs

.PHONY: rrpatched build clean install uninstall distclean

build: autotools_build $(DEVDIR)/fs/config.site.d/vala-$(PKG_VERSION)-host

$(DEVDIR)/fs/config.site.d/vala-$(PKG_VERSION)-host:
	$(V) echo "test -z \"\$$VAPIDIR\" && VAPIDIR=\"$(DEVDIR)/bsp/local/share/vala-0.12/vapi\"" > $@
	$(V) $(MAKE) -C $(DEVDIR)/fs config.site

clean: autotools_clean
	$(V) rm -f installed

install: installed

# The logic for local apps expects a file named installed
installed: autotools_install
	$(V) touch $@

uninstall: autotools_uninstall

distclean: clean rrfetched_clean

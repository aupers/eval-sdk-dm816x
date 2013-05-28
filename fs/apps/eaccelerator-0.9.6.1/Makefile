#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$


PKG_URL=http://sourceforge.net/projects/eaccelerator/files/eaccelerator/eAccelerator%200.9.6.1/
PKG_TARBALL=eaccelerator-0.9.6.1.tar.bz2
PKG_SHA1SUM=c95e87229a6e674b4994d4fc13278e516ea314f9

export mm_sem_pthread=yes

AUTOTOOLS_AUTOGEN_GENERATION_RULE=$(AUTOTOOLS_SRC_DIR)/autogen.sh

PHP_EXTENSIONS_DIR=$(subst $(FSDEVROOT),,$(shell php-config --extension-dir))
LIBRARIES=$(PHP_EXTENSIONS_DIR)/eaccelerator.so

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

$(AUTOTOOLS_SRC_DIR)/autogen.sh:
	$(V) cd $(AUTOTOOLS_SRC_DIR) ; \
	phpize $(QOUT) $(ERRQOUT)
	$(V) sed -i -e "s?  mm_shm_ipc=no?  mm_shm_ipc=yes?" src/configure
	$(V) touch $@ && chmod +x $@

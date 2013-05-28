# Copyright (C) 2007 RidgeRun (http://www.ridgerun.com)
#
# A license for this software is granted for evaluation purposes only.
# Commercial use and/or redistribution is strictly forbidden without 
# written consent from RidgeRun.      
# A free license may be available for educational or personal use.  
# Contact RidgeRun for permission


.PHONY: build chkconfig preconfig buildfs install clean

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

build:
	# Install basic /etc files
	$(V)cp -R etc $(FSROOT)/
	$(V)find $(FSROOT)/etc/ -name .svn | xargs rm -Rf

chkconfig:

preconfig:

buildfs:

install: 

clean: 

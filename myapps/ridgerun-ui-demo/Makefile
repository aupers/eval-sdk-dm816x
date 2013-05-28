#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
#$L$

# We don't have to fetch the source code, is local

FETCHER_NO_DOWNLOAD=yes
QT_BUILD_DIR=src

BINARIES=/usr/bin/ridgerun-ui-demo

QMAKE_OPTIONS=QMAKE_INCDIR="$(DEVDIR)/kernel/$(KERNEL)/include"
INIT_SCRIPT=ridgerun-ui-demo.init
INIT_SCRIPT_LEVEL=99

include ../../bsp/classes/rrsdk.class
include $(CLASSES)/qt.class

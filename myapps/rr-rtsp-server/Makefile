#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

# We don't have to fetch the source code, is local
FETCHER_NO_DOWNLOAD=yes

AUTOTOOLS_PARAMS = LDFLAGS="-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib:$(FSDEVROOT)/lib" --sysconfdir=$(FSDEVROOT)/etc

BINARIES = /usr/bin/rr_rtsp_server
INIT_SCRIPT= rr-rtsp-server.init
INIT_SCRIPT_LEVEL=99

include ../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


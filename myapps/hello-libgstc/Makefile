#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
#$L$

# We don't have to fetch the source code, is local
FETCHER_NO_DOWNLOAD=yes

BINARIES=/usr/bin/hello-libgstc

# Vala code needs to build on his own src dir
AUTOTOOLS_BUILD_DIR=src
# Extra flags for gst apps
AUTOTOOLS_PARAMS = LDFLAGS="-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib:$(FSDEVROOT)/lib" --sysconfdir=$(FSDEVROOT)/etc

include ../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

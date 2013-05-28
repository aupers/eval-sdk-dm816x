#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

# We don't have to fetch the source code, is local
FETCHER_NO_DOWNLOAD=yes


# Extra flags for gst apps
AUTOTOOLS_PARAMS = LDFLAGS="-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib:$(FSDEVROOT)/lib" --sysconfdir=$(FSDEVROOT)/etc

# Name of the binary to install on the final fs
LIBRARIES= /usr/lib/gstreamer-0.10/libgstrrparser.so


include ../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


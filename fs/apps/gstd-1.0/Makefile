#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=git://github.com/RidgeRun/gstd.git
PKG_REVISION=49a819066303cdd57af9b6cd1ec300608225bd19

# When doing development for the application is very tedius to be doing make clean every time
# we do a change on the code, just because we need to re-copy it because doesn't build fine outside
# the src dir. So we just clone the code for the simulator (since we mostly develop for target)
ifeq ($(MAKECMDGOALS),sim)
AUTOTOOLS_CLONE_SOURCE=yes
else
AUTOTOOLS_BUILD_DIR=src
endif

AUTOTOOLS_PARAMS = LDFLAGS="-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib:$(FSDEVROOT)/lib" --sysconfdir=$(FSDEVROOT)/etc
CORRECT_DBUS_SERVICE=/usr/share/dbus-1/system-services/com.ridgerun.gstreamer.gstd.service
INIT_SCRIPT=gstd.init
INIT_SCRIPT_LEVEL=99

BINARIES=   /usr/bin/{gst-client,gstd}
OTHERS= /usr/share/dbus-1/system-services/com.ridgerun.gstreamer.gstd.service \
	/etc/dbus-1/system.d/gstd.conf

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

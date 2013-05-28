#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.alsa-project.org/pub/utils
PKG_TARBALL=alsa-utils-1.0.24.2.tar.bz2
PKG_SHA1SUM=09921047d94369b9bc9f84fb29c61a6baae91bbb

# Since alsa-lib uses modules, we cross-compile with prefix=/usr and setup the DESTDIR
DESTDIR=$(FSDEVROOT)
export CPPFLAGS+=$(shell $(FSDEVROOT)/usr/bin/ncurses5-config --cflags)

# alsa-lib doesn't build fine outside his own dir
AUTOTOOLS_CLONE_SOURCE=yes
AUTOTOOLS_PARAMS=--prefix=/usr --disable-xmlto --disable-nls \
 --with-udev-rules-dir=/usr/libexec/udev/rules.d \
 --with-curses=ncurses ncurses5_config=$(FSDEVROOT)/usr/bin/ncurses5-config \

BINARIES = /usr/bin/{speaker-test,aseqnet,aseqdump,iecset,alsaloop,alsaucm,amidi,aplay,amixer,alsamixer,aconnect,arecord,aplaymidi,arecordmidi} \
           /usr/sbin/{alsaconf,alsactl}
OTHERS = /usr/libexec/udev/rules.d/90-alsa-restore.rules

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.alsa-project.org/pub/lib/
PKG_TARBALL=alsa-lib-1.0.24.1.tar.bz2
PKG_SHA1SUM=e18a337620f23c15223e5e4a27bf04ca43981fc9

# Since alsa-lib uses modules, we cross-compile with prefix=/usr and setup the DESTDIR
DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS=--prefix=/usr --disable-python

CORRECT_LA=/usr/lib/{libasound.la,alsa-lib/smixer/{smixer-ac97.la,smixer-hda.la,smixer-sbase.la}}
CORRECT_PKGCONFIG=/usr/lib/pkgconfig/alsa.pc
DIRECTORIES=/var/lib/alsa

BINARIES = /usr/bin/aserver
LIBRARIES = /usr/lib/{libasound.so.2.0.0,alsa-lib/smixer/{smixer-ac97.so,smixer-hda.so,smixer-sbase.so}}
OTHERS = /usr/share/alsa/{alsa.conf,cards/aliases.conf,pcm/{center_lfe.conf,dmix.conf,dsnoop.conf,hdmi.conf,modem.conf,side.conf,surround41.conf,surround51.conf,default.conf,dpl.conf,front.conf,iec958.conf,rear.conf,surround40.conf,surround50.conf,surround71.conf}}

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


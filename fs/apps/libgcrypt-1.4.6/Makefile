#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.gnupg.org/gcrypt/libgcrypt/
PKG_TARBALL=libgcrypt-1.4.6.tar.gz
PKG_SHA1SUM=dbe3fee0a9eea8128a1e47c973e0f432a62bfaa2

BINARIES = /usr/bin/{dumpsexp,hmac256}
LIBRARIES = /usr/lib/libgcrypt.so.11.6.0

export LDFLAGS=-Wl,-rpath,$(FSDEVROOT)/usr/lib

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

# Extra install steps, need to be defined after including autotools.class
# to have the right order
install::
	$(V) cp $(FSDEVROOT)/usr/share/aclocal/libgcrypt.m4 $(LOCALDIR)/share/aclocal/libgcrypt.m4
	$(V) cp $(FSDEVROOT)/usr/bin/libgcrypt-config $(LOCALDIR)/bin

#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.gnupg.org/gcrypt/libgpg-error/
PKG_TARBALL=libgpg-error-1.10.tar.gz
PKG_SHA1SUM=f964423cb2f29e09dfe5483f00b86518005ca898

BINARIES = /usr/bin/gpg-error
LIBRARIES = /usr/lib/libgpg-error.so.0.8.0

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

# Extra install steps, need to be defined after including autotools.class
# to have the right order
install::
	$(V) cp $(FSDEVROOT)/usr/bin/gpg-error-config $(LOCALDIR)/bin/gpg-error-config

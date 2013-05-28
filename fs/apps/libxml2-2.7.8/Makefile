#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$
PKG_URL = ftp://xmlsoft.org/libxml2/
PKG_TARBALL = libxml2-2.7.8.tar.gz
PKG_SHA1SUM = 859dd535edbb851cc15b64740ee06551a7a17d40

AUTOTOOLS_PARAMS= --with-catalog=no --with-debug=no --with-docbook=no \
--with-ftp=no --with-legacy=no --with-python=no --with-push=no \
--with-xpath=no --with-schematron=no --disable-dependency-tracking

# Fill the spaces with the software components you'll need on the FSROOT
LIBRARIES = /usr/lib/libxml2.so.2.7.8

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$
PKG_URL=http://download.lighttpd.net/lighttpd/releases-1.4.x/
PKG_TARBALL=lighttpd-1.4.28.tar.gz
PKG_SHA1SUM=24d614f75b3aba18f3cff5e52a27ec9fdcf853b5

# Since lighttpd uses modules, we cross-compile with prefix=/usr and setup the DESTDIR
DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS= --without-bzip2 --prefix=/usr
export PCRECONFIG=$(FSDEVROOT)/usr/bin/pcre-config

INIT_SCRIPT=lighttpd.init
INIT_SCRIPT_LEVEL=90

BINARIES=   /usr/sbin/lighttpd
LIBRARIES=  /usr/lib/mod_access.so \
	    /usr/lib/mod_accesslog.so \
	    /usr/lib/mod_alias.so \
	    /usr/lib/mod_auth.so \
	    /usr/lib/mod_cgi.so \
	    /usr/lib/mod_cml.so \
	    /usr/lib/mod_compress.so \
	    /usr/lib/mod_dirlisting.so \
	    /usr/lib/mod_evasive.so \
	    /usr/lib/mod_evhost.so \
	    /usr/lib/mod_expire.so \
	    /usr/lib/mod_extforward.so \
	    /usr/lib/mod_fastcgi.so \
	    /usr/lib/mod_flv_streaming.so \
	    /usr/lib/mod_indexfile.so \
	    /usr/lib/mod_magnet.so \
	    /usr/lib/mod_mysql_vhost.so \
	    /usr/lib/mod_proxy.so \
	    /usr/lib/mod_redirect.so \
	    /usr/lib/mod_rewrite.so \
	    /usr/lib/mod_rrdtool.so \
	    /usr/lib/mod_scgi.so \
	    /usr/lib/mod_secdownload.so \
	    /usr/lib/mod_setenv.so \
	    /usr/lib/mod_simple_vhost.so \
	    /usr/lib/mod_ssi.so \
	    /usr/lib/mod_staticfile.so \
	    /usr/lib/mod_status.so \
	    /usr/lib/mod_trigger_b4_dl.so \
	    /usr/lib/mod_userdir.so \
	    /usr/lib/mod_usertrack.so \
	    /usr/lib/mod_webdav.so

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class
 

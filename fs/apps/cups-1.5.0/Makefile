#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com)
##$L$

PKG_URL=http://ftp.easysw.com/pub/cups/1.5.0/
PKG_TARBALL=cups-1.5.0-source.tar.gz
PKG_SHA1SUM=3891623bb61e6b90b1d4601a22d2a3ea0a4c114a

BINARIES= /usr/bin/{cancel,cups-config,lp,lpq,lpr,lprm,lpstat,ppdi,ppdmerge,ppdpo,ppdhtml,lpoptions,lppasswd}\
/usr/sbin/{accept,cupsaccept,cupsctl,cupsd,cupsdisable,cupsenable,cupsfilter,cupsreject,lpadmin,lpc,lpinfo,lpmove,reject}
LIBRARIES = /usr/lib/{libcupscgi.so.1,libcupsdriver.so.1,libcupsimage.so.2,libcupsmime.so.1,libcupsppdc.so.1,libcups.so.2}
EXTRA_FILES = /usr/share/cups/{banners,charsets,data,drv,fonts,mime,model,profiles} /etc/cups \
/var/{cache/cups,run/cups,log/cups,spool/cups} /usr/lib/cups

INIT_SCRIPT=cupsd.init
INIT_SCRIPT_LEVEL=80

export LDFLAGS =-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -L$(FSDEVROOT)/usr/lib
export DSOFLAGS=-L$(FSDEVROOT)/usr/lib
export DSTROOT=$(FSDEVROOT)

# Cups does not build fine outside itself
AUTOTOOLS_CLONE_SOURCE=yes
AUTOTOOLS_PARAMS=--disable-gssapi --disable-ssl --with-cups-system-groups=pl --without-php --enable-libusb\
--prefix=/usr --sysconfdir=/etc --localstatedir=/var

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

# Correct cups-config, and some file permissions
install:: 
	$(V)sed -i -e 's?prefix=/usr?prefix=$(FSDEVROOT)/usr?' \
	           -e 's?dir=/usr?dir=$(FSDEVROOT)/usr?' \
	                $(FSDEVROOT)/usr/bin/cups-config
	$(V) cp $(FSDEVROOT)/usr/bin/cups-config $(LOCALDIR)/bin
	$(V) if test -d $(FSROOT)/usr/lib/cups/ ; then  $(SUDO) chown -R --from=root:lp `id -nu`:`id -ng` $(FSROOT)/usr/lib/cups/  ; fi
	$(V) $(SUDO) chmod 777 $(LOCALDIR)/bin/cups-config
	$(V) $(SUDO) chmod 666 $(FSDEVROOT)/usr/share/cups/mime/mime.{convs,types}

clean::
	$(V) $(SUDO) rm -rf $(FSROOT)/usr/lib/cups/ $(FSROOT)/etc/cups $(FSDEVROOT)/usr/share/cups

#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$
PKG_URL=http://ftp.gnu.org/pub/gnu/ncurses/
PKG_TARBALL=ncurses-5.7.tar.gz
PKG_SHA1SUM=8233ee56ed84ae05421e4e6d6db6c1fe72ee6797

# We need to use prefix=/usr to avoid ncurses from looking for terminfos in the build dir
AUTOTOOLS_PARAMS=--with-shared --prefix=/usr
DESTDIR=$(FSDEVROOT)

LIBRARIES=  /usr/lib/{libncurses.so.5.7,libform.so.5.7,libmenu.so.5.7,libpanel.so.5.7}
OTHERS= /usr/share/terminfo/v/vt100 \
	/usr/share/terminfo/v/vt102

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

# Extra install steps, need to be defined after including autotools.class
# to have the right order
install::
	$(V)sed -i 's?prefix="/usr"?prefix="$(FSDEVROOT)/usr"?' $(FSDEVROOT)/usr/bin/ncurses5-config
	$(V) cp $(FSDEVROOT)/usr/bin/ncurses5-config $(LOCALDIR)/bin

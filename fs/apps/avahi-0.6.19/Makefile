#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$
PKG_URL=http://avahi.org/download
PKG_TARBALL=avahi-0.6.19.tar.gz
PKG_SHA1SUM=367322064a5dd66a0e69c75df9407ab3518aebdc


# Since avahi hard codes configuration paths into the binaries we cross-compile with prefix=/usr
# and use the DESTDIR parameter to place the output in $(FSDEVROOT)
DESTDIR=$(FSDEVROOT)

AUTOTOOLS_PARAMS= ac_cv_func_malloc_0_nonnull=yes ac_cv_func_realloc_0_nonnull=yes \
--prefix=/usr --sysconfdir=/etc --localstatedir=/var \
--with-avahi-user=root --with-avahi-group=root --with-avahi-priv-access-group=root \
--with-autoipd-user=root --with-autoipd-group=root --disable-glib --disable-qt3 \
--disable-qt4 --disable-gtk --disable-dbus --disable-python --disable-pygtk \
--disable-python-dbus --disable-mono --disable-monodoc --disable-doxygen-doc \
--disable-doxygen-dot --disable-doxygen-html --disable-stack-protector \
--disable-manpages --disable-xmltoman --with-distro=none --disable-gdbm \
--disable-gtk3

INIT_SCRIPT=avahi-daemon.init
INIT_SCRIPT_LEVEL=99

BINARIES= /usr/sbin/avahi-daemon /usr/sbin/avahi-autoipd /usr/sbin/avahi-dnsconfd

LIBRARIES= 	/usr/lib/libavahi-core.so.5.0.2 \
				/usr/lib/libavahi-common.so.3.4.4

OTHERS= /etc/avahi/avahi-autoipd.action \
				/etc/avahi/avahi-daemon.conf \
				/etc/avahi/avahi-dnsconfd.action \
				/etc/avahi/hosts \
				/etc/avahi/services/sftp-ssh.service \
				/etc/avahi/services/ssh.service

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class

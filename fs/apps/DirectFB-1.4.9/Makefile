#$L$
#$L$
# Copyright (C) 2011 Ridgerun
##$L$

PKG_URL=http://directfb.org/downloads/Core/DirectFB-1.4
PKG_TARBALL=DirectFB-1.4.9.tar.gz
PKG_SHA1SUM=f5f6a9b3b439a03b7bc0df408873920a821b1d48

include ../../../bsp/classes/rrsdk.class

BINARIES= /usr/bin/{dfbg,dfbinspector}
LIBRARIES = /usr/lib/{libfusion-1.4.so.5.0.4,libdirectfb-1.4.so.5.0.4,libdirect-1.4.so.5.0.4}
LIBRARIES_OPTIONAL = /usr/lib/directfb-1.4-5/{inputdrivers/libdirectfb_linux_input.so,interfaces/IDirectFBFont/{libidirectfbfont_dgiff.so,libidirectfbfont_ft2.so},interfaces/IDirectFBImageProvider/{libidirectfbimageprovider_dfiff.so,libidirectfbimageprovider_gif.so,libidirectfbimageprovider_jpeg.so,libidirectfbimageprovider_png.so},interfaces/IDirectFBVideoProvider/libidirectfbvideoprovider_gif.so,systems/{libdirectfb_devmem.so,libdirectfb_dummy.so,libdirectfb_fbdev.so},wm/libdirectfbwm_default.so}

AUTOTOOLS_BUILD_DIR=$(AUTOTOOLS_SRC_DIR)
DESTDIR=$(FSDEVROOT)
AUTOTOOLS_PARAMS = --prefix=/usr --with-inputdrivers="linuxinput tslib" --enable-png --with-gfxdrivers=none --enable-zlib \
--enable-shared --disable-debug --disable-video4linux --disable-vnc  --disable-osx --with-tests LDFLAGS="$(APPS_LDFLAGS)" CFLAGS="$(APPS_CFLAGS)"
AUTOTOOLS_CORRECT_LA_SED_EXPRESSION?=s?libdir='/usr?libdir='$(FSDEVROOT)/usr?g;\
        s?\ /usr/lib?\ $(FSDEVROOT)//usr/lib?g
AUTOTOOLS_CORRECT_LA=/usr/lib/{libfusion.la,libdirectfb.la,libdirect.la}
AUTOTOOLS_CORRECT_PKGCONFIG=/usr/lib/pkgconfig/{direct.pc,directfb-internal.pc,directfb.pc,fusion.pc}

APPS_LDFLAGS+=-Wl,--rpath-link -Wl,$(FSDEVROOT)/usr/lib -lm
APPS_CFLAGS+="-D_GNU_SOURCE"

ifeq ($(CONFIG_FS_APPS_DIRECTFB_FREETYPE),y)
 AUTOTOOLS_PARAMS+=--enable-freetype FREETYPE_CONFIG="$(FSDEVROOT)/usr/bin/freetype-config"
else
 AUTOTOOLS_PARAMS+=--disable-freetype
endif

ifeq ($(CONFIG_FS_APPS_DIRECTFB_JPEG),y)
AUTOTOOLS_PARAMS+=--enable-jpeg
else
AUTOTOOLS_PARAMS+=--disable-jpeg
endif

ifeq ($(MAKECMDGOALS),sim)
AUTOTOOLS_PARAMS += --enable-x11 --disable-fbdev
else
AUTOTOOLS_PARAMS += --disable-x11 --enable-fbdev
endif

include $(CLASSES)/autotools.class

# Post install fixes
install::
	$(V)sed -i 's?prefix=/usr?prefix=$(FSDEVROOT)/usr?' $(FSDEVROOT)/usr/bin/directfb-config

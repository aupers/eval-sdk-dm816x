#$L$
# Copyright (C) 2012 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=ftp://ftp.qt-project.org/qt/source/
PKG_TARBALL=qt-everywhere-opensource-src-4.7.2.tar.gz
PKG_SHA1SUM=84414f82bbc9e8d356b986d5d1ebee89d06e4f2e

LIBRARIES= usr/lib/{libQtTest.so.4.7.2,libQtSql.so.4.7.2,libQtXml.so.4.7.2,libQtCore.so.4.7.2,libQtDeclarative.so.4.7.2} \
    usr/lib/{libQtGui.so.4.7.2,libQtScript.so.4.7.2,libQtMultimedia.so.4.7.2,libQtNetwork.so.4.7.2}
LIBRARIES_OPTIONAL=usr/lib/{libQtDBus.so.4.7.2,libQtOpenGL.so.4.7.2,libQtOpenVG.so.4.7.2,libpvrQWSWSEGL.so.1.0.0,libpvrQWSWSEGL.so.1.0} \
   usr/plugins/gfxdrivers/libqgfxpvregl.so \
   usr/plugins/script/libqtscriptdbus.so \
   usr/plugins/sqldrivers/libqsqlite.so
EXTRA_FILES=usr/lib/fonts/
OTHERS= usr/plugins/imageformats/{libqico.so,libqjpeg.so} \
    usr/plugins/bearer/libqgenericbearer.so \
    usr/plugins/qmltooling/libtcpserver.so

# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class

QT_CONF_LOG=$(CURDIR)/$(ARCH)/configure.log
FETCHER_EXTRACT_DIRECTORY_NAME=src
AUTOTOOLS_BUILD_DIR=src

build: check_sgxsdk rrfetched built$(ARCH_SUFFIX)

sim: build install

built$(ARCH_SUFFIX): configured$(ARCH_SUFFIX)
	$(V) $(MAKE) -C $(ARCH) -j $(BSP_NCPU) $(QOUT) $(ERRQOUT)
	$(V) touch $@

CONFIG_OPTIONS= \
-opensource \
-force-pkg-config \
-no-accessibility \
-no-cups \
-no-iconv \
-no-largefile \
-no-libmng \
-no-libtiff \
-nomake demos \
-nomake docs \
-nomake tools \
-nomake translations \
-no-nis \
-no-openssl \
-no-phonon \
-no-phonon-backend \
-no-qt3support \
-no-scripttools \
-no-webkit \
-no-xmlpatterns \
-qt-gfx-transformed \
-release \
-shared \
-no-gif \
-qt-libpng \
-system-freetype \
-system-libjpeg \
-system-zlib \
-qt-mouse-linuxinput

ifneq ($(CONFIG_FS_APPS_QT_OPENGL),y)
CONFIG_OPTIONS+= \
-nomake examples \
-no-pch \
-no-svg 
endif

ifeq ($(CONFIG_FS_APPS_QT_OPENGL),y)
EXTRA_FILES+=examples/
CONFIG_OPTIONS+=-xplatform qws/linux-TIarmv7-sgx-g++ -depths 16,24,32 -qt-freetype \
-no-mmx -no-3dnow -no-sse -no-sse2 -no-sse3 -no-sse4.1 -no-sse4.2 -no-ssse3 -no-avx -no-cups \
-qt-mouse-pc -no-mouse-tslib -plugin-mouse-pc -little-endian \
-opengl es2 -openvg -qt-gfx-transformed -qt-gfx-linuxfb -qt-gfx-multiscreen -plugin-gfx-powervr \
-D QT_NO_QWS_CURSOR -D QT_QWS_CLIENTBLIT -examplesdir $(FSDEVROOT)/examples
LIBRARIES+= usr/lib/libQtSvg.so.4.7.2
endif

ifneq ($(CONFIG_FS_APPS_QT_MOUSE),y)
CONFIG_OPTIONS+=-no-feature-CURSOR
endif

ifeq ($(MAKECMDGOALS),sim)
CONFIG_OPTIONS+=-no-rpath
else
CONFIG_OPTIONS+=-embedded $(ARCH)
endif

ifeq ($(CONFIG_FS_APPS_QT_DBUS),y)
CONFIG_OPTIONS+=-dbus
else
CONFIG_OPTIONS+=-no-dbus
endif

ifeq ($(CONFIG_FS_APPS_QT_EXCEPTIONS),y)
CONFIG_OPTIONS+=-exceptions
else
CONFIG_OPTIONS+=-no-exceptions
endif

ifeq ($(CONFIG_FS_APPS_QT_TSLIB),y)
CONFIG_OPTIONS+=-qt-mouse-tslib
endif

ifeq ($(CONFIG_FS_APPS_QT_GLIB),y)
CONFIG_OPTIONS+=-glib
else
CONFIG_OPTIONS+=-no-glib
endif

ifeq ($(CONFIG_FS_APPS_QT_SQLITE),y)
CONFIG_OPTIONS+=-system-sqlite
else
CONFIG_OPTIONS+=-no-sql-sqlite
endif

ifeq ($(CONFIG_FS_APPS_QT_STL),y)
CONFIG_OPTIONS+=-stl
else
CONFIG_OPTIONS+=-no-stl
endif

ifeq ($(CONFIG_FS_APPS_QT_VNC),y)
CONFIG_OPTIONS+=-qt-gfx-vnc
endif

ifeq ($(CONFIG_FS_APPS_QT_NOWINSTYLE),y)
CONFIG_OPTIONS+=-no-decoration-windows
endif

ifeq ($(CONFIG_FS_APPS_QT_COMPACT),y)
CONFIG_OPTIONS+=-no-feature-TEXTHTMLPARSER \
    -no-feature-TEXTODFWRITER \
    -no-feature-SESSIONMANAGER \
    -no-feature-SOUND \
    -no-feature-EFFECTS \
    -no-feature-SYNTAXHIGHLIGHTER \
    -no-feature-PRINTPREVIEWWIDGET \
    -no-feature-PRINTDIALOG \
    -no-feature-PRINTPREVIEWDIALOG \
    -no-feature-MOVIE \
    -no-feature-PAINT_DEBUG \
    -no-feature-FTP \
    -no-feature-HTTP \
    -no-feature-UDPSOCKET \
    -no-feature-NETWORKPROXY \
    -no-feature-SOCKS5 \
    -no-feature-COP \
    -no-feature-NETWORKINTERFACE \
    -no-feature-SYSTEMTRAYICON \
    -no-feature-SCRIPT \
    -no-feature-QWS_SOUNDSERVER

ifneq ($(MAKECMDGOALS),sim)
CONFIG_OPTIONS+=-no-feature-CLIPBOARD \
    -no-feature-DRAGANDDROP \
    -no-feature-CONTEXTMENU
endif
endif

check_sgxsdk:
ifeq ($(CONFIG_FS_APPS_QT_OPENGL),y)
	$(V) if [ ! -e `dirname $(SGXSDK)` ] ; then \
		$(ECHO) "$(ERROR_COLOR)Error:$(NORMAL_COLOR) SGXSDK is not part of your RidgeRun SDK, please contact RidgeRun to add this support" ; \
		exit -1 ; \
	    else \
		$(MAKE) -C `dirname $(SGXSDK)` ; \
	    fi ;
endif

QMAKE_CONF=qmake.conf
QMAKE_OPEN_GL_CONF=qmake-openGL.conf
-include $(DEVDIR)/fs/Apps.defs

configured$(ARCH_SUFFIX): rrpatched
	$(V) cp $(QMAKE_CONF) src/mkspecs/qws/linux-arm-g++/qmake.conf
	$(V) sed -i -e "s?^SDK_BASE.*?SDK_BASE=$(DEVDIR) ?" -e "s?^TOOLCHAIN_PREFIX.*?TOOLCHAIN_PREFIX=$(TOOLCHAIN_PREFIX) ?" src/mkspecs/qws/linux-arm-g++/qmake.conf
ifneq ($(CONFIG_FS_APPS_QT_OPENGL),)
	$(V) install -D $(QMAKE_OPEN_GL_CONF) src/mkspecs/qws/linux-TIarmv7-sgx-g++/qmake.conf
	$(V) sed -i -e "s?^SGXSDK_BASE.*?SGXSDK_BASE=$(SGXSDK) ?" src/mkspecs/qws/linux-TIarmv7-sgx-g++/qmake.conf
endif
	$(V) [ -d $(ARCH) ] || mkdir $(ARCH)
	$(V) cd $(ARCH) ; echo -e "yes\n" | ../src/configure \
	    $(CONFIG_OPTIONS) \
	    -prefix /usr \
	    -hostprefix $(FSDEVROOT)/usr \
			-v > $(QT_CONF_LOG) $(ERRQOUT)
	$(V) touch $@

installed$(ARCH_SUFFIX):
	$(V) $(MAKE) -C $(ARCH) install $(QOUT) $(ERRQOUT)
	$(V) mkdir -p $(FSDEVROOT)/usr/hostbin
	$(V) ln -sf -t $(FSDEVROOT)/usr/hostbin $(FSDEVROOT)/usr/bin/qmake $(FSDEVROOT)/usr/bin/moc $(FSDEVROOT)/usr/bin/uic $(FSDEVROOT)/usr/bin/rcc
	$(V) touch $@

install: installed$(ARCH_SUFFIX) rrsdk_install
ifneq ($(CONFIG_FS_APPS_QT_OPENGL)),)
	$(V) cd $(FSROOT)/usr/lib ; rm -rf libpvrQWSWSEGL.so ; ln -s libpvrQWSWSEGL.so.1.0.0 libpvrQWSWSEGL.so
endif

uninstall:
	$(V)$(MAKE) -C $(ARCH) uninstall INSTALL_PREFIX=$(FSDEVROOT) $(QOUT)
	$(V) touch $@

clean: unpatch
	$(V) rm -Rf installed* built* configured* $(ARCH) $(QT_CONF_LOG) src/mkspecs/qws/linux-arm-g++/qmake.conf sim .qmake.vars

distclean: clean rrfetched_clean

include $(CLASSES)/fetcher.defs

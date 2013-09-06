QT_VERSION=4.8.4

PKG_URL=http://releases.qt-project.org/qt4/source/
PKG_TARBALL=qt-everywhere-opensource-src-$(QT_VERSION).tar.gz
PKG_SHA1SUM=f5880f11c139d7d8d01ecb8d874535f7d9553198

LIBRARIES= \
	/usr/lib/libQtCore.so.$(QT_VERSION) \
	/usr/lib/libQtGui.so.$(QT_VERSION) \
	/usr/lib/libQtNetwork.so.$(QT_VERSION) \
	/usr/lib/libQtSql.so.$(QT_VERSION) \
	/usr/lib/libQtTest.so.$(QT_VERSION) \
	/usr/lib/libQtXml.so.$(QT_VERSION)

LIBRARIES_OPTIONAL= \
	/usr/lib/libQtDBus.so.$(QT_VERSION) \
	/usr/lib/libQtDeclarative.so.$(QT_VERSION) \
	/usr/lib/libQtMultimedia.so.$(QT_VERSION) \
	/usr/lib/libQtOpenGL.so.$(QT_VERSION) \
	/usr/lib/libQtOpenVG.so.$(QT_VERSION) \
	/usr/lib/libQtScript.so.$(QT_VERSION) \
	/usr/lib/libQtScriptTools.so.$(QT_VERSION) \
	/usr/lib/libQtWebKit.so.4.9.3 \
	/usr/lib/libpvrQWSWSEGL.so.1.0.0 \
	/usr/lib/libpvrQWSWSEGL.so.1.0 \
	/usr/plugins/gfxdrivers/libqgfxpvregl.so

OTHERS= \
	/usr/lib/fonts/{DejaVuSans.ttf,DejaVuSans-Bold.ttf,DejaVuSans-Oblique.ttf,DejaVuSans-BoldOblique.ttf} \
	/usr/plugins/imageformats/{libqico.so,libqjpeg.so} \
	/usr/plugins/bearer/libqgenericbearer.so

# We include this definitions here instead of the bottom of the Makefile
# because we need to get the $(ARCH) variable definition
include ../../../bsp/classes/rrsdk.class

QT_CONF_LOG=$(CURDIR)/$(ARCH)/configure.log
FETCHER_EXTRACT_DIRECTORY_NAME=src

build: check_sgxsdk rrfetched rrpatched built$(ARCH_SUFFIX)

sim: build install

built$(ARCH_SUFFIX): configured$(ARCH_SUFFIX)
	$(V) $(MAKE) -C $(ARCH) -j $(BSP_NCPU) $(QOUT) $(ERRQOUT)
	$(V) touch $@

CONFIG_OPTIONS= \
  -v \
  -opensource \
  -force-pkg-config \
  -nomake demos \
  -nomake docs \
  -nomake tools \
  -nomake translations \
  -no-accessibility \
  -no-audio-backend \
  -no-declarative \
  -no-gif \
  -no-iconv \
  -no-javascript-jit \
  -no-libmng \
  -no-libtiff \
  -no-multimedia \
  -no-nas-sound \
  -no-nis \
  -no-openssl \
  -no-pch \
  -no-phonon \
  -no-phonon-backend\
  -no-qt3support \
  -no-rpath \
  -no-sm \
  -no-xmlpatterns \
  -qt-gfx-transformed \
  -system-libpng \
  -system-freetype \
  -system-libjpeg \
  -system-zlib \
  -qt-mouse-linuxinput 


ifeq ($(CONFIG_FS_APPS_QT_OPENGL),y)
  CONFIG_OPTIONS+=-depths 16,24,32 -opengl es2 -openvg -plugin-gfx-powervr -qt-gfx-linuxfb \
  -no-mmx -no-3dnow -no-sse -no-sse2 -no-sse3 -no-sse4.1 -no-sse4.2 -no-ssse3 -no-avx -little-endian -qt-gfx-transformed \
  -qt-gfx-linuxfb -qt-gfx-multiscreen -D QT_NO_QWS_CURSOR -D QT_QWS_CLIENTBLIT
endif

ifeq ($(CONFIG_FS_APPS_QT_EXAMPLES),y)
  EXTRA_FILES+=examples/
  CONFIG_OPTIONS+=-examplesdir $(FSDEVROOT)/examples
else
  CONFIG_OPTIONS+=-nomake examples
endif

ifeq ($(MAKECMDGOALS),sim)
  CONFIG_OPTIONS+=-prefix $(SIMROOT)/usr
  CONFIG_OPTIONS+=-I $(SIMROOT)/usr/include -I $(SIMROOT)/include
  CONFIG_OPTIONS+=-L $(SIMROOT)/usr/lib -L $(SIMROOT)/lib
else
  CONFIG_OPTIONS+=-prefix /usr -hostprefix $(FSDEVROOT)/usr
  ifeq ($(ARCH),arm)
    CONFIG_OPTIONS+=-embedded arm-gnueabi
  else
    CONFIG_OPTIONS+=-embedded $(ARCH)
  endif
endif

ifeq ($(CONFIG_FS_APPS_QT_CUPS),y)
  CONFIG_OPTIONS+=-cups
else
  CONFIG_OPTIONS+=-no-cups
endif

ifeq ($(CONFIG_FS_APPS_QT_DBUS),y)
  CONFIG_OPTIONS+=-dbus
else
  CONFIG_OPTIONS+=-no-dbus
endif

ifeq ($(CONFIG_FS_APPS_QT_DEBUG),y)
  CONFIG_OPTIONS+=-debug
else
  CONFIG_OPTIONS+=-release
endif

ifeq ($(CONFIG_FS_APPS_QT_EXCEPTIONS),y)
  CONFIG_OPTIONS+=-exceptions
else
  CONFIG_OPTIONS+=-no-exceptions
endif

ifeq ($(CONFIG_FS_APPS_QT_GLIB),y)
  CONFIG_OPTIONS+=-glib
else
  CONFIG_OPTIONS+=-no-glib
endif

ifneq ($(FS_APPS_QT_MULTIPROCESS),y)
  CONFIG_OPTIONS+=-no-feature-QWS_MULTIPROCESS
endif

ifeq ($(CONFIG_FS_APPS_QT_NO_QWS_MOUSE_CURSOR),y)
  CONFIG_OPTIONS+=-no-feature-QWS_CURSOR
else
  CONFIG_OPTIONS+=-feature-QWS_CURSOR
endif

ifeq ($(CONFIG_FS_APPS_QT_SCRIPT),y)
  CONFIG_OPTIONS+=-script -scripttools
else
  CONFIG_OPTIONS+=-no-script -no-scripttools
endif

ifeq ($(CONFIG_FS_APPS_QT_SQLITE),y)
  CONFIG_OPTIONS+=-system-sqlite
else
  CONFIG_OPTIONS+=-no-sql-sqlite
endif

ifeq ($(CONFIG_FS_APPS_QT_STATIC),y)
  CONFIG_OPTIONS+=-static
else
  CONFIG_OPTIONS+=-shared
endif

ifeq ($(CONFIG_FS_APPS_QT_STL),y)
  CONFIG_OPTIONS+=-stl
else
  CONFIG_OPTIONS+=-no-stl
endif

ifeq ($(CONFIG_FS_APPS_QT_SVG),y)
  CONFIG_OPTIONS+=-svg
else
  CONFIG_OPTIONS+=-no-svg
endif

ifeq ($(CONFIG_FS_APPS_QT_TSLIB),y)
  CONFIG_OPTIONS+=-qt-mouse-tslib
endif

ifeq ($(CONFIG_FS_APPS_QT_VNC),y)
  CONFIG_OPTIONS+=-qt-gfx-vnc
endif

ifeq ($(CONFIG_FS_APPS_QT_WEBKIT),y)
  CONFIG_OPTIONS+=-webkit -D ENABLE_VIDEO=0
else
  CONFIG_OPTIONS+=-no-webkit
endif

-include $(DEVDIR)/fs/Apps.defs

# TODO remove this workaround (should be somewhere in bsp/classes/...)
ifeq ($(MAKECMDGOALS),sim)
  export PKG_CONFIG_SYSROOT=$(SIMROOT)
else
  export PKG_CONFIG_SYSROOT=$(FSDEVROOT)
endif

QT_TOOLS= \
  lconvert \
  lrelease \
  lupdate \
  qcollectiongenerator \
  qdbuscpp2xml \
  qdbusxml2cpp

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
QMAKE_CONF_DEST=src/mkspecs/qws/linux-arm-gnueabi-g++/$(QMAKE_CONF)
configured$(ARCH_SUFFIX): rrpatched
ifneq ($(MAKECMDGOALS),sim)
	$(V) cp $(QMAKE_CONF) $(QMAKE_CONF_DEST)
	$(V) sed -i \
		-e "s?___DEVDIR___?$(DEVDIR)?g" \
		-e "s?___TOOLCHAIN_CC___?$(CC)?g" \
		-e "s?___TOOLCHAIN_CXX___?$(CXX)?g" \
		-e "s?___TOOLCHAIN_AR___?$(AR)?g" \
		-e "s?___TOOLCHAIN_OBJCOPY___?$(OBJCOPY)?g" \
		-e "s?___TOOLCHAIN_STRIP___?$(STRIP)?g" \
		$(QMAKE_CONF_DEST)
ifeq	($(CONFIG_FS_APPS_QT_OPENGL),y)
	$(V) sed -i \
		-e "s?___SGX_SDK_ROOT___?$(SGXSDK)?g" \
		$(QMAKE_CONF_DEST)
else
	$(V) sed -i \
		-e "s?QMAKE_LIBS_OPENGL_ES2   =?#QMAKE_LIBS_OPENGL_ES2   =?g" \
		-e "s?QMAKE_LIBS_OPENGL_ES1   =?#QMAKE_LIBS_OPENGL_ES1   =?g" \
		-e "s?QMAKE_LIBS_OPENVG       =?#QMAKE_LIBS_OPENVG       =?g" \
		-e "s?QMAKE_LIBS_EGL          =?#QMAKE_LIBS_EGL          =?g" \
		-e "s?QMAKE_LIBS =?#QMAKE_LIBS =?g" \
		$(QMAKE_CONF_DEST)

endif
endif
	$(V) [ -d $(ARCH) ] || mkdir $(ARCH)
	$(V) cd $(ARCH) ; echo -e "yes\n" | ../src/configure $(CONFIG_OPTIONS) &> $(QT_CONF_LOG)
	$(V) touch $@

installed$(ARCH_SUFFIX):
	$(V) $(MAKE) -C $(ARCH) install $(QOUT) $(ERRQOUT)
	$(V) for TOOL in $(QT_TOOLS) ; do \
		ln -sf -t $(LOCALDIR)/bin $(CURDIR)/tools/$${TOOL} ; \
		ln -sf -t $(FSDEVROOT)/usr/bin $(CURDIR)/tools/$${TOOL} ; \
	done $(QOUT) $(ERRQOUT)
	$(V) touch $@

install: installed$(ARCH_SUFFIX) rrsdk_install
ifneq ($(CONFIG_FS_APPS_QT_OPENGL)),)
	$(V) cd $(FSROOT)/usr/lib ; rm -rf libpvrQWSWSEGL.so ; ln -s libpvrQWSWSEGL.so.1.0.0 libpvrQWSWSEGL.so
endif

uninstall:
	$(V)$(MAKE) -C $(ARCH) uninstall INSTALL_PREFIX=$(FSDEVROOT) $(QOUT)
	$(V) touch $@

clean: unpatch
	$(V) rm -Rf installed* built* configured* $(ARCH) $(QT_CONF_LOG) $(QMAKE_CONF_DEST) sim .qmake.vars

distclean: clean rrfetched_clean

TMP_DIR:=$(shell mktemp -d)
gentools:
	mkdir -p $(TMP_DIR)/{src,install,build}
	cd $(TMP_DIR)/src && tar --strip 1 -xzf $(DEVDIR)/downloads/$(PKG_TARBALL)
	cd $(TMP_DIR)/build ; echo -e "yes\n" | ../src/configure \
		-prefix $(TMP_DIR)/install \
		-opensource \
		-force-pkg-config \
		-nomake demos \
		-nomake docs \
		-nomake examples \
		-no-accessibility \
		-no-audio-backend \
		-no-gif \
		-no-iconv \
		-no-javascript-jit \
		-no-libmng \
		-no-libtiff \
		-no-multimedia \
		-no-nas-sound \
		-no-nis \
		-no-opengl \
		-no-openssl \
		-no-openvg \
		-no-pch \
		-no-phonon \
		-no-phonon-backend\
		-no-qt3support \
		-no-sm \
		-no-svg \
		-no-xmlpatterns \
		-qt-gfx-transformed \
		-system-libpng \
		-system-freetype \
		-system-libjpeg \
		-system-zlib \
		-no-rpath \
		-no-cups \
		-dbus \
		-release \
		-no-glib \
		-no-script -no-scripttools \
		-no-sql-sqlite \
		-static \
		-no-webkit
	$(MAKE) -C $(TMP_DIR)/build -j $(BSP_NCPU)
	$(MAKE) -C $(TMP_DIR)/build -j $(BSP_NCPU) install
	for TOOL in $(QT_TOOLS) ; do \
		cp -f $(TMP_DIR)/install/bin/$${TOOL} $(CURDIR)/tools/$${TOOL} ; \
	done

include $(CLASSES)/fetcher.defs


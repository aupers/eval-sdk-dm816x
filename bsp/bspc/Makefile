# These targets are used from top-level makefile

HOSTCC=$(CC)
SHELL=/bin/bash

all: conf mconf

#kxgettext conf mconf qconf gconf

LXDIALOG=lxdialog/checklist.o lxdialog/util.o lxdialog/inputbox.o lxdialog/textbox.o lxdialog/yesno.o lxdialog/menubox.o
CFLAGS+=${shell $(SHELL) lxdialog/check-lxdialog.sh -ccflags $(CC)}

conf: conf.o zconf.tab.o

mconf: $(LXDIALOG) mconf.o zconf.tab.o 
	$(CC) -o $@ $^ ${shell $(SHELL) lxdialog/check-lxdialog.sh -ldflags $(CC)}

clean:
	rm -f *.o mconf conf lxdialog/*.o

zconf.tab.o: lex.zconf.c zconf.hash.c

kconfig_load.o: lkc_defs.h

lkc_defs.h: $(src)/lkc_proto.h
	sed < $< > $@ 's/P(\([^,]*\),.*/#define \1 (\*\1_p)/'


###
# The following requires flex/bison/gperf
# By default we use the _shipped versions, uncomment the following line if
# you are modifying the flex/bison src.
# LKC_GENPARSER := 1

ifdef LKC_GENPARSER

zconf.tab.c: zconf.y
lex.zconf.c: zconf.l
zconf.hash.c: zconf.gperf

%.tab.c: %.y
	bison -l -b $* -p $(notdir $*) $<
	cp $@ $@_shipped

lex.%.c: %.l
	flex -L -P$(notdir $*) -o$@ $<
	cp $@ $@_shipped

%.hash.c: %.gperf
	gperf < $< > $@
	cp $@ $@_shipped

endif



update-po-config: kxgettext
	xgettext --default-domain=linux \
          --add-comments --keyword=_ --keyword=N_ \
          --files-from=scripts/kconfig/POTFILES.in \
          --output scripts/kconfig/config.pot
	$(Q)ln -fs Kconfig_i386 arch/um/Kconfig_arch
	$(Q)for i in `ls arch/`; \
	do \
	  scripts/kconfig/kxgettext arch/$$i/Kconfig \
	    | msguniq -o scripts/kconfig/linux_$${i}.pot; \
	done
	$(Q)msgcat scripts/kconfig/config.pot \
	  `find scripts/kconfig/ -type f -name linux_*.pot` \
	  --output scripts/kconfig/linux_raw.pot
	$(Q)msguniq --sort-by-file scripts/kconfig/linux_raw.pot \
	    --output scripts/kconfig/linux.pot
	$(Q)rm -f arch/um/Kconfig_arch
	$(Q)rm -f scripts/kconfig/linux_*.pot scripts/kconfig/config.pot

HOST_EXTRACFLAGS += -DLOCALE

kxgettext-objs	:= kxgettext.o zconf.tab.o

hostprogs-y := conf qconf gconf kxgettext


ifeq ($(qconf-target),1)
qconf-cxxobjs	:= qconf.o
qconf-objs	:= kconfig_load.o zconf.tab.o
endif

ifeq ($(gconf-target),1)
gconf-objs	:= gconf.o kconfig_load.o zconf.tab.o
endif


# Needed for systems without gettext
KBUILD_HAVE_NLS := $(shell \
     if echo "\#include <libintl.h>" | $(HOSTCC) $(HOSTCFLAGS) -E - > /dev/null 2>&1 ; \
     then echo yes ; \
     else echo no ; fi)
ifeq ($(KBUILD_HAVE_NLS),no)
HOSTCFLAGS	+= -DKBUILD_NO_NLS
endif

# generated files seem to need this to find local include files
HOSTCFLAGS_lex.zconf.o	:= -I$(src)
HOSTCFLAGS_zconf.tab.o	:= -I$(src)

HOSTLOADLIBES_qconf	= $(KC_QT_LIBS) -ldl
HOSTCXXFLAGS_qconf.o	= $(KC_QT_CFLAGS) -D LKC_DIRECT_LINK

HOSTLOADLIBES_gconf	= `pkg-config --libs gtk+-2.0 gmodule-2.0 libglade-2.0`
HOSTCFLAGS_gconf.o	= `pkg-config --cflags gtk+-2.0 gmodule-2.0 libglade-2.0` \
                          -D LKC_DIRECT_LINK

qconf.o: .tmp_qtcheck

ifeq ($(qconf-target),1)
.tmp_qtcheck: $(src)/Makefile
-include .tmp_qtcheck

# QT needs some extra effort...
.tmp_qtcheck:
	@set -e; echo "  CHECK   qt"; dir=""; pkg=""; \
	pkg-config --exists qt 2> /dev/null && pkg=qt; \
	pkg-config --exists qt-mt 2> /dev/null && pkg=qt-mt; \
	if [ -n "$$pkg" ]; then \
	  cflags="\$$(shell pkg-config $$pkg --cflags)"; \
	  libs="\$$(shell pkg-config $$pkg --libs)"; \
	  moc="\$$(shell pkg-config $$pkg --variable=prefix)/bin/moc"; \
	  dir="$$(pkg-config $$pkg --variable=prefix)"; \
	else \
	  for d in $$QTDIR /usr/share/qt* /usr/lib/qt*; do \
	    if [ -f $$d/include/qconfig.h ]; then dir=$$d; break; fi; \
	  done; \
	  if [ -z "$$dir" ]; then \
	    echo "*"; \
	    echo "* Unable to find the QT3 installation. Please make sure that"; \
	    echo "* the QT3 development package is correctly installed and"; \
	    echo "* either install pkg-config or set the QTDIR environment"; \
	    echo "* variable to the correct location."; \
	    echo "*"; \
	    false; \
	  fi; \
	  libpath=$$dir/lib; lib=qt; osdir=""; \
	  $(HOSTCXX) -print-multi-os-directory > /dev/null 2>&1 && \
	    osdir=x$$($(HOSTCXX) -print-multi-os-directory); \
	  test -d $$libpath/$$osdir && libpath=$$libpath/$$osdir; \
	  test -f $$libpath/libqt-mt.so && lib=qt-mt; \
	  cflags="-I$$dir/include"; \
	  libs="-L$$libpath -Wl,-rpath,$$libpath -l$$lib"; \
	  moc="$$dir/bin/moc"; \
	fi; \
	if [ ! -x $$dir/bin/moc -a -x /usr/bin/moc ]; then \
	  echo "*"; \
	  echo "* Unable to find $$dir/bin/moc, using /usr/bin/moc instead."; \
	  echo "*"; \
	  moc="/usr/bin/moc"; \
	fi; \
	echo "KC_QT_CFLAGS=$$cflags" > $@; \
	echo "KC_QT_LIBS=$$libs" >> $@; \
	echo "KC_QT_MOC=$$moc" >> $@
endif

gconf.o: .tmp_gtkcheck

ifeq ($(gconf-target),1)
-include .tmp_gtkcheck

# GTK needs some extra effort, too...
.tmp_gtkcheck:
	@if `pkg-config --exists gtk+-2.0 gmodule-2.0 libglade-2.0`; then		\
		if `pkg-config --atleast-version=2.0.0 gtk+-2.0`; then			\
			touch $@;								\
		else									\
			echo "*"; 							\
			echo "* GTK+ is present but version >= 2.0.0 is required.";	\
			echo "*";							\
			false;								\
		fi									\
	else										\
		echo "*"; 								\
		echo "* Unable to find the GTK+ installation. Please make sure that"; 	\
		echo "* the GTK+ 2.0 development package is correctly installed..."; 	\
		echo "* You need gtk+-2.0, glib-2.0 and libglade-2.0."; 		\
		echo "*"; 								\
		false;									\
	fi
endif


qconf.o: qconf.moc lkc_defs.h

gconf.o: lkc_defs.h

%.moc: $(src)/%.h
	$(KC_QT_MOC) -i $< -o $@


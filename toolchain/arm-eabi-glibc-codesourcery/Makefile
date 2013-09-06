#$L$
# Copyright (C) 2010 Ridgerun (http://www.ridgerun.com). 
#
#  This source code has a dual license.  If this file is linked with other
#  source code that has a GPL license, then this file is licensed with a GPL
#  license as described below.  Otherwise the source code contained in this
#  file is property of Ridgerun. This source code is protected under
#  copyright law.
#
#  This program is free software; you can redistribute  it and/or modify it
#  under  the terms of  the GNU General  Public License as published by the
#  Free Software Foundation;  either version 2 of the  License, or (at your
#  option) any later version.
#
#  THIS  SOFTWARE  IS  PROVIDED  ``AS  IS''  AND   ANY  EXPRESS  OR IMPLIED
#  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
#  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
#  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
#  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  You should have received a copy of the  GNU General Public License along
#  with this program; if not, write  to the Free Software Foundation, Inc.,
#  675 Mass Ave, Cambridge, MA 02139, USA.
#$L$


.PHONY: build chkconfig preconfig buildfs clean

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

# Build the base file system, install the toolchain libraries
build: 
	# We install all the applications during the normal build process, but only
	# if the FSROOT directory already exists, otherwise we may break the detection
	# for running the buildfs target if required, because we will create the FSROOT ahead of time
	if [ -d $(FSROOT) ] ; then \
	    $(MAKE) buildfs ; \
	fi

buildfs:
	$(V) mkdir -p $(FSROOT)/{lib,usr/bin}
	# Installing the dynamic loader
	$(V) install -D --mode=755 $(TOOLCHAIN_LIB)/ld-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libc
	$(V) install -D --mode=755 $(TOOLCHAIN_LIB)/libc-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libdl
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libdl-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libgcc
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libgcc_s.so.1 \
	    $(FSROOT)/lib/
	# Installing shared libm
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libm-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libnsl
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libnsl-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libnss (minimals, compat,files,dns)
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libnss_compat-2.8.so \
	    $(FSROOT)/lib/
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libnss_dns-2.8.so \
	    $(FSROOT)/lib/
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libnss_files-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libpthread
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libpthread-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libresolv
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libresolv-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libutil
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libutil-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared libcrypt
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libcrypt-2.8.so \
	    $(FSROOT)/lib/
	# Installing shared librt
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/librt-2.8.so \
	    $(FSROOT)/lib/
	# Installing others
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libBrokenLocale-2.8.so \
	    $(FSROOT)/lib/
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libanl-2.8.so \
	    $(FSROOT)/lib/
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libcidn-2.8.so \
	    $(FSROOT)/lib/

ifeq ($(CONFIG_TOOLCHAIN_INSTALL_CPP_SUPPORT),y)
	# Installing shared libstdc++ and friends
	$(V) install -D --mode=755 $(TOOLCHAIN_LIB)/../usr/lib/libstdc++.so.6.0.10 \
	    $(FSROOT)/lib/libstdc++.so.6.0.10
endif

ifeq ($(CONFIG_TOOLCHAIN_INSTALL_GCONV_MODULES),y)
	# Installing GCONV conversion tables required to use iconv utility
	$(V) mkdir -p $(FSROOT)/usr/lib/gconv
	$(V) install -D --mode=755 $(TOOLCHAIN_LIB)/../usr/lib/gconv/* $(FSROOT)/usr/lib/gconv/
endif

ifeq ($(CONFIG_TOOLCHAIN_INSTALL_GDBSERVER),y)
	# Installing gdbserver
	$(V)install -D --mode=755 $(TOOLCHAIN_BIN)/gdbserver $(FSROOT)/usr/bin/gdbserver
	$(V)install -D --mode=755 $(TOOLCHAIN_LIB)/libthread_db-1.0.so \
	    $(FSROOT)/lib/libthread_db-1.0.so
endif
ifeq ($(CONFIG_TOOLCHAIN_INSTALL_LDD),y)
	# Installing ldd
	$(V)install -D --mode=755 $(TOOLCHAIN_BIN)/ldd $(FSROOT)/usr/bin/ldd
endif

preconfig:

patch:

cmdline:

unpatch:

clean: 

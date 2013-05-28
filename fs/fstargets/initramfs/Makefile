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
#  675 Mass Ave, Cambrid5ge, MA 02139, USA.
#$L$


.PHONY: build

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

build:
	# Building a initramfs image
	$(V) test -f $(FSROOT)/init || ln -s /sbin/init $(FSROOT)/init 
	$(V) $(ECHO) Re-genering the kernel image with the initramfs
	$(V) if grep -q CONFIG_INITRAMFS_SOURCE=\"\" $(DEVDIR)/bsp/mach/bspconfig ; then \
	    sed -i -e "s?CONFIG_INITRAMFS_SOURCE=.*?CONFIG_INITRAMFS_SOURCE=\"$(FSROOT)\"?" $(DEVDIR)/bsp/mach/bspconfig ;\
	    echo "CONFIG_INITRAMFS_ROOT_UID=0" >> $(DEVDIR)/bsp/mach/bspconfig ;\
	    echo "CONFIG_INITRAMFS_ROOT_GID=0" >> $(DEVDIR)/bsp/mach/bspconfig ;\
	else \
	    $(ECHO) WARNING: Your variable CONFIG_INITRAMFS_SOURCE is not empty on the kernel configuration ; \
	    touch not_restore ; \
	fi
	$(V)$(ECHO) Building the initramfs from `grep CONFIG_INITRAMFS_SOURCE $(DEVDIR)/bsp/mach/bspconfig | cut -d'=' -f2`
	$(V) $(MAKE) -C $(DEVDIR)/kernel
	$(V) if [ -f not_restore ] ; then \
	    rm not_restore ; \
	else \
	    sed -i -e "s?CONFIG_INITRAMFS_SOURCE=.*?CONFIG_INITRAMFS_SOURCE=\"\"?" $(DEVDIR)/bsp/mach/bspconfig ; \
	    sed -i -e "s?CONFIG_INITRAMFS_ROOT_UID=0??" $(DEVDIR)/bsp/mach/bspconfig ; \
	    sed -i -e "s?CONFIG_INITRAMFS_ROOT_GID=0??" $(DEVDIR)/bsp/mach/bspconfig ; \
	fi


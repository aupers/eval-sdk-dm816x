#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
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


.PHONY: build cmdline

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

ifeq ($(CONFIG_INSTALLER_MODE_SD_CARD),y)
# We probably have a partition for kernel (and maybe bootloader) that is the first one
 TARGET_SD_ROOTFS_DEVICE?=/dev/mmcblk0p2
else
# We assume the SD card is all for the root fs
 TARGET_SD_ROOTFS_DEVICE?=/dev/mmcblk0p1
endif

build:

cmdline:
ifeq ($(CONFIG_FS_TARGET_SD),y)
	$(V)echo -n "root=$(TARGET_SD_ROOTFS_DEVICE) rootdelay=2 " >>$(CMDLINEFILE)
  ifeq ($(CONFIG_INSTALLER_SD_ROOTFS_TYPE_EXT3),y)
	$(V)echo -n "rootfstype=ext3 " >>$(CMDLINEFILE)
  else
	$(V)$(ECHO) "$(WARN_COLOR)Warning:$(NORMAL_COLOR) not defining boot parameters for SD card root fs since we don't know what fs type you have... I hope you know what you are doing!"
  endif
endif

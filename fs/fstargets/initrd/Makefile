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


.PHONY: build cmdline

ifeq ($(DEVDIR),)
$(error ====== DEVDIR variable is empty, invoke this Makefile from the BSP root, or provide the path to it =====)
endif
include $(DEVDIR)/bsp/mach/Make.conf

MKFSEXT2 = mkfs.ext2
FSCKEXT2 = fsck.ext2
GZIP	 = gzip
TMPIMAGE = image.tmp
TMPMNT	= ${shell pwd}/tmp

build:
	# Building a initrd image
ifeq ($(CONFIG_FS_TARGET_INITRD_EXT2),y)
	$(ECHO) Building EXT2 filesystem...
	# We duplicate the size of the filesystem leave some free space and the
	# expenses of metadata (which is around 60% for a small file system)
	$(V)$(SUDO) umount $(TMPMNT) 2>/dev/null ; true #With this true it never complains on failure
	$(V)dd if=/dev/zero of=$(TMPIMAGE) bs=8096 count=`du -s -B 4096 $(FSROOT) | cut -f1` $(QOUT) 2>>$(LOGFILE)
	$(V)$(MKFSEXT2) -F $(TMPIMAGE) $(QOUT) 2>>$(LOGFILE)
	$(V)mkdir -p $(TMPMNT)
	$(V)$(SUDO) mount -o loop $(TMPIMAGE) $(TMPMNT) 
	$(V)echo -n -e "$(TABINDEX)  " ; cd $(FSROOT) && find . | $(SUDO) cpio -pdum $(TMPMNT)
	$(V)$(SUDO) umount $(TMPMNT) 2>/dev/null ; true #With this true it never complains on failure
	$(V)$(FSCKEXT2) -n $(TMPIMAGE) $(QOUT) 2>>$(LOGFILE)
	$(V)$(GZIP) -c -9 $(TMPIMAGE) >initrd
	$(V)cp initrd $(DEVDIR)/images $(QOUT)
	$(V)ln -sf initrd $(FSIMAGE) $(QOUT)
endif
#ifeq ($(CONFIG_FS_TARGET_INITRD_CRAMFS),y)
#endif

cmdline:
	$(V)echo -n "root=/dev/ram0 rw " >>$(CMDLINEFILE)

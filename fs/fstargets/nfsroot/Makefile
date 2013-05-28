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

IFACE_NAME?=$(CONFIG_INSTALLER_HOST_NET_INTERFACE)
HOST_IP ?= $(shell ifconfig $(IFACE_NAME) | head -2 | tail -1 | cut -f 2 -d: | cut -f 1 -d' ')

ifeq ($(CONFIG_BSP_NET_HAS_ETH0),y)
INTERFACE=eth0
endif
ifeq ($(CONFIG_BSP_NET_HAS_USB0),y)
INTERFACE=usb0
endif

build:
	$(ECHO) Selected NFS root filesystem...
	$(V) $(SUDO) chmod -R a+w $(FSROOT)
	$(ECHO) Please check the directory $(FSROOT) is on your nfs-server exports file
	$(V) rm -rf $(FSIMAGE)
	$(V) touch $(FSIMAGE)

cmdline:
	$(V)echo -n "root=/dev/nfs nfsroot=$(HOST_IP):$(FSROOT) rw ip=" >>$(CMDLINEFILE)
ifneq ($(CONFIG_BSP_NET_ETH0_USE_DHCP),y)
	$(V)echo -n "$(CONFIG_BSP_NET_ETH0_IPADDR):::$(CONFIG_BSP_NET_ETH0_NETMASK)::$(INTERFACE) " >>$(CMDLINEFILE)
else
	$(V)echo -n "dhcp " >>$(CMDLINEFILE)
endif
ifeq ($(CONFIG_IPV6),y)
	$(V)$(ECHO) "$(WARN_COLOR)WARNING:$(NORMAL_COLOR) You have IPv6 builtin support in your kernel and booting via NFS root, however some kernels have a bug where they won't boot from NFS root if IPv6 is enabled and no IPv6 router is available on the network. Be aware..."
endif

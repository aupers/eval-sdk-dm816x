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

include $(DEVDIR)/bsp/classes/dependencies.defs

patch: dependency_patch

build: dependency_build

preconfig:
	echo -e "# Automatic generated file by Makefile, don't edit\n\n" >ConfigExtra
	$(V)for i in `ls` ; do \
	    if [ "$$i" != ".svn" ] && [ -e $$i/Config ] ; then \
	        if grep -q "^preconfig:" $$i/Makefile ; then \
		    $(ECHO) "Entering $$i..." ; \
		    $(MAKE) -C $$i $(MAKE_CALL_PARAMS) preconfig || { exit 1 ; } ; \
		fi; \
		echo -e "source myapps/$$i/Config \n\n" >>ConfigExtra ; \
	    fi ; \
	done

unpatch: dependency_unpatch

force_build_execute: build

include $(CLASSES)/force_build.defs

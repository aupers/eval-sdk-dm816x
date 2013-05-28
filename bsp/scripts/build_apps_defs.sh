#!/bin/bash
# Copyright (C) 2007 Ridgerun (http://www.ridgerun.com). 
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

###############################################################################
# "GLOBAL VARIABLES" REPOSITORY BUILDER SCRIPT
###############################################################################
# The purprose of this script is to generate an 'includable' Makefile defi-
# nition file that provides variables representing the path to an applica-
# tion. In this way, no matter which version of an application we are using
# it is possible to access its path in a way similar to $(SOME_APP) instead
# of hardwiring the path including version numbers. 
#
# ATTENTION/WARNING/README: Don't use the variables provided in this file as 
#   substitutions for the paths in the "install:" part of the originating 
#   Makefiles. 
#
#   If you have app-1.0/Makefile and inside it there is an "install" directive 
#   with an specific path, leave it as is, because we need that line to deter-
#   mine if we must create OUTPUT, LIB or INCLUDE variables. 

CMNT_BAR="###############################################################################"
INDIVIDUAL_BANNER="# Symbols individually defined in each app Apps.defs file"

load_variables(){
# Here we scan each directory looking for individually defined symbols in the 
# file Apps.defs under each app root directory 
# $(DEVDIR)/fs/$1/some_app-version/Apps.defs. 

for i in $1/* 
 do
  $DEVDIR/bsp/scripts/metainfo -p $i -a
 done
}

# Print the results to standard out (Redirected to a file in 
# $(DEVDIR)/fs/Makefile ( > Apps.defs ).  

echo "# WARNING: Automatic generated file by Makefile, don't edit.
#
# If you wish to change the contents of this file look into the script 
# \$(DEVDIR)/bsp/scripts/build_apps_defs.sh.
#
# That script look inside each application internal Apps.defs to get other 
# defined variables and made them available to all other apps.
#"

echo 
echo $CMNT_BAR
echo $INDIVIDUAL_BANNER
echo $CMNT_BAR

for j in $@ ; do
    load_variables $j;
done
exit 0

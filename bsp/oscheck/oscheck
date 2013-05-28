#!/bin/bash
# 
# This script will try to detect the underlying Unix distribution
# and if possible its version.
#
# It is assumed that every current distribution places a file 
# in /etc, named something like /etc/distribution-release
#
# At the end of the script is a table suggested in many Linux 
# magazines and websites as a means to detect the distribution. Please 
# update every distribution detection function in the future if this
# changes some day. 
#
# Some distributions provide specific and non portable tools to extract 
# the version number with some magic, we will prefer to obtain it by 
# pure stream manipulation as standard. 
# 
# We require to detect:
# 1) the distribution name 
# 2) the release or version number
# 3) the architecture 
#
# Please provide a function appropiately named for each of the supported 
# distributions. This function will fill the $SYSTEM_ID variable. 
#
# Add the function name to the supported systems array.

# Supported systems array 
SYS_ARRAY="sys_lsb system_release"


# Empty variables declaration (As a listing of what we use)
SYSTEM=""    # Name of the system
VERSION=""   # Version number of the system
SYSTEM_ID="" # String used globally for package listings files
             # and other identification. 
ARCH_ID=""   # If it is i686 (32) or x86_64 (64)
SYSID=""     # The file with the information ($SYSTEM_ID\_$ARCH_ID)

function sys_lsb {
    if lsb_release > /dev/null 2>&1 ; then
        SYSTEM=`lsb_release -s -i | tr A-Z a-z`
        VERSION=`lsb_release -s -r`
        SYSTEM_ID=$SYSTEM-$VERSION
    fi
}

function system_release {
    if [ -f /etc/system-release ] ; then
	SYSTEM=`cat /etc/system-release | cut -d' ' -f1`
	VERSION=`cat /etc/system-release | cut -d' ' -f3`
	SYSTEM_ID=$SYSTEM-$VERSION
    fi
}

# Check if the architecture is i686 or x86_64, short term and easily to
# change if ARM or PowerPC takes over the world next week. Or if 
# something as bizarre as i786 happens. i586 is a Pentium II from 1999.
function archcheck {
 if uname -a | grep i686 > /dev/null
  then ARCH_ID="32"
 elif uname -a | grep x86_64 > /dev/null
  then ARCH_ID="64"
 else
  echo "ERROR: Architecture not supported (Not i686 or x86_64 detected with uname)"
  exit
 fi
}

# This function will execute each of the tests until it finds a supported
# system. If no supported system is found, the string "unsupported" will 
# appear in the file $DEVDIR/.system.id
function distrocheck {
 echo "unsupported" > $DEVDIR/.system.id 
 for distribution in $SYS_ARRAY
 do 
  $distribution 
  if test -n "$SYSTEM_ID"
  then 
   break
  fi
 done
}

usage="
usage: oscheck [-d]
  -d  enable debug output
"

while getopts  ":d" options
do
 case $options in
  d ) set -x;;
  * ) echo "$usage"
   exit 1;;
 esac
done


# Execute archcheck
archcheck

# Execute distrocheck
distrocheck

# Save system identification in $DEVDIR/.system.id
if test -n $SYSTEM_ID && test -n $ARCH_ID
 then SYSID=`echo $SYSTEM_ID\_$ARCH_ID`
 echo $SYSID > $DEVDIR/.system.id
 echo $SYSTEM > $DEVDIR/.distro.id
fi 

# What we found
echo "The system is $SYSTEM_ID running in a $ARCH_ID bit architecture"
echo "SYSID: $SYSID"

# Query SYSID file and check for necessary files 
# alias:package1 package2:required
# required = [1,0]
#for i in `grep :1$ $DEVDIR/bsp/oscheck/$SYSID`
#do 
# echo $i | sed -e "s/:.*//"
#done

# Distribution release files table. 
# Use as reference, and update as appropiate
#Annvix:                         /etc/annvix-release
#Arch Linux:                     /etc/arch-release
#Arklinux:                       /etc/arklinux-release
#Aurox Linux:                    /etc/aurox-release
#BlackCat:                       /etc/blackcat-release
#Cobalt:                         /etc/cobalt-release
#Conectiva:                      /etc/conectiva-release
#Debian:                         /etc/debian_version, /etc/debian_release (rare)
#Fedora Core:                    /etc/fedora-release
#Gentoo Linux:                   /etc/gentoo-release
#Immunix:                        /etc/immunix-release
#Knoppix:                        knoppix_version (?????)
#Linux-From-Scratch:             /etc/lfs-release
#Linux-PPC:                      /etc/linuxppc-release
#Mandrake:                       /etc/mandrake-release
#Mandriva/Mandrake Linux:        /etc/mandriva-release, /etc/mandrake-release, /etc/mandakelinux-release
#MkLinux:                        /etc/mklinux-release
#Novell Linux Desktop:           /etc/nld-release
#PLD Linux:                      /etc/pld-release
#Red Hat:                        /etc/redhat-release, /etc/redhat_version (rare)
#Slackware:                      /etc/slackware-version, /etc/slackware-release (rare)
#SME Server (Formerly E-Smith):  /etc/e-smith-release
#Solaris SPARC:                  /etc/release
#Sun JDS:                        /etc/sun-release
#SUSE Linux:                     /etc/SuSE-release, /etc/novell-release
#SUSE Linux ES9:                 /etc/sles-release
#Tiny Sofa:                      /etc/tinysofa-release
#TurboLinux:                     /etc/turbolinux-release
#Ubuntu Linux:                   /etc/lsb-release
#UltraPenguin:                   /etc/ultrapenguin-release
#UnitedLinux:                    /etc/UnitedLinux-release (covers SUSE SLES8)
#VA-Linux/RH-VALE:               /etc/va-release
#Yellow Dog:                     /etc/yellowdog-release 

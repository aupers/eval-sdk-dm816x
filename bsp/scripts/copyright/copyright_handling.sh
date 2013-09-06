#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

#! /bin/bash

# fail after something went wrong
set -e

# ensure DEVDIR is set
if ! [ -n "${DEVDIR}" ]
then
	echo "DEVDIR is not set"
	exit 1
fi

# cmdline arguments
readonly OUTPUT="components.xml"

if ! [ -n "${OUTPUT}" ]
then
	echo "usage: ${0} <output-file.xml>"
	exit 1
fi
readonly OUTPUT_TMP=`mktemp`

# some constants
readonly BSP_CONFIG="${DEVDIR}/bsp/mach/bspconfig"
readonly MAKE_CONF="${DEVDIR}/bsp/mach/Make.conf"
readonly APP_DIRS="fs/apps proprietary myapps"
readonly KERNEL="copyrights"
readonly BOOTLOADER=`grep -E --max-count=1 "^\s*BOOTLOADER\s*[\?:]?=" $MAKE_CONF | cut -d "=" -f 2`
readonly TOOLCHAIN=`grep -E --max-count=1 "^\s*TOOLCHAIN\s*[\?:]?=" $MAKE_CONF | cut -d "=" -f 2`

# create empty list of all software components
COMPONENTS=""

# add kernel, bootloader and toolchain
COMPONENTS="$COMPONENTS ${DEVDIR}/kernel/$KERNEL ${DEVDIR}/bootloader/$BOOTLOADER/copyrights ${DEVDIR}/toolchain/$TOOLCHAIN"

# find all apps and libs in the SDK
APPS=""
for APP_DIR in ${APP_DIRS}
do
	APPS="$APPS `find "${DEVDIR}/${APP_DIR}" -mindepth 1 -maxdepth 1 \( -type d -or -type l \) -and -not -name "\.svn" | sort`"
done

# check, which apps & libs are selected (in bspconfig)
for APP in $APPS
do
	if ${DEVDIR}/bsp/scripts/metainfo -c -p $APP
	then			
		COMPONENTS="$COMPONENTS $APP"
	else
		COMPONENTS="$COMPONENTS"
	fi
done

# sort components
TMP_FILE=`mktemp`
for COMPONENT in $COMPONENTS
do
	echo $COMPONENT >> $TMP_FILE
done
COMPONENTS=`sort $TMP_FILE`
rm $TMP_FILE
 
# generate XML file
echo '<?xml version="1.0" encoding="UTF-8"?>' > "${OUTPUT_TMP}"
echo '<!DOCTYPE components [' >> "${OUTPUT_TMP}"
echo -n '<!ENTITY % components SYSTEM "' >> "${OUTPUT_TMP}"
pushd . >/dev/null
cd "`dirname ${0}`"
echo -n "$PWD/components.dtd" >> "${OUTPUT_TMP}"
popd > /dev/null
echo '" >' >> "${OUTPUT_TMP}"
echo '%components;' >> "${OUTPUT_TMP}"

# iterate over all selected copyrights.xml and add them to the output XML file
I=0
for COMPONENT in $COMPONENTS
do
	FILE="$COMPONENT/copyrights.xml"
	if [ -r "$FILE" ]
	then
		echo "<!ENTITY component$I SYSTEM \"$FILE\">" >> "${OUTPUT_TMP}"
	else
		echo "*** WARNING: $FILE is missing ***"
	fi
	I=$(( I + 1 ))
done

echo ']>' >> "${OUTPUT_TMP}"
echo '<components>' >> "${OUTPUT_TMP}"
I=0
for COMPONENT in $COMPONENTS
do
	FILE=$COMPONENT/copyrights.xml
	if test -r $FILE
	then
		echo "&component$I;" >> "${OUTPUT_TMP}"
	fi
	I=$(( I + 1 ))
done
echo '</components>' >> "${OUTPUT_TMP}"

# check generated XML file
# echo "check syntax"
if ! xmllint --valid "${OUTPUT_TMP}" > /dev/null
then
	rm -f "${OUTPUT_TMP}"
	echo "*** WARNING: the generated XML (${OUTPUT_TMP}) file is invalid"
fi

# done, let's rename the generated file
if ! mv -f "${OUTPUT_TMP}" "${OUTPUT}"
then
	echo "*** WARNING: failed to rename ${OUTPUT_TMP} -> ${OUTPUT}"
fi

# Eliminate SysVinit copyrights
#sed -i '/sysvinit/d' ${OUTPUT}

# create empty list of all html files
HTMLS=""

# add all html files
HTMLS="$HTMLS copyrights copyrights-short copyrights-pico summary table soup"

# create the install directory
readonly INSTALL_DIR="${DEVDIR}/fs/fs/usr/share/copyrights"
mkdir -p ${INSTALL_DIR}

# create the html files and install them in $(FSROOT)/usr/share
for HTML in $HTMLS
do
	xsltproc -o $HTML.html  $HTML.xsl $OUTPUT
	cp $HTML.html ${INSTALL_DIR}
	rm $HTML.html
done

exit 0


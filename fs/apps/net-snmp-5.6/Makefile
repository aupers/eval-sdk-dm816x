#$L$
# Copyright (C) 2011 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://voxel.dl.sourceforge.net/project/net-snmp/net-snmp/5.6.1.1/
PKG_TARBALL=net-snmp-5.6.1.1.tar.gz
PKG_SHA1SUM=ec88ba3e0dff4d1b3d342ccebb48ea84c9fa6fa9

AUTOTOOLS_PARAMS=--with-mibdirs="/usr/share/snmp/mibs:/usr/share:" --enable-ipv6  --enable-mfd-rewrites \
		--with-default-snmp-version="3" --with-sys-contact="Vicon" \
		--with-sys-location="megapixel dome unit" --with-logfile="/var/log/snmpd.log" \
		--with-persistent-directory="/var/net-snmp"

BINARIES= /usr/bin/{net-snmp-config,net-snmp-create-v3-user,snmpget,snmpgetnext,snmpset,snmpusm} \
	/usr/bin/{snmpwalk,snmpbulkwalk,snmptable,snmptrap,snmpbulkget,snmptranslate,snmpstatus} \
	/usr/bin/{snmpdelta,snmptest,encode_keychange,snmpdf,agentxtrap,snmpvacm,snmpnetstat} \
	/usr/bin/{snmpcheck,traptoemail,net-snmp-cert} \
	/usr/sbin/{snmpd,snmptrapd}

LIBRARIES= /usr/lib/{libnetsnmpagent.so.25.0.2,libnetsnmphelpers.so.25.0.2,libnetsnmpmibs.so.25.0.2} \
	/usr/lib/{libnetsnmp.so.25.0.2,libnetsnmptrapd.so.25.0.2,libnetsnmpagent.so.25,libnetsnmphelpers.so.25} \
	/usr/lib/{libnetsnmpmibs.so.25,libnetsnmp.so.25,libnetsnmptrapd.so.25}

EXTRA_FILES = /usr/share/snmp

AUTOTOOLS_BUILD_DIR=src

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


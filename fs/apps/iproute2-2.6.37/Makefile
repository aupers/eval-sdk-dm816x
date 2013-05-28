#$L$
# Copyright (C) 2012 Ridgerun (http://www.ridgerun.com). 
##$L$

PKG_URL=http://pkgs.fedoraproject.org/repo/pkgs/iproute/iproute2-2.6.37.tar.bz2/9774ff9d74ebd301bf56bd8d74473786/
PKG_TARBALL=iproute2-2.6.37.tar.bz2
PKG_SHA1SUM=7852fb66fb745dc3c1fabee24d7d8ff017c48d36

AUTOTOOLS_CLONE_SOURCE=yes
export DESTDIR=$(FSDEVROOT)

OTHERS= /etc/iproute2/{ematch_map,rt_dsfield,rt_protos,rt_realms,rt_scopes,rt_tables}
BINARIES=   /sbin/{genl,ifcfg,ifstat,ip,lnstat,nstat,routef,routel,rtacct} \
	    /sbin/{rtmon,rtpr,rtstat,ss,tc}
LIBRARIES=  /usr/lib/tc/{experimental.dist,normal.dist,pareto.dist,paretonormal.dist}
DIRECTORIES= lib/tc

include ../../../bsp/classes/rrsdk.class
include $(CLASSES)/autotools.class


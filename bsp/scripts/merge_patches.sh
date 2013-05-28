#!/bin/bash

if [ ! -f series ] ; then
    exit 0;
fi

# Check ARCH
if [ -f patches/arch/series ] ; then
    SERIESORIG=patches/arch/series
else
    SERIESORIG=/dev/null
fi
if ! $DEVDIR/bsp/scripts/find_section.pl \
    "## ARCH SERIES ##" "## END OF ARCH SERIES ##" < series | \
    sed "s?^arch/\(.*\)?\1?" | \
    diff -q $SERIESORIG - > /dev/null ; then
    echo -e "  Merging patches back from series into patches/arch/series"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## ARCH SERIES ##" "## END OF ARCH SERIES ##" < series | \
        sed "s?^arch/\(.*\)?\1?" > patches/arch/series
fi

# Check MACH
if [ -f patches/mach/series ] ; then
    SERIESORIG=patches/mach/series
else
    SERIESORIG=/dev/null
fi
if [ -f patches/mach/series ] &&
    ! $DEVDIR/bsp/scripts/find_section.pl \
    "## MACH SERIES ##" "## END OF MACH SERIES ##" < series | \
    sed "s?^mach/\(.*\)?\1?" | \
    diff -q $SERIESORIG - > /dev/null ; then
    echo -e "  Merging patches back from series into patches/mach/series"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## MACH SERIES ##" "## END OF MACH SERIES ##" < series | \
        sed "s?^mach/\(.*\)?\1?" > patches/mach/series
fi

# Check PLATFORM independent
if [ -f patches/series ] ; then
    SERIESORIG=patches/series
else
    SERIESORIG=/dev/null
fi
if [ -f patches/series ] &&
    ! $DEVDIR/bsp/scripts/find_section.pl \
    "## SERIES ##" "#END OF SERIES FILE" < series | \
    diff -q $SERIESORIG - > /dev/null; then
    echo -e "  Merging patches back from series into patches/series"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## SERIES ##" "#END OF SERIES FILE" < series > patches/series
fi

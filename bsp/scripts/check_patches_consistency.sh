#!/bin/bash

if [ "$FORCE" = "1" ] || [ ! -f series ] ; then
    exit 0;
fi

# Check ARCH
if [ -f patches/arch/series ] &&
    ! $DEVDIR/bsp/scripts/find_section.pl \
    "## ARCH SERIES ##" "## END OF ARCH SERIES ##" < series | \
    sed "s?^arch/\(.*\)?\1?" | \
    diff -q patches/arch/series - > /dev/null ; then
    echo -e "\n  ${WARN_COLOR}Warning:$GREEN You have modifications to your architecture patches!$NORMAL_COLOR"
    echo -e "  Differences are:\n"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## ARCH SERIES ##" "## END OF ARCH SERIES ##" < series | \
        sed "s?^arch/\(.*\)?\1?" | \
        diff -up patches/arch/series -
    echo -e "\n  You can either lose these changes setting the environment variable FORCE=1 or run:\n  ${GREEN}make patch_refresh$NORMAL_COLOR\n  to update your changes back into the arch series\n\n"
    exit -1;
fi

# Check MACH
if [ -f patches/mach/series ] &&
    ! $DEVDIR/bsp/scripts/find_section.pl \
    "## MACH SERIES ##" "## END OF MACH SERIES ##" < series | \
    sed "s?^mach/\(.*\)?\1?" | \
    diff -q patches/mach/series - > /dev/null ; then
    echo -e "\n  ${WARN_COLOR}Warning:$GREEN You have modifications to your machine patches!$NORMAL_COLOR"
    echo -e "  Differences are:\n"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## MACH SERIES ##" "## END OF MACH SERIES ##" < series | \
        sed "s?^mach/\(.*\)?\1?" | \
        diff -up patches/mach/series -
    echo -e "\n  You can either lose these changes setting the environment variable FORCE=1 or run:\n  ${GREEN}make patch_refresh$NORMAL_COLOR\n  to update your changes back into the mach series\n\n"
    exit -1;
fi

# Check PLATFORM independent
if [ -f patches/series ] &&
    ! $DEVDIR/bsp/scripts/find_section.pl \
    "## SERIES ##" "#END OF SERIES FILE" < series | \
    diff -q patches/series - > /dev/null; then
    echo -e "\n  ${WARN_COLOR}Warning:$GREEN You have modifications to your patches!$NORMAL_COLOR"
    echo -e "  Differences are:\n"
    $DEVDIR/bsp/scripts/find_section.pl \
        "## SERIES ##" "#END OF SERIES FILE" < series | \
        diff -up patches/series -
    echo -e "\n  You can either lose these changes setting the environment variable FORCE=1 or run:\n  ${GREEN}make patch_refresh$NORMAL_COLOR\n  to update your changes back into the series\n\n"
    exit -1;
fi


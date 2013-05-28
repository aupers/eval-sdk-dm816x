AC_INIT([hello_vala],[1.0],[support@ridgerun.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

AM_PROG_VALAC([0.7.7])

dnl Check for pkgconfig first
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, yes, no)

dnl Give error and exit if we don't have pkgconfig
if test "x$HAVE_PKGCONFIG" = "xno"; then
  AC_MSG_ERROR(you need to have pkgconfig installed !)
fi

dnl Now we're ready to ask for glib
PKG_CHECK_MODULES(GOBJECT, gobject-2.0 >= 2.16.0, HAVE_GOBJECT=yes, HAVE_GOBJECT=no)

dnl Give error and exit if we don't have directfb
if test "x$HAVE_GOBJECT" = "xno"; then
  AC_MSG_ERROR([you need glib development packages installed >= 2.16.0 !])
fi

dnl append GOBJECT_ERROR cflags to GOBJECT_CFLAGS
GOBJECT_CFLAGS="$GOBJECT_CFLAGS $GOBJECT_ERROR"

dnl make GOBJECT_CFLAGS and GOBJECT_LIBS available
AC_SUBST(GOBJECT_CFLAGS)
AC_SUBST(GOBJECT_LIBS)

AC_OUTPUT




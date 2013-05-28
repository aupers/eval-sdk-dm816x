AC_INIT([hello-libgstc],[1.0],[support@ridgerun.com])
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
PKG_CHECK_MODULES(LIBGSTC, libgstc >= 0.8 , HAVE_LIBGSTC=yes, HAVE_LIBGSTC=no)

dnl Give error and exit if we don't have directfb
if test "x$HAVE_LIBGSTC" = "xno"; then
  AC_MSG_ERROR([you need libgstc installed >= 0.8 !])
fi

dnl make DBUS_GLIB_CFLAGS and DBUS_GLIB_LIBS available
AC_SUBST(LIBGSTC_CFLAGS)
AC_SUBST(LIBGSTC_LIBS)

AC_OUTPUT

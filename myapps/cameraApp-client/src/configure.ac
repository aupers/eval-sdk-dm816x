AC_INIT([cameraApp-client],[1.0],[support@ridgerun.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

dnl Check for pkgconfig first
AC_CHECK_PROG(HAVE_PKGCONFIG, pkg-config, yes, no)

dnl Give error and exit if we don't have pkgconfig
if test "x$HAVE_PKGCONFIG" = "xno"; then
  AC_MSG_ERROR(you need to have pkgconfig installed !)
fi

dnl Now we're ready to ask for libgstcam
PKG_CHECK_MODULES(LIBGSTCAM, libgstcam >= 1.0 , HAVE_LIBGSTCAM=yes, HAVE_LIBGSTCAM=no)

dnl Give error and exit if we don't have libgstcam
if test "x$HAVE_LIBGSTCAM" = "xno"; then
  AC_MSG_ERROR([you need libgstcam installed >= 1.0 !])
fi

dnl make LIBGSTCAM_CFLAGS and LIBGSTCAM_LIBS available
AC_SUBST(LIBGSTCAM_CFLAGS)
AC_SUBST(LIBGSTCAM_LIBS)

AC_OUTPUT

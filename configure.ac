AC_INIT([LESS CSS Compiler], [1.0], [bram@vanderkroef.net], [clessc], [https://github.com/BramvdKroef/clessc])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CXX
AC_PROG_RANLIB
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

# C++11 support
AX_CXX_COMPILE_STDCXX_11()

# libpng support
AC_ARG_WITH([libpng],
  [AS_HELP_STRING([--without-libpng],
    [Compile without libpng])])

AS_IF([test "x$with_libpng" != "xno"], [
  PKG_CHECK_MODULES([LIBPNG], [libpng >= 1.2],
    [AC_DEFINE(WITH_LIBPNG, 1, [Compile with libpng])],
    [AC_MSG_FAILURE(
        [libpng not found, use configure with --without-libpng to disable
        png support])]
  )
])
    
# libjpeg support
AC_ARG_WITH([libjpeg],
  [AS_HELP_STRING([--without-libjpeg],
    [Compile without libjpeg])])

LIBJPEG_LIBS=
AS_IF([test "x$with_libjpeg" != "xno"], [
  AC_CHECK_LIB([jpeg], [jpeg_mem_src],
    [AC_CHECK_HEADER([jpeglib.h],
        [],
        [AC_MSG_FAILURE([libjpeg headers were not found in the compiler's include path.])])
     AC_SUBST([LIBJPEG_LIBS], ["-ljpeg"])
     AC_DEFINE(WITH_LIBJPEG, 1, [Compile with libjpeg])],
    [AC_MSG_FAILURE(
        [libjpeg not found, use configure with --without-libjpeg to disable
        jpeg support])]
  )
])

# google glog support
AC_ARG_WITH([libglog],
  [AS_HELP_STRING([--without-libglog],
    [Compile without libglog])])

AS_IF([test "x$with_libglog" != "xno"], [
  PKG_CHECK_MODULES([LIBGLOG], [libglog >= 0.3],
    [AC_DEFINE(WITH_LIBGLOG, 1, [Compile with libglog])],
    [AC_MSG_FAILURE(
        [libglog not found, use configure with --without-libglog to disable
        glog support (glog is only needed for debugging)])]
  )
])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
])
AC_OUTPUT

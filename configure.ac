AC_PREREQ([2.59])
AC_INIT([lierolibre C++], [0.1], [martinerikwerner@gmail.com], [lierolibre], [https://gitorious.org/lierolibre])
AC_CONFIG_SRCDIR([worm.cpp])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

LT_INIT
AM_INIT_AUTOMAKE([1.10 -Wall subdir-objects])

# Checks for programs.
AC_PROG_CPP
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AC_CHECK_PROG(HAS_SOX, sox, yes)
if test x"$HAS_SOX" != x"yes" ; then
	AC_MSG_WARN(SoX not found, you will need this to build the sound data!)
fi

AC_CHECK_PROG(HAS_IM, convert, yes)
if test x"$HAS_IM" != x"yes" ; then
	AC_MSG_WARN([ImageMagick not found, you will need this to build the graphics data!])
fi

# Checks for libraries.
LIBRT=""
	AC_CHECK_LIB(rt, clock_gettime, [LIBRT="-lrt"])
AC_SUBST(LIBRT)

SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION, :, \
	 AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

PKG_CHECK_MODULES([DEPS], [libconfig++ SDL_mixer])
PKG_CHECK_MODULES([GVL_DEPS], [zlib])

dnl Get libgvl library and include locations
AC_ARG_WITH([gvl-include-path],
	[AS_HELP_STRING([--with-gvl-include-path],
    		[location of the gvl headers, defaults to ./glv/])],
	[GVL_CPPFLAGS="-I$withval"],
	[GVL_CPPFLAGS='-I./gvl/'])
AC_SUBST([GVL_CFLAGS])
AC_ARG_WITH([gvl-lib-path],
	[AS_HELP_STRING([--with-gvl-lib-path],
		[location of the gvl libraries, defaults to ./gvl/])],
	[GVL_LIBS="-L$withval -lgvl"],
	[GVL_LIBS='-L./gvl/ -lgvl'])
AC_SUBST([GVL_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h fenv.h float.h limits.h malloc.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime floor gethostbyname localeconv memmove memset mkdir munmap pow select setenv socket sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT


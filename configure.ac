AC_PREREQ([2.59])
AC_INIT([lierolibre C++], [0.4], [martinerikwerner@gmail.com], [lierolibre], [https://gitorious.org/lierolibre])
AC_CONFIG_SRCDIR([src/worm.cpp])
AC_CONFIG_MACRO_DIR([src/m4])
AC_CONFIG_AUX_DIR([src/build-aux])
AC_CONFIG_HEADERS([src/config.h])

LT_INIT
AM_INIT_AUTOMAKE([1.10 -Wall subdir-objects])

AC_DEFINE_UNQUOTED([PACKAGE_CAPTION],
	["$PACKAGE_TARNAME $PACKAGE_VERSION"],
	[Caption for SDL window])

# Checks for programs.
AC_PROG_CPP
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_CHECK_PROG(HAS_SOX, sox, yes)
if test x"$HAS_SOX" != x"yes" ; then
	AC_MSG_WARN([SoX not found, you will need this to build the sound data!])
fi

AC_CHECK_PROG(HAS_IM, convert, yes)
if test x"$HAS_IM" != x"yes" ; then
	AC_MSG_WARN([ImageMagick not found, you will need this to build the graphics data!])
fi

# Checks for libraries.
BOOST_PO_LIBS=""
AC_LANG_PUSH([C++])
	AC_CHECK_HEADER([boost/program_options.hpp],
	[BOOST_PO_LIBS="-lboost_program_options"],
	[AC_MSG_WARN([boost_program_options header not found, you will need this to compile lierolibre!])])
AC_LANG_POP([C++])
AC_SUBST(BOOST_PO_LIBS)

LIBRT=""
	AC_CHECK_LIB(rt, clock_gettime, [LIBRT="-lrt"])
AC_SUBST(LIBRT)

SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION, :, \
	 AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

PKG_CHECK_MODULES([LIBCONFIGXX], [libconfig++])

PKG_CHECK_MODULES([SDL_MIXER], [SDL_mixer],
	[SDL_MIXER_CFLAGS=`pkg-config --cflags SDL_mixer` \
	SDL_MIXER_LIBS=`pkg-config --libs SDL_mixer`],
	[pkgcSDLM="no"])

# Fall back on a quite stupid header check if pkg-config doesn't work
# (pkg-config for SDL_mixer is relatively new)
AS_IF([test "x$pkgcSDLM" = "xno"], [
	AC_CHECK_HEADERS([SDL/SDL_mixer.h],
		[SDL_MIXER_CFLAGS="-D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL"],
		[AC_MSG_WARN([SDL_mixer headers not found, you will need this to compile lierolibre!])])
	AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio,
		[SDL_MIXER_LIBS="-lSDL_mixer -lSDL"],
		[AC_MSG_WARN([SDL_mixer library not found, you will need this to link lierolibre!])])
	])

PKG_CHECK_MODULES([ZLIB], [zlib])

# Get libgvl library and include locations
AC_ARG_WITH([gvl-include-path],
	[AS_HELP_STRING([--with-gvl-include-path],
    		[location of the gvl headers, defaults to ./src/glv/])],
	[GVL_CPPFLAGS="-I$withval"],
	[GVL_CPPFLAGS='-I./src/gvl/'])
AC_SUBST([GVL_CFLAGS])
AC_ARG_WITH([gvl-lib-path],
	[AS_HELP_STRING([--with-gvl-lib-path],
		[location of the gvl libraries, defaults to ./src/gvl/])],
	[GVL_LIBS="-L$withval -lgvl"],
	[GVL_LIBS='-L./src/gvl/ -lgvl'])
AC_SUBST([GVL_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h fenv.h float.h limits.h malloc.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/socket.h unistd.h])

AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([tut/tut.hpp tut/tut_reporter.hpp tut/tut_restartable.hpp],
	[],
	[AC_MSG_NOTICE([libtut headers not found, you will need these to compile gvltest])])
AC_LANG_POP([C++])

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

# Relative path for portable packages with accompanying libs
AC_ARG_ENABLE([relpath],
  AC_HELP_STRING([--enable-relpath], [add lib/ to the runtime library search path]),
  [want_relative=yes], [want_relative=no])
if test "$want_relative" = yes; then
  RELPATH_CFLAGS='-DUSE_RELATIVE_PATHS'
  RELPATH_LDFLAGS="-Wl,-rpath -Wl,\\\$\$ORIGIN/lib"
fi
AC_SUBST([RELPATH_CFLAGS])
AC_SUBST([RELPATH_LDFLAGS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT


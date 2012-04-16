AC_INIT([Liero C++], [1.40], [martinerikwerner@gmail.com], [liero], [https://gitorious.org/liero])
AC_PREREQ([2.59])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

dnl Need libtool for boost.m4 :(
LT_INIT
AM_INIT_AUTOMAKE([1.10 -Wall no-define subdir-objects])

AC_CONFIG_FILES([Makefile])
AC_PROG_CPP
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O

dnl Check for SDL
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION, :, \
	 AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))

dnl Check for Boost
BOOST_REQUIRE
BOOST_FILESYSTEM
BOOST_SYSTEM

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
  [AS_HELP_STRING([--with-gvl-lib-path], [location of the gvl libraries, defaults to ./gvl/])],
  [GVL_LIBS="-L$withval -lgvl"],
  [GVL_LIBS='-L./gvl/ -lgvl'])
AC_SUBST([GVL_LIBS])

AC_OUTPUT

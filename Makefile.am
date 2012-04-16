ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

dist_noinst_SCRIPTS = autogen.sh Jamfile gvl/Jamfile

bin_PROGRAMS = liero
liero_CPPFLAGS = $(DEPS_CPPFLAGS) $(GVL_CPPFLAGS) $(SDL_CPPFLAGS) \
	$(BOOST_CPPFLAGS)
liero_CFLAGS = $(DEPS_CFLAGS) $(SDL_CFLAGS) $(BOOST_CFLAGS)
liero_CXXFLAGS = $(DEPS_CXXFLAGS) $(SDL_CXXFLAGS) $(BOOST_CXXFLAGS)
liero_LDFLAGS = $(BOOST_FILESYSTEM_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS)
liero_LDADD = gvl/libgvl.la
liero_LIBS = $(DEPS_LIBS) $(GVL_LIBS) $(SDL_LIBS) $(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

noinst_LTLIBRARIES = gvl/libgvl.la
gvl_libgvl_la_CPPFLAGS = $(GVL_DEPS_CPPFLAGS)
gvl_libgvl_la_CFLAGS = $(GVL_DEPS_CFLAGS)
gvl_libgvl_la_CXXFLAGS = $(GVL_DEPS_CXXFLAGS)
gvl_libgvl_la_LDFLAGS = $(GVL_DEPS_LDFLAGS)
gvl_libgvl_la_LIBS = $(GVL_DEPS)

check_PROGRAMS = gvl/gvltest

liero_SOURCES = \
	bobject.cpp bonus.cpp common.cpp console.cpp constants.cpp \
	filesystem.cpp game.cpp gfx.cpp keys.cpp level.cpp main.cpp math.cpp \
	ninjarope.cpp nobject.cpp rand.cpp reader.cpp sdlmain.cpp replay.cpp \
	settings.cpp sfx.cpp sobject.cpp sys.cpp text.cpp viewport.cpp \
	weapon.cpp weapsel.cpp worm.cpp \
	bobject.hpp bonus.hpp common.hpp console.hpp constants.hpp \
	filesystem.hpp game.hpp gfx.hpp keys.hpp level.hpp math.hpp \
	nobject.hpp rand.hpp reader.hpp replay.hpp settings.hpp sfx.hpp \
	sobject.hpp sys.hpp text.hpp viewport.hpp weapon.hpp weapsel.hpp \
	worm.hpp exactObjectList.hpp fastObjectList.hpp lfs.hpp \
	objectList.hpp version.hpp rect.hpp\
	\
	dataPath.cpp  binReader.cpp to_string.cpp configHelper.cpp \
	configInit.cpp \
	dataPath.hpp  binReader.hpp to_string.hpp configHelper.hpp \
	configInit.hpp \
	\
	controller/commonController.cpp controller/localController.cpp \
	controller/replayController.cpp \
	controller/commonController.hpp controller/localController.hpp \
	controller/replayController.hpp controller/controller.hpp \
	\
	gfx/blit.cpp gfx/font.cpp gfx/palette.cpp gfx/sprite.cpp \
	gfx/blit.hpp gfx/font.hpp gfx/palette.hpp gfx/sprite.hpp \
	gfx/color.hpp gfx/macros.hpp \
	\
	menu/booleanSwitchBehavior.cpp menu/enumBehavior.cpp \
	menu/hiddenMenu.cpp menu/integerBehavior.cpp menu/itemBehavior.cpp \
	menu/menu.cpp menu/menuItem.cpp menu/timeBehavior.cpp \
	menu/booleanSwitchBehavior.hpp menu/enumBehavior.hpp \
	menu/hiddenMenu.hpp menu/integerBehavior.hpp menu/itemBehavior.hpp \
	menu/arrayEnumBehavior.hpp \
	menu/menu.hpp menu/menuItem.hpp menu/timeBehavior.hpp

gvl_libgvl_la_SOURCES = \
	containers/list.cpp \
	\
	crypt/curve25519.cpp \
	\
	io/stream.cpp \
	io/encoding.cpp \
	io/convert.cpp \
	\
	\
	math/ieee.cpp \
	math/tt800.cpp \
	math/fdlibm/e_acos.c \
	math/fdlibm/e_acosh.c \
	math/fdlibm/e_asin.c \
	math/fdlibm/e_atan2.c \
	math/fdlibm/e_atanh.c \
	math/fdlibm/e_cosh.c \
	math/fdlibm/e_exp.c \
	math/fdlibm/e_fmod.c \
	math/fdlibm/e_gamma.c \
	math/fdlibm/e_gamma_r.c \
	math/fdlibm/e_hypot.c \
	math/fdlibm/e_j0.c \
	math/fdlibm/e_j1.c \
	math/fdlibm/e_jn.c \
	math/fdlibm/e_lgamma.c \
	math/fdlibm/e_lgamma_r.c \
	math/fdlibm/e_log.c \
	math/fdlibm/e_log10.c \
	math/fdlibm/e_pow.c \
	math/fdlibm/e_remainder.c \
	math/fdlibm/e_rem_pio2.c \
	math/fdlibm/e_scalb.c \
	math/fdlibm/e_sinh.c \
	math/fdlibm/e_sqrt.c \
	math/fdlibm/k_cos.c \
	math/fdlibm/k_rem_pio2.c \
	math/fdlibm/k_sin.c \
	math/fdlibm/k_standard.c \
	math/fdlibm/k_tan.c \
	math/fdlibm/s_asinh.c \
	math/fdlibm/s_atan.c \
	math/fdlibm/s_cbrt.c \
	math/fdlibm/s_ceil.c \
	math/fdlibm/s_copysign.c \
	math/fdlibm/s_cos.c \
	math/fdlibm/s_erf.c \
	math/fdlibm/s_expm1.c \
	math/fdlibm/s_fabs.c \
	math/fdlibm/s_finite.c \
	math/fdlibm/s_floor.c \
	math/fdlibm/s_frexp.c \
	math/fdlibm/s_ilogb.c \
	math/fdlibm/s_isnan.c \
	math/fdlibm/s_ldexp.c \
	math/fdlibm/s_lib_version.c \
	math/fdlibm/s_log1p.c \
	math/fdlibm/s_logb.c \
	math/fdlibm/s_matherr.c \
	math/fdlibm/s_modf.c \
	math/fdlibm/s_nextafter.c \
	math/fdlibm/s_rint.c \
	math/fdlibm/s_scalbn.c \
	math/fdlibm/s_signgam.c \
	math/fdlibm/s_significand.c \
	math/fdlibm/s_sin.c \
	math/fdlibm/s_tan.c \
	math/fdlibm/s_tanh.c \
	math/fdlibm/w_acos.c \
	math/fdlibm/w_acosh.c \
	math/fdlibm/w_asin.c \
	math/fdlibm/w_atan2.c \
	math/fdlibm/w_atanh.c \
	math/fdlibm/w_cosh.c \
	math/fdlibm/w_exp.c \
	math/fdlibm/w_fmod.c \
	math/fdlibm/w_gamma.c \
	math/fdlibm/w_gamma_r.c \
	math/fdlibm/w_hypot.c \
	math/fdlibm/w_j0.c \
	math/fdlibm/w_j1.c \
	math/fdlibm/w_jn.c \
	math/fdlibm/w_lgamma.c \
	math/fdlibm/w_lgamma_r.c \
	math/fdlibm/w_log.c \
	math/fdlibm/w_log10.c \
	math/fdlibm/w_pow.c \
	math/fdlibm/w_remainder.c \
	math/fdlibm/w_scalb.c \
	math/fdlibm/w_sinh.c \
	math/fdlibm/w_sqrt.c \
	\
	resman/shared.cpp \
	\
	sockets/fd_set.cpp \
	sockets/sockets.cpp \
	sockets/socketstream.cpp \
	\
	support/bits.c \
	support/debug.cpp \
	support/hash.cpp \
	support/log.cpp \
	support/profile.cpp \
	\
	system/system.c \
	\
	tut/quickcheck/context.cpp

gvl_gvltest_SOURCES = \
	gvl_test/containers/list.cpp \
	gvl_test/containers/pairing_heap.cpp \
	gvl_test/containers/treap.cpp \
	gvl_test/io/bitstream.cpp \
	gvl_test/io/stream.cpp \
	gvl_test/support/bits.cpp \
	gvl_test/math/deterministic_float.cpp \
	gvl_test/test.cpp


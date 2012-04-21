ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

dist_noinst_SCRIPTS = autogen.sh Jamfile gvl/Jamfile

LIEROLIBRE = lierolibre
LIBGVL = gvl/libgvl.la
GVLTEST = gvl/gvltest

bin_PROGRAMS = $(LIEROLIBRE)
lierolibre_CPPFLAGS = $(GVL_CPPFLAGS) $(SDL_CPPFLAGS)
lierolibre_CFLAGS = $(DEPS_CFLAGS) $(SDL_CFLAGS)
lierolibre_CXXFLAGS = $(SDL_CXXFLAGS)
lierolibre_LDADD = $(LIBGVL) $(DEPS_LIBS) $(SDL_LIBS)

noinst_LTLIBRARIES = $(LIBGVL)
gvl_libgvl_la_CFLAGS = $(GVL_DEPS_CFLAGS)
gvl_libgvl_la_LIBADD = $(GVL_DEPS_LIBS)

check_PROGRAMS = $(GVLTEST)
gvl_gvltest_CFLAGS = $(GVL_DEPS_CFLAGS)
gvl_gvltest_LDFLAGS = $(GVL_DEPS_LIBS) $(LIBRT)
gvl_gvltest_LDADD = $(LIBGVL)

lierolibre_SOURCES = \
	binReader.cpp \
	bobject.cpp \
	bonus.cpp \
	common.cpp \
	console.cpp \
	constants.cpp \
	filesystem.cpp \
	game.cpp \
	gfx.cpp \
	keys.cpp \
	level.cpp \
	main.cpp \
	math.cpp \
	ninjarope.cpp \
	nobject.cpp \
	rand.cpp \
	reader.cpp \
	replay.cpp \
	sdlmain.cpp \
	settings.cpp \
	sfx.cpp \
	sobject.cpp \
	sys.cpp \
	text.cpp \
	viewport.cpp \
	weapon.cpp \
	weapsel.cpp \
	worm.cpp \
	\
	binReader.hpp \
	bobject.hpp \
	bonus.hpp \
	common.hpp \
	console.hpp \
	constants.hpp \
	exactObjectList.hpp \
	fastObjectList.hpp \
	filesystem.hpp \
	game.hpp \
	gfx.hpp \
	keys.hpp \
	level.hpp \
	lfs.hpp \
	math.hpp \
	nobject.hpp \
	objectList.hpp \
	rand.hpp \
	reader.hpp \
	rect.hpp\
	replay.hpp \
	settings.hpp \
	sfx.hpp \
	sobject.hpp \
	sys.hpp \
	text.hpp \
	version.hpp \
	viewport.hpp \
	weapon.hpp \
	weapsel.hpp \
	worm.hpp \
	\
	\
	configHelper.cpp \
	configInit.cpp \
	dataPath.cpp \
	to_string.cpp \
	\
	configHelper.hpp \
	configInit.hpp \
	dataPath.hpp \
	to_string.hpp \
	\
	\
	controller/commonController.cpp \
	controller/localController.cpp \
	controller/replayController.cpp \
	\
	controller/commonController.hpp \
	controller/controller.hpp \
	controller/localController.hpp \
	controller/replayController.hpp \
	\
	\
	gfx/blit.cpp \
	gfx/font.cpp \
	gfx/palette.cpp \
	gfx/sprite.cpp \
	\
	gfx/blit.hpp \
	gfx/color.hpp \
	gfx/font.hpp \
	gfx/macros.hpp \
	gfx/palette.hpp \
	gfx/sprite.hpp \
	\
	\
	menu/booleanSwitchBehavior.cpp \
	menu/enumBehavior.cpp \
	menu/hiddenMenu.cpp \
	menu/integerBehavior.cpp \
	menu/itemBehavior.cpp \
	menu/menu.cpp \
	menu/menuItem.cpp \
	menu/timeBehavior.cpp \
	\
	menu/arrayEnumBehavior.hpp \
	menu/booleanSwitchBehavior.hpp \
	menu/enumBehavior.hpp \
	menu/hiddenMenu.hpp \
	menu/integerBehavior.hpp \
	menu/itemBehavior.hpp \
	menu/menu.hpp \
	menu/menuItem.hpp \
	menu/timeBehavior.hpp

gvl_libgvl_la_SOURCES = \
	gvl/containers/list.cpp \
	\
	gvl/containers/list.hpp \
	gvl/containers/bucket.hpp \
	gvl/containers/string.hpp \
	gvl/containers/list.h \
	\
	\
	gvl/crypt/curve25519.cpp \
	gvl/crypt/curve25519.hpp \
	\
	\
	gvl/io/stream.cpp \
	gvl/io/encoding.cpp \
	gvl/io/convert.cpp \
	\
	gvl/io/stream.hpp \
	gvl/io/fstream.hpp \
	gvl/io/iostream.hpp \
	gvl/io/encoding.hpp \
	gvl/io/convert.hpp \
	\
	\
	gvl/math/ieee.cpp \
	gvl/math/tt800.cpp \
	\
	gvl/math/ieee.hpp \
	gvl/math/tt800.hpp \
	gvl/math/cmwc.hpp \
	gvl/math/random.hpp \
	\
	\
	gvl/meta/as_unsigned.hpp \
	\
	\
	gvl/resman/shared.cpp \
	\
	gvl/resman/shared_ptr.hpp \
	gvl/resman/shared.hpp \
	gvl/resman/shared_count.hpp \
	\
	\
	gvl/sockets/fd_set.cpp \
	gvl/sockets/sockets.cpp \
	gvl/sockets/socketstream.cpp \
	\
	gvl/sockets/fd_set.hpp \
	gvl/sockets/sockets.hpp \
	gvl/sockets/sockets_sys_impl.hpp \
	gvl/sockets/socketstream.hpp \
	\
	\
	gvl/support/bits.c \
	gvl/support/debug.cpp \
	gvl/support/hash.cpp \
	gvl/support/log.cpp \
	gvl/support/profile.cpp \
	\
	gvl/support/functional.hpp \
	gvl/support/profile.hpp \
	gvl/support/hash.hpp \
	gvl/support/debug.hpp \
	gvl/support/log.hpp \
	gvl/support/macros.hpp \
	gvl/support/platform.hpp \
	gvl/support/cstdint.hpp \
	gvl/support/type_info.hpp \
	gvl/support/platform.h \
	gvl/support/opt.hpp \
	gvl/support/bits.hpp \
	gvl/support/flags.hpp \
	gvl/support/algorithm.hpp \
	\
	\
	gvl/system/system.c \
	\
	gvl/system/system.hpp \
	\
	\
	gvl/tut/quickcheck/context.cpp \
	\
	gvl/tut/quickcheck/context.hpp \
	gvl/tut/quickcheck/generator.hpp

gvl_gvltest_SOURCES = \
	gvl/gvl_test/containers/list.cpp \
	gvl/gvl_test/containers/pairing_heap.cpp \
	gvl/gvl_test/containers/treap.cpp \
	gvl/gvl_test/io/bitstream.cpp \
	gvl/gvl_test/io/stream.cpp \
	gvl/gvl_test/support/bits.cpp \
	gvl/gvl_test/math/deterministic_float.cpp \
	gvl/gvl_test/test.cpp \
	\
	\
	gvl/list.hpp \
	\
	\
	gvl/math/cmwc.hpp \
	\
	\
	gvl/support/algorithm.hpp \
	gvl/support/macros.hpp \
	\
	\
	gvl/tut/tut.hpp \
	gvl/tut/quickcheck/context.hpp \
	gvl/tut/quickcheck/generator.hpp \
	gvl/tut/quickcheck/property.hpp

#EXTRA_gvl_libgvl_la_SOURCES = \
#	gvl/containers/buffer.cpp \
#	gvl/containers/critbit.cpp \
#	gvl/containers/accurate_rectangle_packing.hpp \
#	gvl/containers/avl_tree.hpp \
#	gvl/containers/bounded_rectangle_packing.hpp \
#	gvl/containers/bucket.hpp \
#	gvl/containers/buffer.hpp \
#	gvl/containers/compact_interval_set.hpp \
#	gvl/containers/critbit.hpp \
#	gvl/containers/deque.hpp \
#	gvl/containers/generic_hash_set.hpp \
#	gvl/containers/hash_map.hpp \
#	gvl/containers/hash_set.hpp \
#	gvl/containers/int_set.hpp \
#	gvl/containers/iterator.hpp \
#	gvl/containers/linked_vector.hpp \
#	gvl/containers/list3.hpp \
#	gvl/containers/node_base.hpp \
#	gvl/containers/pairing_heap.hpp \
#	gvl/containers/pod_vector.hpp \
#	gvl/containers/range.hpp \
#	gvl/containers/string.hpp \
#	gvl/containers/treap.hpp \
#	gvl/containers/treap2.hpp \
#	gvl/containers/xlist.hpp

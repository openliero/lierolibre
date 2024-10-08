ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I src/m4

appicondir = $(datarootdir)/icons/hicolor/scalable/apps
desktopdir = $(datarootdir)/applications

# For sedding in wrapper script later on
CFGFILE = liero.cfg

# For nixbin-dist
PACKAGE_DIRNAME = $(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
NIXBIN_DIRNAME = $(PACKAGE_DIRNAME)_linux-$(build_cpu)

pkglibexec_PROGRAMS = lierolibre
# It seems it only includes src/../ by default
lierolibre_CPPFLAGS = $(LIBCONFIGXX_CPPFLAGS) $(GVL_CPPFLAGS) $(SDL_CPPFLAGS) -I$(srcdir)/src $(WINDOWS_CPPFLAGS)
lierolibre_CFLAGS = $(LIBCONFIGXX_CFLAGS) $(SDL_MIXER_CFLAGS) $(SDL_CFLAGS) $(RELPATH_CFLAGS)
lierolibre_CXXFLAGS = $(SDL_CXXFLAGS) $(RELPATH_CFLAGS)
lierolibre_LDADD = src/gvl/libgvl.la $(LIBCONFIGXX_LIBS) $(SDL_MIXER_LIBS) $(SDL_LIBS) $(BOOST_PO_LIBS)
lierolibre_LDFLAGS = $(RELPATH_LDFLAGS) $(WINDOWS_LDFLAGS)

noinst_LTLIBRARIES = src/gvl/libgvl.la
src_gvl_libgvl_la_CFLAGS = $(ZLIB_CFLAGS) $(RELPATH_CFLAGS)
src_gvl_libgvl_la_LIBADD = $(ZLIB_LIBS)
src_gvl_libgvl_la_LDFLAGS = $(RELPATH_LDFLAGS)

EXTRA_PROGRAMS = src/gvl/gvltest
src_gvl_gvltest_CFLAGS = $(ZLIB_CFLAGS) $(RELPATH_CFLAGS)
src_gvl_gvltest_LDFLAGS = $(ZLIB_LIBS) $(LIBRT) $(RELPATH_LDFLAGS)
src_gvl_gvltest_LDADD = src/gvl/libgvl.la

nodist_bin_SCRIPTS = \
	scripts/lierolibre

dist_bin_SCRIPTS = \
	scripts/lierolibre-extractgfx \
	scripts/lierolibre-packgfx \
	scripts/lierolibre-extractsounds \
	scripts/lierolibre-packsounds \
	scripts/lierolibre-extractlev \
	scripts/lierolibre-packlev

dist_noinst_SCRIPTS = \
	autogen.sh \
	scripts/cross-compile \
	scripts/lierolibre.am \
	src/Jamfile \
	src/dummy_config.h \
	src/gvl/Jamfile

nodist_man6_MANS = \
	man/lierolibre.6 \
	man/lierolibre-extractgfx.6 \
	man/lierolibre-packgfx.6 \
	man/lierolibre-extractsounds.6 \
	man/lierolibre-packsounds.6 \
	man/lierolibre-extractlev.6 \
	man/lierolibre-packlev.6

# For nixbin
MANS_TXT = $(nodist_man6_MANS:.6=.txt)

dist_doc_DATA = \
	AUTHORS \
	ChangeLog \
	NEWS \
	README

dist_desktop_DATA = \
	data/lierolibre.desktop

dist_appicon_DATA = \
	data/lierolibre.svg

dist_pkgdata_DATA = \
	data/LIERO.CHR \
	data/LIERO.DAT \
	data/LIERO.OPT \
	data/LIERO.SND \
	data/NAMES.DAT \
	data/liero.cfg

MANPAGES_SOURCES = \
	man/lierolibre.6.am \
	man/lierolibre-extractgfx.6.am \
	man/lierolibre-packgfx.6.am \
	man/lierolibre-extractsounds.6.am \
	man/lierolibre-packsounds.6.am \
	man/lierolibre-extractlev.6.am \
	man/lierolibre-packlev.6.am

GRAPHICS_SOURCES = \
	data/graphics/gfx1.xpm \
	data/graphics/gfx2.xpm \
	data/graphics/gfx3.xpm

SOUND_SOURCES = \
	data/sounds/ALIVE.wav \
	data/sounds/BAZOOKA.wav \
	data/sounds/BEGIN.wav \
	data/sounds/BLASTER.wav \
	data/sounds/BOING.wav \
	data/sounds/BUMP.wav \
	data/sounds/BURNER.wav \
	data/sounds/DEATH1.wav \
	data/sounds/DEATH2.wav \
	data/sounds/DEATH3.wav \
	data/sounds/DIRT.wav \
	data/sounds/DROPSHEL.wav \
	data/sounds/EXP2.wav \
	data/sounds/EXP3.wav \
	data/sounds/EXP3A.wav \
	data/sounds/EXP3B.wav \
	data/sounds/EXP4.wav \
	data/sounds/EXP5.wav \
	data/sounds/HURT1.wav \
	data/sounds/HURT2.wav \
	data/sounds/HURT3.wav \
	data/sounds/LARPA.wav \
	data/sounds/MOVEDOWN.wav \
	data/sounds/MOVEUP.wav \
	data/sounds/RELOADED.wav \
	data/sounds/RIFLE.wav \
	data/sounds/SELECT.wav \
	data/sounds/SHOT.wav \
	data/sounds/SHOTGUN.wav \
	data/sounds/THROW.wav

WINDOWS_SOURCES = \
	scripts/lierolibre-cmd.bat \
	src/gvl/_build/Gvl_C++0x.props \
	src/gvl/_build/Gvl_IEEE_SEE2.props \
	src/gvl/_build/Gvl_Standard_Config.props \
	src/gvl/_build/gvl.vcproj \
	src/gvl/_build/gvl.vcxproj \
	src/gvl/_build/gvl.vcxproj.filters \
	windows/visualC/liero.vcproj \
	windows/visualC/liero.vcxproj \
	windows/visualC/lierolibre.sln

dist_noinst_DATA = \
	$(GRAPHICS_SOURCES) \
	$(MANPAGES_SOURCES) \
	$(SOUND_SOURCES) \
	$(WINDOWS_SOURCES) \
	COPYING \
	COPYING_winbin \
	README.txt \
	README_linuxbin \
	data/FILE_ID.DIZ \
	data/LICENSE.TXT \
	data/LIERO.TXT \
	data/LIEROENG.TXT \
	data/lierolibre.xpm \
	data/sounds/sounds.txt \
	lgpl-2.1.txt \
        TODO

lierolibre_SOURCES = \
	src/binReader.cpp \
	src/bobject.cpp \
	src/bonus.cpp \
	src/common.cpp \
	src/console.cpp \
	src/constants.cpp \
	src/filesystem.cpp \
	src/game.cpp \
	src/gfx.cpp \
	src/keys.cpp \
	src/level.cpp \
	src/main.cpp \
	src/math.cpp \
	src/ninjarope.cpp \
	src/nobject.cpp \
	src/rand.cpp \
	src/reader.cpp \
	src/replay.cpp \
	src/sdlmain.cpp \
	src/settings.cpp \
	src/sfx.cpp \
	src/sobject.cpp \
	src/sys.cpp \
	src/text.cpp \
	src/viewport.cpp \
	src/weapon.cpp \
	src/weapsel.cpp \
	src/worm.cpp \
	\
	src/binReader.hpp \
	src/bobject.hpp \
	src/bonus.hpp \
	src/common.hpp \
	src/console.hpp \
	src/constants.hpp \
	src/exactObjectList.hpp \
	src/fastObjectList.hpp \
	src/filesystem.hpp \
	src/game.hpp \
	src/gfx.hpp \
	src/keys.hpp \
	src/level.hpp \
	src/lfs.hpp \
	src/math.hpp \
	src/nobject.hpp \
	src/objectList.hpp \
	src/rand.hpp \
	src/reader.hpp \
	src/rect.hpp\
	src/replay.hpp \
	src/settings.hpp \
	src/sfx.hpp \
	src/sobject.hpp \
	src/sys.hpp \
	src/text.hpp \
	src/version.hpp \
	src/viewport.hpp \
	src/weapon.hpp \
	src/weapsel.hpp \
	src/worm.hpp \
	\
	\
	src/argParse.cpp \
	src/configCompat.cpp \
	src/configHelper.cpp \
	src/configInit.cpp \
	src/dataPath.cpp \
	src/to_string.cpp \
	\
	src/argParse.hpp \
	src/configHelper.hpp \
	src/configInit.hpp \
	src/dataPath.hpp \
	src/to_string.hpp \
	\
	\
	src/controller/commonController.cpp \
	src/controller/localController.cpp \
	src/controller/replayController.cpp \
	\
	src/controller/commonController.hpp \
	src/controller/controller.hpp \
	src/controller/localController.hpp \
	src/controller/replayController.hpp \
	\
	\
	src/gfx/blit.cpp \
	src/gfx/font.cpp \
	src/gfx/palette.cpp \
	src/gfx/sprite.cpp \
	\
	src/gfx/blit.hpp \
	src/gfx/color.hpp \
	src/gfx/font.hpp \
	src/gfx/macros.hpp \
	src/gfx/palette.hpp \
	src/gfx/sprite.hpp \
	\
	\
	src/menu/booleanSwitchBehavior.cpp \
	src/menu/enumBehavior.cpp \
	src/menu/hiddenMenu.cpp \
	src/menu/integerBehavior.cpp \
	src/menu/itemBehavior.cpp \
	src/menu/menu.cpp \
	src/menu/menuItem.cpp \
	src/menu/timeBehavior.cpp \
	\
	src/menu/arrayEnumBehavior.hpp \
	src/menu/booleanSwitchBehavior.hpp \
	src/menu/enumBehavior.hpp \
	src/menu/hiddenMenu.hpp \
	src/menu/integerBehavior.hpp \
	src/menu/itemBehavior.hpp \
	src/menu/menu.hpp \
	src/menu/menuItem.hpp \
	src/menu/timeBehavior.hpp

src_gvl_libgvl_la_SOURCES = \
	src/gvl/containers/list.cpp \
	\
	src/gvl/containers/list.hpp \
	src/gvl/containers/bucket.hpp \
	src/gvl/containers/string.hpp \
	src/gvl/containers/list.h \
	\
	\
	src/gvl/crypt/curve25519.cpp \
	src/gvl/crypt/curve25519.hpp \
	\
	\
	src/gvl/io/stream.cpp \
	src/gvl/io/encoding.cpp \
	src/gvl/io/convert.cpp \
	\
	src/gvl/io/stream.hpp \
	src/gvl/io/fstream.hpp \
	src/gvl/io/iostream.hpp \
	src/gvl/io/encoding.hpp \
	src/gvl/io/convert.hpp \
	\
	\
	src/gvl/math/ieee.cpp \
	src/gvl/math/tt800.cpp \
	\
	src/gvl/math/ieee.hpp \
	src/gvl/math/tt800.hpp \
	src/gvl/math/cmwc.hpp \
	src/gvl/math/random.hpp \
	\
	\
	src/gvl/meta/as_unsigned.hpp \
	\
	\
	src/gvl/resman/shared.cpp \
	\
	src/gvl/resman/shared_ptr.hpp \
	src/gvl/resman/shared.hpp \
	src/gvl/resman/shared_count.hpp \
	\
	\
	src/gvl/sockets/fd_set.cpp \
	src/gvl/sockets/sockets.cpp \
	src/gvl/sockets/socketstream.cpp \
	\
	src/gvl/sockets/fd_set.hpp \
	src/gvl/sockets/sockets.hpp \
	src/gvl/sockets/sockets_sys_impl.hpp \
	src/gvl/sockets/socketstream.hpp \
	\
	\
	src/gvl/support/bits.c \
	src/gvl/support/debug.cpp \
	src/gvl/support/hash.cpp \
	src/gvl/support/log.cpp \
	src/gvl/support/profile.cpp \
	\
	src/gvl/support/functional.hpp \
	src/gvl/support/profile.hpp \
	src/gvl/support/hash.hpp \
	src/gvl/support/debug.hpp \
	src/gvl/support/log.hpp \
	src/gvl/support/macros.hpp \
	src/gvl/support/platform.hpp \
	src/gvl/support/cstdint.hpp \
	src/gvl/support/type_info.hpp \
	src/gvl/support/platform.h \
	src/gvl/support/opt.hpp \
	src/gvl/support/bits.hpp \
	src/gvl/support/flags.hpp \
	src/gvl/support/algorithm.hpp \
	\
	\
	src/gvl/system/system.c \
	\
	src/gvl/system/system.hpp \
	\
	\
	src/gvl/tut/quickcheck/context.cpp \
	\
	src/gvl/tut/quickcheck/context.hpp \
	src/gvl/tut/quickcheck/generator.hpp

src_gvl_gvltest_SOURCES = \
	src/gvl/gvl_test/containers/list.cpp \
	src/gvl/gvl_test/containers/pairing_heap.cpp \
	src/gvl/gvl_test/containers/treap.cpp \
	src/gvl/gvl_test/io/bitstream.cpp \
	src/gvl/gvl_test/io/stream.cpp \
	src/gvl/gvl_test/support/bits.cpp \
	src/gvl/gvl_test/math/deterministic_float.cpp \
	src/gvl/gvl_test/test.cpp \
	\
	\
	src/gvl/containers/list.hpp \
	src/gvl/containers/list.h \
	\
	\
	src/gvl/io/iostream.hpp
	\
	\
	src/gvl/list.hpp \
	\
	\
	src/gvl/math/cmwc.hpp \
	src/gvl/math/random.hpp \
	src/gvl/math/ieee.hpp \
	\
	\
	src/gvl/resman/shared_ptr.hpp \
	src/gvl/resman/shared.hpp \
	src/gvl/resman/shared_count.hpp \
	\
	\
	src/gvl/support/algorithm.hpp \
	src/gvl/support/macros.hpp \
	src/gvl/support/functional.hpp \
	src/gvl/support/debug.hpp \
	src/gvl/support/platform.hpp \
	src/gvl/support/platform.h \
	src/gvl/support/cstdint.hpp \
	src/gvl/support/type_info.hpp \
	\
	\
	src/gvl/tut/quickcheck/context.hpp \
	src/gvl/tut/quickcheck/generator.hpp \
	src/gvl/tut/quickcheck/property.hpp

# Just everything in a bunch, some bits are unused currently
# but I'm ignorant so I'm bloating the archive.
EXTRA_DIST = \
	src/gvl/containers/buffer.cpp \
	src/gvl/containers/critbit.cpp \
	src/gvl/containers/list.cpp \
	src/gvl/containers/tests/deque.cpp \
	src/gvl/containers/tests/hash_set.cpp \
	src/gvl/containers/tests/list.cpp \
	src/gvl/containers/tests/pairing_heap.cpp \
	src/gvl/containers/tests/treap.cpp \
	src/gvl/crypt/curve25519.cpp \
	src/gvl/gvl_test/_build/deque.cpp \
	src/gvl/gvl_test/containers/accurate_rectangle_packing.cpp \
	src/gvl/gvl_test/containers/bounded_rectangle_packing.cpp \
	src/gvl/gvl_test/containers/compact_interval_set.cpp \
	src/gvl/gvl_test/containers/dense_int_set.cpp \
	src/gvl/gvl_test/containers/hash_set.cpp \
	src/gvl/gvl_test/containers/list.cpp \
	src/gvl/gvl_test/containers/pairing_heap.cpp \
	src/gvl/gvl_test/containers/string.cpp \
	src/gvl/gvl_test/containers/treap.cpp \
	src/gvl/gvl_test/io/bitstream.cpp \
	src/gvl/gvl_test/io/formatter.cpp \
	src/gvl/gvl_test/io/stream.cpp \
	src/gvl/gvl_test/math/deterministic_float.cpp \
	src/gvl/gvl_test/math/random.cpp \
	src/gvl/gvl_test/support/bits.cpp \
	src/gvl/gvl_test/support/opt.cpp \
	src/gvl/gvl_test/test.cpp \
	src/gvl/io/convert.cpp \
	src/gvl/io/device_buf.cpp \
	src/gvl/io/encoding.cpp \
	src/gvl/io/stream.cpp \
	src/gvl/io/tests/bitstream.cpp \
	src/gvl/io/tests/stream.cpp \
	src/gvl/math/ieee.cpp \
	src/gvl/math/tests/reproducible_floats.cpp \
	src/gvl/math/tt800.cpp \
	src/gvl/resman/shared.cpp \
	src/gvl/sockets/fd_set.cpp \
	src/gvl/sockets/socket_listener.cpp \
	src/gvl/sockets/sockets.cpp \
	src/gvl/sockets/socketstream.cpp \
	src/gvl/support/bits.c \
	src/gvl/support/debug.cpp \
	src/gvl/support/hash.cpp \
	src/gvl/support/log.cpp \
	src/gvl/support/platform.cpp \
	src/gvl/support/profile.cpp \
	src/gvl/support/string_pool.cpp \
	src/gvl/support/tests/bits.cpp \
	src/gvl/system/mutex.c \
	src/gvl/system/system.c \
	src/gvl/test/gvl_tests.cpp \
	src/gvl/text/util.cpp \
	src/gvl/tut/quickcheck/context.cpp \
	\
	src/gvl/containers/accurate_rectangle_packing.hpp \
	src/gvl/containers/avl_tree.hpp \
	src/gvl/containers/bounded_rectangle_packing.hpp \
	src/gvl/containers/bucket.hpp \
	src/gvl/containers/buffer.hpp \
	src/gvl/containers/compact_interval_set.hpp \
	src/gvl/containers/critbit.hpp \
	src/gvl/containers/deque.hpp \
	src/gvl/containers/generic_hash_set.hpp \
	src/gvl/containers/hash_map.hpp \
	src/gvl/containers/hash_set.hpp \
	src/gvl/containers/int_set.hpp \
	src/gvl/containers/iterator.hpp \
	src/gvl/containers/linked_vector.hpp \
	src/gvl/containers/list.h \
	src/gvl/containers/list.hpp \
	src/gvl/containers/list3.hpp \
	src/gvl/containers/node_base.hpp \
	src/gvl/containers/pairing_heap.hpp \
	src/gvl/containers/pod_vector.hpp \
	src/gvl/containers/range.hpp \
	src/gvl/containers/string.hpp \
	src/gvl/containers/treap.hpp \
	src/gvl/containers/treap2.hpp \
	src/gvl/containers/xlist.hpp \
	src/gvl/crypt/curve25519.hpp \
	src/gvl/crypt/gash.hpp \
	src/gvl/crypt/gciph.hpp \
	src/gvl/cstdint.hpp \
	src/gvl/debug.hpp \
	src/gvl/dense_int_set.hpp \
	src/gvl/gvl_test/template.hpp \
	src/gvl/hash_set/generic_hash_set.hpp \
	src/gvl/hash_set/hash_set.hpp \
	src/gvl/io/bitstream.hpp \
	src/gvl/io/bitstream_old.hpp \
	src/gvl/io/bitstream_templ.hpp \
	src/gvl/io/bitstream_templ_old.hpp \
	src/gvl/io/brigade2.h \
	src/gvl/io/brigade2.hpp \
	src/gvl/io/common_bitstream.hpp \
	src/gvl/io/convert.hpp \
	src/gvl/io/deflate_filter.hpp \
	src/gvl/io/device_buf.hpp \
	src/gvl/io/devnull.hpp \
	src/gvl/io/encoding.hpp \
	src/gvl/io/encoding_compat.hpp \
	src/gvl/io/fstream.hpp \
	src/gvl/io/iostream.hpp \
	src/gvl/io/range_coder.hpp \
	src/gvl/io/stream.hpp \
	src/gvl/io/unicode.hpp \
	src/gvl/linked_hash_set.hpp \
	src/gvl/list.hpp \
	src/gvl/math/cmwc.hpp \
	src/gvl/math/float.hpp \
	src/gvl/math/ieee.hpp \
	src/gvl/math/math.hpp \
	src/gvl/math/matrix.hpp \
	src/gvl/math/normal_distribution.hpp \
	src/gvl/math/random.hpp \
	src/gvl/math/rect.hpp \
	src/gvl/math/tt800.hpp \
	src/gvl/math/vec.hpp \
	src/gvl/meta/as_unsigned.hpp \
	src/gvl/meta/is_ptr_convertible.hpp \
	src/gvl/meta/meta.hpp \
	src/gvl/meta/static_log2.hpp \
	src/gvl/resman/allocator.hpp \
	src/gvl/resman/linked_object.hpp \
	src/gvl/resman/scoped_array.hpp \
	src/gvl/resman/shared.h \
	src/gvl/resman/shared.hpp \
	src/gvl/resman/shared_count.hpp \
	src/gvl/resman/shared_list.hpp \
	src/gvl/resman/shared_ptr.hpp \
	src/gvl/serialization/archive.hpp \
	src/gvl/serialization/context.hpp \
	src/gvl/serialization/except.hpp \
	src/gvl/sockets/fd_set.hpp \
	src/gvl/sockets/socket_listener.hpp \
	src/gvl/sockets/sockets.hpp \
	src/gvl/sockets/sockets_sys_impl.hpp \
	src/gvl/sockets/socketstream.hpp \
	src/gvl/support.hpp \
	src/gvl/support/algorithm.hpp \
	src/gvl/support/align.hpp \
	src/gvl/support/bits.hpp \
	src/gvl/support/borrow.hpp \
	src/gvl/support/cheap_flags.hpp \
	src/gvl/support/config.h \
	src/gvl/support/cstdint.hpp \
	src/gvl/support/debug.hpp \
	src/gvl/support/disjoint_set.hpp \
	src/gvl/support/flags.hpp \
	src/gvl/support/foreach.hpp \
	src/gvl/support/functional.hpp \
	src/gvl/support/hash.hpp \
	src/gvl/support/log.hpp \
	src/gvl/support/macros.hpp \
	src/gvl/support/move.hpp \
	src/gvl/support/object_model.h \
	src/gvl/support/opt.hpp \
	src/gvl/support/platform.h \
	src/gvl/support/platform.hpp \
	src/gvl/support/profile.hpp \
	src/gvl/support/string_pool.hpp \
	src/gvl/support/type_info.hpp \
	src/gvl/system/memory.hpp \
	src/gvl/system/mutex.hpp \
	src/gvl/system/system.hpp \
	src/gvl/system/windows.hpp \
	src/gvl/test/gvl_tests.hpp \
	src/gvl/test/test.hpp \
	src/gvl/text/utf8.hpp \
	src/gvl/text/util.hpp \
	src/gvl/trees/node_base.hpp \
	src/gvl/tut/quickcheck/context.hpp \
	src/gvl/tut/quickcheck/generator.hpp \
	src/gvl/tut/quickcheck/property.hpp \
	src/gvl/tut/quickcheck/quickcheck.hpp \
	\
	src/boostTesting.cpp


LIB_ARCH_NIXBIN_LIBFILES = \
	lib/libcap.so.2 \
	lib/libdbus-1.so.3 \
	lib/libtinfo.so.5 \
	lib/libwrap.so.0 \
	lib/libz.so.1

USR_LIB_ARCH_NIXBIN_LIBFILES = \
	lib/libconfig++.so \
        lib/libSDL_mixer-1.2.so.0 \
        lib/libSDL-1.2.so.0 \
	lib/libmikmod.so.2 \
	lib/libvorbisfile.so.3 \
	lib/libvorbis.so.0 \
	lib/libFLAC.so.8 \
	lib/libpulse-simple.so.0 \
	lib/libpulse.so.0 \
	lib/libdirectfb-1.2.so.9 \
	lib/libfusion-1.2.so.9 \
	lib/libdirect-1.2.so.9 \
	lib/libcaca.so.0 \
	lib/libsndfile.so.1 \
	lib/libasyncns.so.0 \
	lib/libogg.so.0 \
	lib/libvorbisenc.so.2 \
	lib/libxcb.so.1 \
	lib/libX11-xcb.so.1 \
	lib/libjson.so.0

USR_LIB_NIXBIN_LIBFILES = \
	lib/libboost_program_options.so \
	lib/libmad.so.0

USR_LIB_ARCH_PA_NIXBIN_LIBFILES = \
	lib/libpulsecommon-2.0.so

NIXBIN_LIBFILES = \
	$(LIB_ARCH_NIXBIN_LIBFILES) \
	$(USR_LIB_ARCH_NIXBIN_LIBFILES) \
	$(USR_LIB_NIXBIN_LIBFILES) \
	$(LIB_NIXBIN_LIBFILES) \
	$(USR_LIB_ARCH_PA_NIXBIN_LIBFILES)

NIXBIN_LIB_DEBS = \
	libasyncns0 \
	libcaca0 \
	libconfig++9 \
	libdbus-1-3 \
	libdirectfb-1.2-9 \
	libflac8 \
	libmad0 \
	libmikmod2 \
	libpulse0 \
	libsdl-mixer1.2 \
	libsdl1.2debian \
	libsndfile1

NIXBIN_LIB_DEBS_NOSRC = \
	libboost-program-options1.49.0 \
	libcap2 \
	libjson0 \
	libncursesw5 \
	libogg0 \
	libtinfo5 \
	libvorbis0a \
	libvorbisenc2
	libvorbisfile3 \
	libwrap0 \
	libx11-xcb1 \
	libxcb1 \
	zlib1g

WINDOWS_LIBS_A = \
	windows/libconfig-1.4.8/lib/.libs/libconfig++.a

WINDOWS_LIBS_DLL = \
	windows/SDL-1.2.15/build/.libs/SDL.dll \
	windows/SDL_mixer-1.2.12/lib/x86/SDL_mixer.dll \
	windows/boost-program_options-1.51.0/stage/lib/libboost_program_options.dll \
	windows/zlib-1.2.7/zlib1.dll

WINDOWS_LIBS = $(WINDOWS_LIBS_A) $(WINDOWS_LIBS_DLL)

WINDOWS_TXT = AUTHORS COPYING ChangeLog NEWS

if HAS_WINDOWS_LDFLAGS
EXTRA_lierolibre_DEPENDENCIES = $(WINDOWS_LIBS)
endif

windows/boost-program_options-1.51.0/stage/lib/libboost_program_options.dll:
	cd windows/boost-program_options-1.51.0/ ;\
		./bootstrap.sh ;\
		rm -rf stage ;\
		rm -rf bin.v2 ;\
		./b2 --user-config=tools/build/v2/user-config_i686-w64-mingw32-gcc.jam toolset=gcc-mingw32 target-os=windows variant=release link=shared -sNO_BZIP2=1 -sNO_ZLIB=1 linkflags='-static-libgcc -static-libstdc++' stage/lib/libboost_program_options.dll stage/lib/libboost_program_options.dll.a

windows/zlib-1.2.7/zlib1.dll:
	cd windows/zlib-1.2.7/ && \
		make -f win32/Makefile.gcc PREFIX=i686-w64-mingw32-

windows/SDL-1.2.15/build/.libs/SDL.dll:
	cd windows/SDL-1.2.15/ && \
		./configure --host=i686-w64-mingw32 && \
		make LDFLAGS='-static-libgcc -static-libstdc++'

windows/libconfig-1.4.8/lib/.libs/libconfig++.a:
	cd windows/libconfig-1.4.8/ && \
		./configure --host=i686-w64-mingw32 && \
		make LDFLAGS='-static-libgcc -static-libstdc++'

if HAS_WINDOWS_LDFLAGS
dist-hook: lierolibre.exe $(WINDOWS_LIBS)
	for i in $(WINDOWS_LIBS_DLL) .libs/lierolibre.exe; do \
		$(STRIP) $$i -o $(distdir)/$$(basename $$i); \
		chmod +x $(distdir)/$$(basename $$i); done
	cp scripts/lierolibre-cmd.bat $(distdir)
	cp $(distdir)/data/liero.cfg $(distdir)/data/lierocfg.txt
	for i in $(WINDOWS_TXT); do \
		cp $(distdir)/$$i $(distdir)/$$i.txt; \
		sed 's/$$//' -i $(distdir)/$$i.txt; done
	mkdir $(distdir)/user
	mkdir $(distdir)/libsrc
	cp -r windows/SDL-1.2.15/ $(distdir)/libsrc/
	cp -r windows/libconfig-1.4.8/ $(distdir)/libsrc/
	-make -C $(distdir)/libsrc/SDL-1.2.15/ distclean
	-make -C $(distdir)/libsrc/libconfig-1.4.8/ distclean
	sed '/no longer applies./r COPYING_winbin' -i $(distdir)/COPYING.txt
	sed \
		-e '/START_MACHINE_READABLE/,/END_MACHINE_READABLE/d' \
		-e '/.*_HUMAN_READABLE/d' \
		-i $(distdir)/COPYING.txt
	sed '/         separate licenses, and not covered under the BSD-2-Clause license/r COPYING_winbin' -i $(distdir)/COPYING.txt
	sed \
		-e '/START_HUMAN_READABLE/,/END_HUMAN_READABLE/d' \
		-e '/.*_MACHINE_READABLE/d' \
		-i $(distdir)/COPYING.txt
else
dist-hook:
endif
	cp $(distdir)/src/gvl/_build/Gvl_C++0x.props \
		"$(distdir)/src/gvl/_build/Gvl C++0x.props"
	cp $(distdir)/src/gvl/_build/Gvl_IEEE_SEE2.props \
		"$(distdir)/src/gvl/_build/Gvl IEEE SEE2.props"
	cp $(distdir)/src/gvl/_build/Gvl_Standard_Config.props \
		"$(distdir)/src/gvl/_build/Gvl Standard Config.props"

$(nodist_bin_SCRIPTS): scripts/lierolibre.am
	install -d scripts/
	sed \
		-e 's,#PKGDATADIR#,$(pkgdatadir),g' \
		-e 's,#CFGFILE#,$(CFGFILE),g' \
		-e 's,#LIBEXECDIR#,$(libexecdir),g' \
		-e 's,#PACKAGE#,$(PACKAGE),g' \
		$(srcdir)/$@.am \
		> $@

$(nodist_man6_MANS): $(MANPAGES_SOURCES)
	install -d man/
	sed \
		-e 's,#PKGDATADIR#,$(pkgdatadir),g' \
		-e 's,#CFGFILE#,$(CFGFILE),g' \
		-e 's,#LIBEXECDIR#,$(libexecdir),g' \
		-e 's,#PACKAGE#,$(PACKAGE),g' \
		-e 's,#UPPERCASE_PACKAGE#,\U$(PACKAGE),g' \
		-e 's,#PACKAGE_VERSION#,$(PACKAGE_VERSION),g' \
		$(srcdir)/$@.am \
		> $@

data/LIERO.CHR: $(GRAPHICS_SOURCES)
	install -d data/
	$(srcdir)/scripts/lierolibre-packgfx \
		$(srcdir)/data/graphics/gfx{1..3}.xpm \
		$@

data/LIERO.SND: $(SOUND_SOURCES)
	install -d data/
	$(srcdir)/scripts/lierolibre-packsounds \
		$(srcdir)/data/sounds/ \
		$@

.PHONY: clean-local dist-nixbin-dir dist-nixbin-libcopyright dist-nixbin-libsrc dist-nixbin dist-nixbin-xz

clean-local:
	rm -f \
		$(nodist_bin_SCRIPTS) \
		$(nodist_man6_MANS) \
		$(MANS_TXT)
	rm -rf lib/ libsrc/

$(LIB_ARCH_NIXBIN_LIBFILES):
	install -d lib/
	NIXBIN_LIBFILE=$@ ;\
		cp -a \
		/lib/$(build_cpu)-$(build_os)/$${NIXBIN_LIBFILE#lib/}* \
		lib/ || \
		touch lib/00MISSING_$${NIXBIN_LIBFILE#lib/}

$(USR_LIB_ARCH_NIXBIN_LIBFILES):
	install -d lib/
	NIXBIN_LIBFILE=$@ ;\
		cp -a \
		/usr/lib/$(build_cpu)-$(build_os)/$${NIXBIN_LIBFILE#lib/}* \
		lib/ || \
		touch lib/00MISSING_$${NIXBIN_LIBFILE#lib/}

$(USR_LIB_NIXBIN_LIBFILES):
	install -d lib/
	NIXBIN_LIBFILE=$@ ;\
		cp -a /usr/lib/$${NIXBIN_LIBFILE#lib/}* lib/ || \
		touch lib/00MISSING_$${NIXBIN_LIBFILE#lib/}

$(LIB_NIXBIN_LIBFILES):
	install -d lib/
	NIXBIN_LIBFILE=$@ ;\
		cp -a /lib/$${NIXBIN_LIBFILE#lib/}* lib/ || \
		touch lib/00MISSING_$${NIXBIN_LIBFILE#lib/}

$(USR_LIB_ARCH_PA_NIXBIN_LIBFILES):
	install -d lib/
	NIXBIN_LIBFILE=$@ ;\
		cp -a \
		/usr/lib/$(build_cpu)-$(build_os)/pulseaudio/$${NIXBIN_LIBFILE#lib/}* \
		lib/ || \
		touch lib/00MISSING_$${NIXBIN_LIBFILE#lib/}

$(MANS_TXT): $(nodist_man6_MANS)
	man --no-justification --no-hyphenation $(@:.txt=.6) | col -b > $@
	echo >> $@
	echo "This text file was automatically generated from $(@:.txt=.6)" \
		>> $@

dist-nixbin-libcopyright:
	install -d lib/
	cd lib/ && \
		for i in $(NIXBIN_LIB_DEBS) $(NIXBIN_LIB_DEBS_NOSRC); do \
		cupt copyright $$i > $$i.copyright || \
		touch 00MISSING_$$i.copyright; done

dist-nixbin-libsrc:
	install -d libsrc/
	cd libsrc/ && \
		LANG=C apt-get source --download-only \
		$$(for i in $(NIXBIN_LIB_DEBS); do \
		echo $$i=$$(dpkg -s $$i | \
		sed -n 's/^Version:\ \(.*\)/\1/p'); done) 2>&1 >/dev/null | \
		sed -n 's/E: Unable to find a source package for \(.*\)/\1/p' | \
		xargs -I '{}' touch 00MISSING_'{}'.debsource

dist-nixbin-dir: distdir $(pkglibexec_PROGRAMS) $(NIXBIN_LIBFILES) \
		$(MANS_TXT) dist-nixbin-libcopyright dist-nixbin-libsrc
	cp -aT $(PACKAGE_DIRNAME) $(NIXBIN_DIRNAME)
	cp -a lib/ $(NIXBIN_DIRNAME)
	cp -a libsrc/ $(NIXBIN_DIRNAME)
	cp -a $(pkglibexec_PROGRAMS) $(NIXBIN_DIRNAME)
	cp -a $(nodist_man6_MANS) $(NIXBIN_DIRNAME)/man/
	cp -a $(MANS_TXT) $(NIXBIN_DIRNAME)/man/

dist-nixbin: dist-nixbin-dir
	tar caf $(NIXBIN_DIRNAME).tar.gz $(NIXBIN_DIRNAME)

dist-nixbin-xz: dist-nixbin-dir
	tar caf $(NIXBIN_DIRNAME).tar.xz $(NIXBIN_DIRNAME)


ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

appicondir = $(datadir)/icons/hicolor/scalable/apps
desktopdir = $(datadir)/applications

# For sedding in wrapper script later on
CFGFILE = liero.cfg

pkglibexec_PROGRAMS = lierolibre
lierolibre_CPPFLAGS = $(GVL_CPPFLAGS) $(SDL_CPPFLAGS)
lierolibre_CFLAGS = $(DEPS_CFLAGS) $(SDL_CFLAGS)
lierolibre_CXXFLAGS = $(SDL_CXXFLAGS)
lierolibre_LDADD = gvl/libgvl.la $(DEPS_LIBS) $(SDL_LIBS)

noinst_LTLIBRARIES = gvl/libgvl.la
gvl_libgvl_la_CFLAGS = $(GVL_DEPS_CFLAGS)
gvl_libgvl_la_LIBADD = $(GVL_DEPS_LIBS)

EXTRA_PROGRAMS = gvl/gvltest
gvl_gvltest_CFLAGS = $(GVL_DEPS_CFLAGS)
gvl_gvltest_LDFLAGS = $(GVL_DEPS_LIBS) $(LIBRT)
gvl_gvltest_LDADD = gvl/libgvl.la

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
	Jamfile \
	gvl/Jamfile \
	scripts/lierolibre.am

nodist_man6_MANS = \
	man/lierolibre.6 \
	man/lierolibre-extractgfx.6 \
	man/lierolibre-packgfx.6 \
	man/lierolibre-extractsounds.6 \
	man/lierolibre-packsounds.6 \
	man/lierolibre-extractlev.6 \
	man/lierolibre-packlev.6

dist_doc_DATA = \
	AUTHORS \
	COPYING \
	NEWS \
	README

dist_desktop_DATA = \
	data/lierolibre.desktop

dist_appicon_DATA = \
	data/lierolibre.svg

dist_pkgdata_DATA = \
	data/LIERO.DAT \
	data/LIERO.OPT \
	data/NAMES.DAT \
	data/liero.cfg

nodist_pkgdata_DATA = \
	data/LIERO.CHR \
	data/LIERO.SND

dist_noinst_DATA = \
	man/lierolibre.6.am \
	man/lierolibre-extractgfx.6.am \
	man/lierolibre-packgfx.6.am \
	man/lierolibre-extractsounds.6.am \
	man/lierolibre-packsounds.6.am \
	man/lierolibre-extractlev.6.am \
	man/lierolibre-packlev.6.am \
	\
	\
	data/lierolibre.desktop
	\
	\
	data/lierolibre.xpm \
	\
	\
	data/graphics/gfx1.xpm \
	data/graphics/gfx2.xpm \
	data/graphics/gfx3.xpm \
	\
	\
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
	gvl/containers/list.hpp \
	gvl/containers/list.h \
	\
	\
	gvl/io/iostream.hpp
	\
	\
	gvl/list.hpp \
	\
	\
	gvl/math/cmwc.hpp \
	gvl/math/random.hpp \
	gvl/math/ieee.hpp \
	\
	\
	gvl/resman/shared_ptr.hpp \
	gvl/resman/shared.hpp \
	gvl/resman/shared_count.hpp \
	\
	\
	gvl/support/algorithm.hpp \
	gvl/support/macros.hpp \
	gvl/support/functional.hpp \
	gvl/support/debug.hpp \
	gvl/support/platform.hpp \
	gvl/support/platform.h \
	gvl/support/cstdint.hpp \
	gvl/support/type_info.hpp \
	\
	\
	gvl/tut/tut.hpp \
	gvl/tut/quickcheck/context.hpp \
	gvl/tut/quickcheck/generator.hpp \
	gvl/tut/quickcheck/property.hpp

# Just everything in a bunch, some bits are unused currently
# but I'm ignorant so I'm bloating the archive.
EXTRA_DIST = \
	gvl/containers/buffer.cpp \
	gvl/containers/critbit.cpp \
	gvl/containers/list.cpp \
	gvl/containers/tests/deque.cpp \
	gvl/containers/tests/hash_set.cpp \
	gvl/containers/tests/list.cpp \
	gvl/containers/tests/pairing_heap.cpp \
	gvl/containers/tests/treap.cpp \
	gvl/crypt/curve25519.cpp \
	gvl/gvl_test/_build/deque.cpp \
	gvl/gvl_test/containers/accurate_rectangle_packing.cpp \
	gvl/gvl_test/containers/bounded_rectangle_packing.cpp \
	gvl/gvl_test/containers/compact_interval_set.cpp \
	gvl/gvl_test/containers/dense_int_set.cpp \
	gvl/gvl_test/containers/hash_set.cpp \
	gvl/gvl_test/containers/list.cpp \
	gvl/gvl_test/containers/pairing_heap.cpp \
	gvl/gvl_test/containers/string.cpp \
	gvl/gvl_test/containers/treap.cpp \
	gvl/gvl_test/io/bitstream.cpp \
	gvl/gvl_test/io/formatter.cpp \
	gvl/gvl_test/io/stream.cpp \
	gvl/gvl_test/math/deterministic_float.cpp \
	gvl/gvl_test/math/random.cpp \
	gvl/gvl_test/support/bits.cpp \
	gvl/gvl_test/support/opt.cpp \
	gvl/gvl_test/test.cpp \
	gvl/io/convert.cpp \
	gvl/io/device_buf.cpp \
	gvl/io/encoding.cpp \
	gvl/io/stream.cpp \
	gvl/io/tests/bitstream.cpp \
	gvl/io/tests/stream.cpp \
	gvl/math/dtoa.c \
	gvl/math/ieee.cpp \
	gvl/math/tests/reproducible_floats.cpp \
	gvl/math/tt800.cpp \
	gvl/resman/shared.cpp \
	gvl/sockets/fd_set.cpp \
	gvl/sockets/socket_listener.cpp \
	gvl/sockets/sockets.cpp \
	gvl/sockets/socketstream.cpp \
	gvl/support/bits.c \
	gvl/support/debug.cpp \
	gvl/support/hash.cpp \
	gvl/support/log.cpp \
	gvl/support/platform.cpp \
	gvl/support/profile.cpp \
	gvl/support/string_pool.cpp \
	gvl/support/tests/bits.cpp \
	gvl/system/mutex.c \
	gvl/system/system.c \
	gvl/test/gvl_tests.cpp \
	gvl/text/util.cpp \
	gvl/tut/quickcheck/context.cpp \
	gvl/uthread/coro.cpp \
	gvl/uthread/test.cpp \
	gvl/uthread/uthread.cpp \
	gvl/zlib/adler32.c \
	gvl/zlib/compress.c \
	gvl/zlib/crc32.c \
	gvl/zlib/deflate.c \
	gvl/zlib/example.c \
	gvl/zlib/gzio.c \
	gvl/zlib/infback.c \
	gvl/zlib/inffast.c \
	gvl/zlib/inflate.c \
	gvl/zlib/inftrees.c \
	gvl/zlib/minigzip.c \
	gvl/zlib/trees.c \
	gvl/zlib/uncompr.c \
	gvl/zlib/zutil.c \
	\
	gvl/containers/accurate_rectangle_packing.hpp \
	gvl/containers/avl_tree.hpp \
	gvl/containers/bounded_rectangle_packing.hpp \
	gvl/containers/bucket.hpp \
	gvl/containers/buffer.hpp \
	gvl/containers/compact_interval_set.hpp \
	gvl/containers/critbit.hpp \
	gvl/containers/deque.hpp \
	gvl/containers/generic_hash_set.hpp \
	gvl/containers/hash_map.hpp \
	gvl/containers/hash_set.hpp \
	gvl/containers/int_set.hpp \
	gvl/containers/iterator.hpp \
	gvl/containers/linked_vector.hpp \
	gvl/containers/list.h \
	gvl/containers/list.hpp \
	gvl/containers/list3.hpp \
	gvl/containers/node_base.hpp \
	gvl/containers/pairing_heap.hpp \
	gvl/containers/pod_vector.hpp \
	gvl/containers/range.hpp \
	gvl/containers/string.hpp \
	gvl/containers/treap.hpp \
	gvl/containers/treap2.hpp \
	gvl/containers/xlist.hpp \
	gvl/crypt/curve25519.hpp \
	gvl/crypt/gash.hpp \
	gvl/crypt/gciph.hpp \
	gvl/cstdint.hpp \
	gvl/debug.hpp \
	gvl/dense_int_set.hpp \
	gvl/gvl_test/template.hpp \
	gvl/hash_set/generic_hash_set.hpp \
	gvl/hash_set/hash_set.hpp \
	gvl/io/bitstream.hpp \
	gvl/io/bitstream_old.hpp \
	gvl/io/bitstream_templ.hpp \
	gvl/io/bitstream_templ_old.hpp \
	gvl/io/brigade2.h \
	gvl/io/brigade2.hpp \
	gvl/io/common_bitstream.hpp \
	gvl/io/convert.hpp \
	gvl/io/deflate_filter.hpp \
	gvl/io/device_buf.hpp \
	gvl/io/devnull.hpp \
	gvl/io/encoding.hpp \
	gvl/io/encoding_compat.hpp \
	gvl/io/fstream.hpp \
	gvl/io/iostream.hpp \
	gvl/io/range_coder.hpp \
	gvl/io/stream.hpp \
	gvl/io/unicode.hpp \
	gvl/linked_hash_set.hpp \
	gvl/list.hpp \
	gvl/math/cmwc.hpp \
	gvl/math/dtoa.hpp \
	gvl/math/float.hpp \
	gvl/math/ieee.hpp \
	gvl/math/math.hpp \
	gvl/math/matrix.hpp \
	gvl/math/normal_distribution.hpp \
	gvl/math/random.hpp \
	gvl/math/rect.hpp \
	gvl/math/tt800.hpp \
	gvl/math/vec.hpp \
	gvl/meta/as_unsigned.hpp \
	gvl/meta/is_ptr_convertible.hpp \
	gvl/meta/meta.hpp \
	gvl/meta/static_log2.hpp \
	gvl/resman/allocator.hpp \
	gvl/resman/linked_object.hpp \
	gvl/resman/scoped_array.hpp \
	gvl/resman/shared.h \
	gvl/resman/shared.hpp \
	gvl/resman/shared_count.hpp \
	gvl/resman/shared_list.hpp \
	gvl/resman/shared_ptr.hpp \
	gvl/serialization/archive.hpp \
	gvl/serialization/context.hpp \
	gvl/serialization/except.hpp \
	gvl/sockets/fd_set.hpp \
	gvl/sockets/socket_listener.hpp \
	gvl/sockets/sockets.hpp \
	gvl/sockets/sockets_sys_impl.hpp \
	gvl/sockets/socketstream.hpp \
	gvl/support.hpp \
	gvl/support/algorithm.hpp \
	gvl/support/align.hpp \
	gvl/support/bits.hpp \
	gvl/support/borrow.hpp \
	gvl/support/cheap_flags.hpp \
	gvl/support/config.h \
	gvl/support/cstdint.hpp \
	gvl/support/debug.hpp \
	gvl/support/disjoint_set.hpp \
	gvl/support/flags.hpp \
	gvl/support/foreach.hpp \
	gvl/support/functional.hpp \
	gvl/support/hash.hpp \
	gvl/support/log.hpp \
	gvl/support/macros.hpp \
	gvl/support/move.hpp \
	gvl/support/object_model.h \
	gvl/support/opt.hpp \
	gvl/support/platform.h \
	gvl/support/platform.hpp \
	gvl/support/profile.hpp \
	gvl/support/string_pool.hpp \
	gvl/support/type_info.hpp \
	gvl/system/memory.hpp \
	gvl/system/mutex.hpp \
	gvl/system/system.hpp \
	gvl/system/windows.hpp \
	gvl/test/gvl_tests.hpp \
	gvl/test/test.hpp \
	gvl/text/utf8.hpp \
	gvl/text/util.hpp \
	gvl/trees/node_base.hpp \
	gvl/tut/quickcheck/context.hpp \
	gvl/tut/quickcheck/generator.hpp \
	gvl/tut/quickcheck/property.hpp \
	gvl/tut/quickcheck/quickcheck.hpp \
	gvl/tut/tut.hpp \
	gvl/tut/tut_reporter.hpp \
	gvl/tut/tut_restartable.hpp \
	gvl/uthread/coro.hpp \
	gvl/uthread/uthread.hpp \
	gvl/uthread/uthread_config.hpp \
	gvl/zlib/crc32.h \
	gvl/zlib/deflate.h \
	gvl/zlib/inffast.h \
	gvl/zlib/inffixed.h \
	gvl/zlib/inflate.h \
	gvl/zlib/inftrees.h \
	gvl/zlib/trees.h \
	gvl/zlib/zconf.h \
	gvl/zlib/zconf.in.h \
	gvl/zlib/zlib.h \
	gvl/zlib/zutil.h

$(nodist_bin_SCRIPTS):
	install -d scripts/
	sed \
		-e 's,#PKGDATADIR#,$(pkgdatadir),g' \
		-e 's,#CFGFILE#,$(CFGFILE),g' \
		-e 's,#LIBEXECDIR#,$(libexecdir),g' \
		-e 's,#PACKAGE#,$(PACKAGE),g' \
		$(srcdir)/$@.am \
		> $@

$(nodist_man6_MANS):
	install -d man/
	sed \
		-e 's,#PKGDATADIR#,$(pkgdatadir),g' \
		-e 's,#CFGFILE#,$(CFGFILE),g' \
		-e 's,#LIBEXECDIR#,$(libexecdir),g' \
		-e 's,#PACKAGE#,$(PACKAGE),g' \
		-e 's,#UPPERCASE_PACKAGE#,\U$(PACKAGE),g' \
		$(srcdir)/$@.am \
		> $@

data/LIERO.CHR:
	install -d data/
	$(srcdir)/scripts/lierolibre-packgfx \
		$(srcdir)/data/graphics/gfx{1..3}.xpm \
		$@

data/LIERO.SND:
	install -d data/
	$(srcdir)/scripts/lierolibre-packsounds \
		$(srcdir)/data/sounds/ \
		$@

clean-local:
	rm -f \
		$(nodist_pkgdata_DATA) \
		$(nodist_bin_SCRIPTS) \
		$(nodist_man6_MANS)


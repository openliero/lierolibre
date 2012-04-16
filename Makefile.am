AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

dist_noinst_SCRIPTS = autogen.sh

bin_PROGRAMS = liero

LIBS = $(DEPS_LIBS) $(GVL_LIBS) $(SDL_LIBS) $(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

AM_CPPFLAGS = $(DEPS_CFLAGS) $(GVL_CFLAGS) $(SDL_CXXFLAGS) $(BOOST_CPPFLAGS) -g

AM_LDFLAGS = $(BOOST_FILESYSTEM_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS)

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
	worm.hpp \
	\
	dataPath.cpp  binReader.cpp to_string.cpp configHelper.cpp \
	configInit.cpp \
	dataPath.hpp  binReader.hpp to_string.hpp configHelper.hpp \
	configInit.hpp \
	\
	controller/commonController.cpp controller/localController.cpp \
	controller/replayController.cpp \
	controller/commonController.hpp controller/localController.hpp \
	controller/replayController.hpp \
	\
	gfx/blit.cpp gfx/font.cpp gfx/palette.cpp gfx/sprite.cpp \
	gfx/blit.hpp gfx/font.hpp gfx/palette.hpp gfx/sprite.hpp \
	\
	menu/booleanSwitchBehavior.cpp menu/enumBehavior.cpp \
	menu/hiddenMenu.cpp menu/integerBehavior.cpp menu/itemBehavior.cpp \
	menu/menu.cpp menu/menuItem.cpp menu/timeBehavior.cpp \
	menu/booleanSwitchBehavior.hpp menu/enumBehavior.hpp \
	menu/hiddenMenu.hpp menu/integerBehavior.hpp menu/itemBehavior.hpp \
	menu/menu.hpp menu/menuItem.hpp menu/timeBehavior.hpp

EXTRA_DIST = Jamfile

#ifndef UUID_DC1D9513CDD34960AB8A648004DA149D
#define UUID_DC1D9513CDD34960AB8A648004DA149D

#include <SDL/SDL.h>
#if !SDL13
#include <SDL/SDL_getenv.h>
#endif

#include "gfx.hpp"
#include "sfx.hpp"
#include "sys.hpp"
#include "game.hpp"
#include "viewport.hpp"
#include "worm.hpp"
#include "reader.hpp"
#include "filesystem.hpp"
#include "text.hpp"
#include "keys.hpp"
#include "constants.hpp"
#include "math.hpp"
#include "console.hpp"
#include <gvl/support/platform.hpp>

#include <iostream>
#include <ctime>
#include <exception>
#include <gvl/math/ieee.hpp>

#include <gvl/math/cmwc.hpp>

//#include <gvl/support/profile.hpp> // TEMP
#include <gvl/support/log.hpp> // TEMP

#include "configInit.hpp"
#include "argParse.hpp"

//#undef main

int gameEntry(int argc, char* argv[])
try
{
	gvl_init_ieee();

	// TODO: Better PRNG seeding
	Console::init();
	gfx.rand.seed(Uint32(std::time(0)));

	std::string inputFile = "./liero.cfg";
	std::string inputDir;
	std::string outputFile;
	gvl::shared_ptr<Common> common(new Common);
	gfx.common = common;

	ArgParse argParse(argc, argv);

	if (argParse.vm.count("help")) {
		std::cout << argParse.desc << std::endl;
		return 0;
	}

	if (argParse.vm.count("sdlvideo")) {
		// SDL_putenv seems to take char* in linux, STOOPID
		std::string s = "SDL_VIDEODRIVER=" + argParse.vm["sdlvideo"].as<std::string>();
		char * sdlvd = new char[s.length()+1];
		strcpy(sdlvd, s.c_str());
		SDL_putenv(sdlvd);
	}

	if (argParse.vm.count("file"))
		inputFile = argParse.vm["file"].as<std::string>();

	if (argParse.vm.count("dir"))
		inputDir = argParse.vm["dir"].as<std::string>();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

/*
	char buf[256];
	std::cout << SDL_VideoDriverName(buf, 256) << std::endl;
*/

	if (argParse.vm.count("file") && argParse.vm.count("dir")) {
		ConfigInit cfgInit(inputFile, inputDir, common);

		if (argParse.vm.count("write"))
			cfgInit.write(argParse.vm["write"].as<std::string>());
	} else {
		ConfigInit cfgInit(inputFile, common);

		if (argParse.vm.count("write"))
			cfgInit.write(argParse.vm["write"].as<std::string>());
	}

	Console::writeLine(common->S[OK]);

	Console::writeLine(common->S[InitSound]);

	Console::write(common->S[Init_BaseIO]);
	Console::write("0220");
	Console::write(common->S[Init_IRQ]);
	Console::write("7");
	Console::write(common->S[Init_DMA8]);
	Console::write("1");
	Console::write(common->S[Init_DMA16]);
	Console::writeLine("5");

#if !DISABLE_SOUND
	Console::write(common->S[Init_DSPVersion]);
	SDL_version const* mixerVer = Mix_Linked_Version();
	Console::write(toString(mixerVer->major) + "." + toString(mixerVer->minor));
	Console::write(common->S[Init_Colon]);
	Console::write(common->S[Init_16bit]);
	Console::writeLine(common->S[Init_Autoinit]);
#endif
	Console::writeLine(common->S[Init_XMSSucc]);

	Console::write(common->S[Init_FreeXMS]);
#if GVL_WIN32
	Console::write(toString(Win32::getFreeMemory()));
#else

	Console::write("OVER 9000 ");
#endif
	Console::write(common->S[Init_k]);

	Console::write(common->S[LoadingSounds]);
	sfx.loadFromSND();
	Console::writeLine(common->S[OK2]);

	Console::writeLine("");
#if GVL_WINDOWS
	Console::write(common->S[PressAnyKey]);
	Console::waitForAnyKey();
#endif
	Console::clear();

	gfx.init();

	gfx.settingsFile = "LIERO";

	// NOTE: Liero uses LIERO.OPT to store the name of the currently active settings file
	if (!fileExists(lieroOPT)) {
		gfx.settings.reset(new Settings);
		gfx.saveSettings();
	} else {
		FILE* f = fopen(lieroOPT.c_str(), "rb");
		std::size_t len = fileLength(f);
		if (len > 255)
			len = 255;
		char buf[256];
		fread(buf, 1, len, f);
		gfx.settingsFile.assign(buf, len);

		rtrim(gfx.settingsFile);
		if (!gfx.loadSettings()) {
			gfx.settingsFile = "LIERO";
			gfx.settings.reset(new Settings);
			gfx.saveSettings();
		}

		fclose(f);
	}

	gfx.setVideoMode();
	sfx.init();

	//game.initGame();
	gfx.mainLoop();

	gfx.saveSettings();

	FILE* f = fopen(lieroOPT.c_str(), "wb");
	fwrite(gfx.settingsFile.data(), 1, gfx.settingsFile.size(), f);
	fputc('\r', f);
	fputc('\n', f);
	fclose(f);

	closeAllCachedFiles();

	sfx.deinit();
	SDL_Quit();

	//gvl::present_profile(std::cout);

	return 0;
}
catch(std::exception& ex)
{
	SDL_Quit();
	Console::setAttributes(0x2f);
	Console::writeLine(std::string("EXCEPTION: ") + ex.what());
#if GVL_WINDOWS
	Console::writeLine("Press any key to quit");
	Console::waitForAnyKey();
#endif
	return 1;
}

#endif // UUID_DC1D9513CDD34960AB8A648004DA149D

#include <SDL/SDL.h>
//#if !SDL13
//#include <SDL/SDL_getenv.h>
//#endif

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
#include "common.hpp"
#include "math.hpp"
#include "console.hpp"
#include <gvl/support/platform.hpp>

#include <iostream>
#include <ctime>
#include <exception>
#include <gvl/math/ieee.hpp>

#include <gvl/math/cmwc.hpp>

#include <gvl/support/log.hpp> // TEMP

#include "init.hpp"
#include <boost/filesystem.hpp>

#if GVL_LINUX
#define BOOST_FILESYSTEM_DYN_LINK
#endif

#include <string>
#include <fstream>

using namespace std;
namespace bfs = boost::filesystem;

ConfigInit::ConfigInit(string a_filePath, gvl::shared_ptr<Common> a_common)
{
	common = a_common;

	bfs::path filePath(a_filePath);

	if(filePath.extension() == ".EXE" || filePath.extension() == ".exe")
		loadFromEXE(filePath.native());
	else
		loadFromCFG(filePath.native());
}

void ConfigInit::consoleBlurb()
{
	Console::clear();
	Console::writeTextBar(common->texts.copyright1, common->texts.copyrightBarFormat);
	Console::setAttributes(0x07);
	Console::writeLine("");

	Console::write(common->S[LoadingAndThinking]);
}

void ConfigInit::loadFromEXE(string filePath)
{
	// Need to get grab the path to the exe from somewheres
//	setLieroEXE(filePath);

	common->texts.loadFromEXE();

	initKeys();

	common->loadConstantsFromEXE();
	loadTablesFromEXE();

	consoleBlurb();

	common->font.loadFromEXE();
	common->loadPalette();
	gfx.loadPalette(); // This gets the palette from common
	gfx.loadMenus();
	common->loadGfx();
	common->loadMaterials();
	common->loadWeapons();
	common->loadTextures();
	common->loadOthers();
}

void ConfigInit::loadFromCFG(string filePath)
{
	common->texts.loadFromCFG(filePath);

	initKeys();

	common->loadConstantsFromCFG(filePath);
	loadTablesFromCFG(filePath);

	consoleBlurb();

	common->font.loadFromCFG(filePath);
	common->loadPaletteFromCFG(filePath);
	gfx.loadPalette(); // This gets the palette from common
	gfx.loadMenusFromCFG(filePath);
	common->loadGfxFromCFG(filePath);
	common->loadMaterialsFromCFG(filePath);
	common->loadWeaponsFromCFG(filePath);
	common->loadTexturesFromCFG(filePath);
	common->loadOthersFromCFG(filePath);
}


void ConfigInit::write(string filePath)
{
	Console::writeLine("");
	Console::writeLine("Saving variables to file '" + filePath +"'");

	// Create empty if nonexistant
	if(!bfs::exists(filePath)) {
		ofstream f(filePath.c_str());
		f << flush;
		f.close();
	}

	common->texts.writeToCFG(filePath);
	common->writeConstantsToCFG(filePath);
	writeTablesToCFG(filePath);
	common->font.writeToCFG(filePath);
	common->writePaletteToCFG(filePath);
	gfx.writeMenusToCFG(filePath);
	common->writeGfxToCFG(filePath);
	common->writeMaterialsToCFG(filePath);
	common->writeWeaponsToCFG(filePath);
	common->writeTexturesToCFG(filePath);
	common->writeOthersToCFG(filePath);
}

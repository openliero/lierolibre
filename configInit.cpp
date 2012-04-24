#include "configInit.hpp"

#include <string>
#include <fstream>
#include <exception>

#include "filesystem.hpp"
#include "gfx.hpp"
#include "common.hpp"
#include "console.hpp"
#include "reader.hpp"

using namespace std;

ConfigInit::ConfigInit(string filePath, gvl::shared_ptr<Common> a_common)
{
	common = a_common;

	if (getExtension(filePath) == "EXE" || getExtension(filePath) == "exe") {
		setLieroEXE(filePath);
		loadFromEXE(filePath);
	} else if (getExtension(filePath) == "cfg" || getExtension(filePath) == "txt") {
		// Force reading from given CFG
		setLieroCFG(filePath);
		loadFromCFG(lieroCFG);
	} else {
		// $HOME CFG takes priority
		setLieroPath(filePath);
		loadFromCFG(lieroCFG);
	}
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
	if (!fileExists(filePath)) {
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

/*
 * Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
 * This software is released under the The BSD-2-Clause License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "configInit.hpp"

#include <string>
#include <fstream>
#include <stdexcept>

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
		setLieroPath(filePath);
		loadFromEXE(filePath);
	} else if (getExtension(filePath) == "cfg" || getExtension(filePath) == "txt") {
		setLieroPath(filePath);
		loadFromCFG(filePath); // Force reading from given CFG
	} else {
		setLieroPath(filePath);
		setLieroCFG(filePath); // Copies to $HOME
		loadFromCFG(lieroCFG); // $HOME CFG takes priority
	}
}

ConfigInit::ConfigInit(string filePath, string dirPath, gvl::shared_ptr<Common> a_common)
{
	common = a_common;

	if (getExtension(filePath) == "EXE" || getExtension(filePath) == "exe") {
		setLieroPath(dirPath);
		loadFromEXE(filePath);
	} else if (isDir(filePath)) {
		// User gave us two directories
		setLieroPath(dirPath);
		setLieroCFG(filePath); // Copies to $HOME
		loadFromCFG(lieroCFG); // $HOME CFG takes priority
	} else {
		setLieroPath(dirPath);
		loadFromCFG(filePath);
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
	setLieroEXE(filePath);

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
/* The neat exception methods were introduced in v 1.4 of libconfig
 * don't try to use them on earlier versions
 */
#if LIBCONFIGXX_VER_MAJOR >= 1 && LIBCONFIGXX_VER_MINOR >= 4
	try {
#endif
		int CFGFileVersion = common->readCFGVersion(filePath);
		if (CFGFileVersion > CFGVERSION)
			throw runtime_error("Config file '" + filePath + "' is of a newer, incompatible version");

		common->texts.loadFromCFG(filePath);

		initKeys();

		if (CFGFileVersion == 0)
			common->loadConstantsFromCFGVer0(filePath);
		else
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

#if LIBCONFIGXX_VER_MAJOR >= 1 && LIBCONFIGXX_VER_MINOR >= 4
	} catch (const libconfig::ParseException& e) {
		cerr << e.getError() << " in file '" << e.getFile() << "' at line " << e.getLine() << endl;
		throw;
	} catch (const libconfig::SettingException e) {
		cerr << "Problem at " <<  e.getPath() << endl;
		throw;
	}
#endif
}

void ConfigInit::write(string filePath)
{
/* The neat exception methods were introduced in v 1.4 of libconfig
 * don't try to use them on earlier versions
 */
#if LIBCONFIGXX_VER_MAJOR >= 1 && LIBCONFIGXX_VER_MINOR >= 4
	try {
#endif
		Console::writeLine("");
		Console::writeLine("Saving variables to file '" + filePath +"'");

		// Create empty if nonexistant
		if (!fileExists(filePath)) {
			ofstream f(filePath.c_str());
			f << flush;
			f.close();
		}

		common->writeCFGVersion(filePath, CFGVERSION);

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

#if LIBCONFIGXX_VER_MAJOR >= 1 && LIBCONFIGXX_VER_MINOR >= 4
	} catch (const libconfig::ParseException& e) {
		cerr << e.getError() << " in file '" << e.getFile() << "' at line " << e.getLine() << endl;
		throw;
	} catch (const libconfig::SettingException e) {
		cerr << "Problem at " <<  e.getPath() << endl;
		throw;
	}
#endif
}

bool ConfigInit::upgradeCFG(string filePath, int version)
{
	try {
		int CFGFileVersion = common->readCFGVersion(filePath);
		if (CFGFileVersion > CFGVERSION)
			throw runtime_error("Config file '" + filePath + "' is of a newer, incompatible version");
		else if (CFGFileVersion < CFGVERSION) {
			loadFromCFG(filePath);
			backupFile(filePath);
			rmFile(filePath);
			write(filePath);
			return true;
		}
	} catch (std::exception& e) {
		throw runtime_error("Error when upgrading CFG file: " + string(e.what()));
	} catch (...) {
		throw runtime_error("Error when upgrading CFG file");
	}

	return false; // Not upgraded
}

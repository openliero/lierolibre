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
		setLieroPath(filePath);
		loadFromEXE(filePath);
	} else if (getExtension(filePath) == "cfg" || getExtension(filePath) == "txt") {
		setLieroPath(filePath);
		loadFromCFG(filePath); // Force reading from given CFG
	} else {
		setLieroPath(filePath);
		loadFromCFG(lieroCFG); // $HOME CFG takes priority
	}
}

ConfigInit::ConfigInit(string filePath, string dirPath, gvl::shared_ptr<Common> a_common)
{
	common = a_common;

	if (getExtension(filePath) == "EXE" || getExtension(filePath) == "exe") {
		setLieroPath(dirPath);
		loadFromEXE(filePath);
	} else {
		// User provides file and dir/
		// file must be intented as config hence ignore cfg in $HOME
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

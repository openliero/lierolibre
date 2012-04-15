/*
 Copyright (c) 2010, Erik Lindroos <gliptic@gmail.com>
 Copyright (c) 2010, "basro"
 Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
 This software is released under the The BSD-2-Clause License:

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UUID_9E238CFB9F074A3A432E22AE5B8EE5FB
#define UUID_9E238CFB9F074A3A432E22AE5B8EE5FB

#include "gfx/font.hpp"
#include "weapon.hpp"
#include "sobject.hpp"
#include "nobject.hpp"
#include "constants.hpp"
#include "gfx/palette.hpp"
#include "gfx/sprite.hpp"
#include <string>
#include <gvl/resman/shared_ptr.hpp>

#include <libconfig.h++>


extern int stoneTab[3][4];

struct Material
{
	enum
	{
		Dirt = 1<<0,
		Dirt2 = 1<<1,
		Rock = 1<<2,
		Background = 1<<3,
		SeeShadow = 1<<4,
		WormM = 1<<5
	};

	bool dirt() { return (flags & Dirt) != 0; }
	bool dirt2() { return (flags & Dirt2) != 0; }
	bool rock() { return (flags & Rock) != 0; }
	bool background() { return (flags & Background) != 0; }
	bool seeShadow() { return (flags & SeeShadow) != 0; }

	// Constructed
	bool dirtRock() { return (flags & (Dirt | Dirt2 | Rock)) != 0; }
	bool anyDirt() { return (flags & (Dirt | Dirt2)) != 0; }
	bool dirtBack() { return (flags & (Dirt | Dirt2 | Background)) != 0; }
	bool worm() { return (flags & WormM) != 0; }

	int flags;
};

struct Texture
{
	bool nDrawBack; // 1C208
	int  mFrame; // 1C1EA
	int  sFrame; // 1C1F4
	int  rFrame; // 1C1FE
};

struct Texts
{
	void loadFromEXE();
	void loadFromCFG();
	void writeToCFG(std::string cfgFilePath);
	void writeToCFG();

	std::string copyright1;
	std::string copyright2;
	std::string loadoptions;
	std::string saveoptions;
	std::string curOptNoFile;
	std::string curOpt;

	std::string gameModes[4];
	std::string gameModeSpec[3];
	std::string onoff[2];
	std::string controllers[2];

	std::string keyNames[177];

	std::string random;
	std::string random2;
	std::string reloadLevel;
	std::string regenLevel;
	std::string selWeap;
	std::string levelRandom;
	std::string levelIs1;
	std::string levelIs2;
	std::string randomize;
	std::string done;

	std::string kills;
	std::string lives;

	std::string suicide;
	std::string reloading;
	std::string pressFire;
	std::string selLevel;

	std::string noWeaps;
	std::string weapon;
	std::string availability;
	std::string weapStates[3];

	int copyrightBarFormat;

};

struct ColourAnim
{
	int from;
	int to;
};

struct AIParams
{
	int k[2][7]; // 0x1AEEE, contiguous words
};

struct Common : gvl::shared
{
	Common()
	{
	}

	static int fireConeOffset[2][7][2];

	void loadMaterials();
	void loadMaterialsFromCFG(std::string);
	void loadMaterialsFromCFG();
	void writeMaterialsToCFG(std::string);
	void writeMaterialsToCFG();

	void loadWeapons();
	void loadWeaponsFromCFG(std::string cfgFilePath);
	void loadWeaponsFromCFG();
	void writeWeaponsToCFG(std::string cfgFilePath);
	void writeWeaponsToCFG();

	void loadTextures();
	void loadTexturesFromCFG(std::string cfgFilePath);
	void loadTexturesFromCFG();
	void writeTexturesToCFG(std::string cfgFilePath);
	void writeTexturesToCFG();

	void loadOthers();
	void loadOthersFromCFG(std::string cfgFilePath);
	void loadOthersFromCFG();
	void writeOthersToCFG(std::string cfgFilePath);
	void writeOthersToCFG();

	void loadConstantsFromEXE();
	void loadConstantsFromCFG(std::string cfgFilePath);
	void loadConstantsFromCFG();
	void writeConstantsToCFG(std::string cfgFilePath);
	void writeConstantsToCFG();

	void loadGfxFromEXE();
	void loadGfxFromCHR();
	void loadGfxExtra();
	void loadGfx();
	void loadGfxFromCFG(std::string cfgFilePath);
	void loadGfxFromCFG();
	void writeGfxToCFG(std::string cfgFilePath);
	void writeGfxToCFG();

	void loadPalette();
	void loadPaletteFromCFG(std::string cfgFilePath);
	void loadPaletteFromCFG();
	void writePaletteToCFG(std::string cfgFilePath);
	void writePaletteToCFG();

	void drawTextSmall(char const* str, int x, int y);

	PalIdx* wormSprite(int f, int dir, int w)
	{
		return wormSprites.spritePtr(f + dir*7*3 + w*2*7*3);
	}

	PalIdx* fireConeSprite(int f, int dir)
	{
		return fireConeSprites.spritePtr(f + dir*7);
	}

	Material materials[256];
	Texts texts;
	Texture textures[9];
	Weapon weapons[40];
	SObjectType sobjectTypes[14];
	NObjectType nobjectTypes[24];
	int weapOrder[41]; // 1-based!
	int bonusRandTimer[2][2];
	int bonusSObjects[2];
	AIParams aiParams;
	ColourAnim colorAnim[4];
	int bonusFrames[2];
	SpriteSet smallSprites;
	SpriteSet largeSprites;
	SpriteSet textSprites;
	SpriteSet wormSprites;
	SpriteSet fireConeSprites;
	Palette exepal;
	Font font;

	int C[MaxC];
	std::string S[MaxS];
	bool H[MaxH];
};

#endif // UUID_9E238CFB9F074A3A432E22AE5B8EE5FB

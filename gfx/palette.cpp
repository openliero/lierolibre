/*
 * Copyright (c) 2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
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

#include "palette.hpp"

#include "../settings.hpp"
#include "../reader.hpp"
#include "../gfx.hpp"
#include <SDL/SDL.h>
#include <libconfig.h++>
#include "to_string.hpp"
#include "configHelper.hpp"

void Palette::activate()
{
	SDL_Color realPal[256];

	for(int i = 0; i < 256; ++i)
	{
		realPal[i].r = entries[i].r << 2;
		realPal[i].g = entries[i].g << 2;
		realPal[i].b = entries[i].b << 2;
	}

	SDL_SetColors(gfx.back, realPal, 0, 256);
	SDL_SetColors(gfx.screen, realPal, 0, 256);
}

int fadeValue(int v, int amount)
{
	assert(v < 64);
	v = (v * amount) >> 5;
	if(v < 0) v = 0;
	return v;
}

int lightUpValue(int v, int amount)
{
	v = (v * (32 - amount) + amount*63) >> 5;
	if(v > 63) v = 63;
	return v;
}

void Palette::fade(int amount)
{
	if(amount >= 32)
		return;

	for(int i = 0; i < 256; ++i)
	{
		entries[i].r = fadeValue(entries[i].r, amount);
		entries[i].g = fadeValue(entries[i].g, amount);
		entries[i].b = fadeValue(entries[i].b, amount);
	}
}

void Palette::lightUp(int amount)
{
	for(int i = 0; i < 256; ++i)
	{
		entries[i].r = lightUpValue(entries[i].r, amount);
		entries[i].g = lightUpValue(entries[i].g, amount);
		entries[i].b = lightUpValue(entries[i].b, amount);
	}
}

void Palette::rotate(int from, int to)
{
	SDL_Color tocol = entries[to];
	for(int i = to; i > from; --i)
	{
		entries[i] = entries[i - 1];
	}
	entries[from] = tocol;
}

void Palette::clear()
{
	std::memset(entries, 0, sizeof(entries));
}

void Palette::read(FILE* f)
{
	for(int i = 0; i < 256; ++i)
	{
		unsigned char rgb[3];
		checkedFread(rgb, 1, 3, f);

		entries[i].r = rgb[0] & 63;
		entries[i].g = rgb[1] & 63;
		entries[i].b = rgb[2] & 63;
	}
}

void Palette::readFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &spentries = cfg.lookup("Palette.entries");

	for(int i = 0; i < 256; ++i)
	{
		entries[i].r = cfgHelp.getValue<Uint8>(spentries, "entries" + to_string(i) + "r");
		entries[i].g = cfgHelp.getValue<Uint8>(spentries, "entries" + to_string(i) + "g");
		entries[i].b = cfgHelp.getValue<Uint8>(spentries, "entries" + to_string(i) + "b");
	}
}

void Palette::readFromCFG(void)
{
	readFromCFG("liero.cfg");
}

void Palette::writeToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &palette = cfgHelp.getSubgroup(root, "Palette");
	libconfig::Setting &spentries = cfgHelp.getSubgroup(palette, "entries");

	for(int i = 0; i < 256; ++i)
	{
		cfgHelp.put(spentries, "entries" + to_string(i) + "r", entries[i].r);
		cfgHelp.put(spentries, "entries" + to_string(i) + "g", entries[i].g);
		cfgHelp.put(spentries, "entries" + to_string(i) + "b", entries[i].b);
	}
	cfg.writeFile(cfgFilePath.c_str());
}

void Palette::writeToCFG()
{
	writeToCFG("liero.cfg");
}

void Palette::setWormColour(int i, WormSettings const& settings)
{
	int const b[2] = {0x58, 0x78}; // TODO: Read from EXE?

	int idx = settings.color;

	setWormColoursSpan(idx, settings.rgb);

	for(int j = 0; j < 6; ++j)
	{
		entries[b[i] + j] = entries[idx + (j % 3) - 1];
	}

	for(int j = 0; j < 3; ++j)
	{
		entries[129 + i * 4 + j] = entries[idx + j];
	}
}


void Palette::setWormColours(Settings const& settings)
{
	for(int i = 0; i < 2; ++i)
	{
		setWormColour(i, *settings.wormSettings[i]);
	}
}

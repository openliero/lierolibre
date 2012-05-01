/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
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

#include "font.hpp"
#include "../reader.hpp"
#include "../gfx.hpp"
#include "macros.hpp"
#include "color.hpp"
#include <iostream>

#include <libconfig.h++>
#include "configHelper.hpp"
#include "to_string.hpp"

void Font::loadFromEXE()
{
	chars.resize(250);

	std::size_t const FontSize = 250 * 8 * 8 + 1;
	std::vector<unsigned char> temp(FontSize);

	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C825, SEEK_SET);

	checkedFread(&temp[0], 1, FontSize, exe);

	for(int i = 0; i < 250; ++i)
	{
		unsigned char* ptr = &temp[i*64 + 1];

		for(int y = 0; y < 8; ++y)
		{
			for(int x = 0; x < 7; ++x)
			{
				chars[i].data[y*7 + x] = ptr[y*8 + x];
			}
		}

		chars[i].width = ptr[63];
	}
}

void Font::loadFromCFG(std::string cfgFilePath)
{
	chars.resize(250);

	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &sfont = cfg.lookup("Font");

	for(int i = 0; i < 250; ++i)
	{
		const libconfig::Setting &sfchar = sfont[i];
		for(int j = 0; j < 56; ++j)
		{
			// Font { char0 { data[]
			const libconfig::Setting &sfcdata = sfchar["data"];
			chars[i].data[j] = cfgHelp.getValue<Uint8>(sfcdata, j);
		}
		// Font { char0 { width
		chars[i].width = sfchar["width"];
	}
}

void Font::writeToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &sfont = cfgHelp.getSubgroup(root, "Font");

	for(int i = 0; i < 250; ++i)
	{
		libconfig::Setting &sfchar = cfgHelp.getSubgroup(sfont, "char" + to_string(i));
		libconfig::Setting &sfcdata = cfgHelp.mkArray(sfchar, "data");
		for(int j = 0; j < 56; ++j)
		{
			// convert from Uint8 to int for config
			sfcdata.add(libconfig::Setting::TypeInt) = static_cast<int>(chars[i].data[j]);
		}
		// Font { char0 { width
		cfgHelp.put(sfchar, "width", chars[i].width);
	}
	cfg.writeFile(cfgFilePath.c_str());
}

void Font::drawChar(unsigned char c, int x, int y, int color)
{
	if(c >= 2 && c < 252) // TODO: Is this correct, shouldn't it be c >= 0 && c < 250, since drawText subtracts 2?
	{
		SDL_Surface* scr = gfx.screen;
		uint8_t* mem = chars[c].data;
		int width = 7;
		int height = 8;
		int pitch = 7;

		CLIP_IMAGE(scr->clip_rect);

		PalIdx* scrptr = static_cast<PalIdx*>(scr->pixels) + y*scr->pitch + x;

		for(int cy = 0; cy < height; ++cy)
		{
			PalIdx* rowdest = scrptr;
			PalIdx* rowsrc = mem;

			for(int cx = 0; cx < width; ++cx)
			{
				PalIdx c = *rowsrc;
				if(c)
					*rowdest = color;
				++rowsrc;
				++rowdest;
			}

			scrptr += scr->pitch;
			mem += pitch;
		}
	}
}

void Font::drawText(char const* str, std::size_t len, int x, int y, int color)
{
	int orgX = x;

	for(std::size_t i = 0; i < len; ++str, ++i)
	{
		unsigned char c = static_cast<unsigned char>(*str);

		if(!c)
		{
			x = orgX;
			y += 8;
		}
		else if(c >= 2 && c < 252)
		{
			c -= 2;

			drawChar(c, x, y, color);

			x += chars[c].width;
		}
	}
}

void Font::drawFramedText(std::string const& text, int x, int y, int color)
{
	drawRoundedBox(x, y, 0, 7, getDims(text));
	drawText(text, x + 2, y + 1, color);
}

int Font::getDims(char const* str, std::size_t len, int* height)
{
	int width = 0;
	int maxHeight = 8;

	int maxWidth = 0;

	for(std::size_t i = 0; i < len; ++str, ++i)
	{
		unsigned char c = static_cast<unsigned char>(*str);
		if(c >= 2 && c < 252)
			width += chars[c - 2].width;
		else if(!c)
		{
			maxWidth = std::max(maxWidth, width);
			width = 0;
			maxHeight += 8;
		}
	}

	if(height)
		*height = maxHeight;

	return std::max(maxWidth, width);
}

/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
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

#ifndef LIERO_LEVEL_HPP
#define LIERO_LEVEL_HPP

#include <vector>
#include <string>
#include <cstdio>
#include <utility>
#include "rect.hpp"
#include "gfx/palette.hpp"
#include <SDL/SDL.h>

struct Game;
struct Settings;
struct Rand;
struct Common;

struct Level
{
	Level()
	: width(0)
	, height(0)
	{
	}

	bool load(Common& common, Settings const& settings, std::string const& path);

	void generateDirtPattern(Common& common, Rand& rand);
	void generateRandom(Common& common, Settings const& settings, Rand& rand);
	void makeShadow(Common& common);
	void generateFromSettings(Common& common, Settings const& settings, Rand& rand);

	unsigned char& pixel(int x, int y)
	{
		return data[x + y*width];
	}

	unsigned char checkedPixelWrap(int x, int y)
	{
		unsigned int idx = static_cast<unsigned int>(x + y*width);
		if(idx < data.size())
			return data[idx];
		return 0;
	}

	bool inside(int x, int y)
	{
		return static_cast<unsigned int>(x) < static_cast<unsigned int>(width)
		    && static_cast<unsigned int>(y) < static_cast<unsigned int>(height);
	}

	void swap(Level& other)
	{
		data.swap(other.data);
		std::swap(width, other.width);
		std::swap(height, other.height);
		std::swap(origpal, other.origpal);
		std::swap(oldRandomLevel, other.oldRandomLevel);
		std::swap(oldLevelFile, other.oldLevelFile);
	}

	Rect rect()
	{
		return Rect(0, 0, width, height);
	}

	void resize(int width_new, int height_new);

	std::vector<unsigned char> data;

	bool oldRandomLevel;
	std::string oldLevelFile;
	int width;
	int height;
	Palette origpal;
};

#endif // LIERO_LEVEL_HPP

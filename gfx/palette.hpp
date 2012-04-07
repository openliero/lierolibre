/*
 Copyright (c) 2009, Erik Lindroos <gliptic@gmail.com>
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

#ifndef UUID_74C8EE76D5564F2D8C7BBC9B26C16192
#define UUID_74C8EE76D5564F2D8C7BBC9B26C16192

#include <SDL/SDL.h>
#include <cstdio>
#include <gvl/support/debug.hpp>
#include <string>

struct Settings;
struct WormSettings;

struct Palette
{
	SDL_Color entries[256];

	// TODO: Move definitions of these from gfx.cpp to palette.cpp
	void activate();
	void fade(int amount);
	void lightUp(int amount);
	void rotate(int from, int to);
	void read(FILE* f);

	void scaleAdd(int dest, int const(&c)[3], int scale, int add)
	{
		entries[dest].r = (add + c[0] * scale) / 64;
		entries[dest].g = (add + c[1] * scale) / 64;
		entries[dest].b = (add + c[2] * scale) / 64;

		sassert(entries[dest].r < 64);
		sassert(entries[dest].g < 64);
		sassert(entries[dest].b < 64);
	}

	void setWormColoursSpan(int base, int const (&c)[3])
	{
		scaleAdd(base - 2, c, 38, 0);
		scaleAdd(base - 1, c, 50, 0);
		scaleAdd(base    , c, 64, 0);
		scaleAdd(base + 1, c, 47, 1008);
		scaleAdd(base + 2, c, 28, 2205);
	}

	void resetPalette(Palette const& newPal, Settings const& settings)
	{
		*this = newPal;
		//setWormColours(settings);
	}

	void setWormColour(int i, WormSettings const& settings);
	void setWormColours(Settings const& settings);

	void clear();
};

#endif // UUID_74C8EE76D5564F2D8C7BBC9B26C16192

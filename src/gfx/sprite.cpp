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

#include "sprite.hpp"

#include "../reader.hpp"

#include <vector>
#include <cassert>

void SpriteSet::read(FILE* f, int width, int height, int count)
{
	assert(width == height); // We only support rectangular sprites right now
	
	this->width = width;
	this->height = height;
	this->spriteSize = width * height;
	this->count = count;
	
	int amount = spriteSize * count;
	data.resize(amount);
	
	std::vector<PalIdx> temp(amount);
	
	checkedFread(&temp[0], 1, amount, f);
	
	PalIdx* dest = &data[0];
	PalIdx* src = &temp[0];
	
	for(int i = 0; i < count; i++)
	{
		for(int x = 0; x < width; ++x)
		{
			for(int y = 0; y < height; ++y)
			{
				dest[x + y*width] = src[y];
			}
			
			src += height;
		}
		
		dest += spriteSize;
	}
}

void SpriteSet::allocate(int width, int height, int count)
{
	this->width = width;
	this->height = height;
	this->spriteSize = width * height;
	this->count = count;
	
	int amount = spriteSize * count;
	data.resize(amount);
}

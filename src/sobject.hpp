/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
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

#ifndef LIERO_SOBJECT_HPP
#define LIERO_SOBJECT_HPP

#include "math.hpp"
#include "objectList.hpp"
#include "exactObjectList.hpp"

struct Worm;
struct Game;

struct SObjectType
{
	void create(Game& game, int x, int y, Worm* owner);

	int startSound;
	int numSounds;
	int animDelay;
	int startFrame;
	int numFrames;
	int detectRange;
	int damage;
	int blowAway;
	bool shadow;
	int shake;
	int flash;
	int dirtEffect;

	int id;
};

struct SObject : ExactObjectListBase
{
	void process(Game& game);

	fixed x, y;
	int id; // type
	int curFrame;
	int animDelay;
};

#endif // LIERO_SOBJECT_HPP

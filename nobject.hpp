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

#ifndef LIERO_NOBJECT_HPP
#define LIERO_NOBJECT_HPP

#include "math.hpp"
#include "objectList.hpp"
#include "exactObjectList.hpp"

struct Worm;
struct Game;

struct NObjectType
{
	void create1(Game& game, fixed velX, fixed velY, int x, int y, int color, Worm* owner);
	void create2(Game& game, int angle, fixed velX, fixed velY, fixed x, fixed y, int color, Worm* owner);

	int detectDistance;
	fixed gravity;
	int speed;
	int speedV;
	int distribution;
	int blowAway;
	int bounce;
	int hitDamage;
	bool wormExplode;
	bool explGround;
	bool wormDestroy;
	int bloodOnHit;
	int startFrame;
	int numFrames;
	bool drawOnMap;
	int colorBullets;
	int createOnExp;
	bool affectByExplosions;
	int dirtEffect;
	int splinterAmount;
	int splinterColour;
	int splinterType;
	bool bloodTrail;
	int bloodTrailDelay;
	int leaveObj;
	int leaveObjDelay;
	int timeToExplo;
	int timeToExploV;

	int id;
};

struct NObject : ExactObjectListBase
{
	void process(Game& game);

	fixed x, y;
	fixed velX, velY;
	int timeLeft;
	int id;
	Worm* owner;
	int curFrame;
};

#endif // LIERO_NOBJECT_HPP

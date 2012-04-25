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

#ifndef LIERO_WEAPON_HPP
#define LIERO_WEAPON_HPP

#include "math.hpp"
#include "objectList.hpp"
#include "exactObjectList.hpp"
#include <string>

struct Worm;
struct Game;
struct Settings;

struct Weapon
{
	enum
	{
		STNormal,
		STDType1,
		STSteerable,
		STDType2,
		STLaser
	};

	void fire(Game& game, int angle, fixed velX, fixed velY, int speed, fixed x, fixed y, Worm* owner);

	int detectDistance;
	bool affectByWorm;
	int blowAway;
	fixed gravity;
	bool shadow;
	bool laserSight;
	int launchSound;
	int loopSound;
	int exploSound;
	int speed;
	fixed addSpeed;
	int distribution;
	int parts;
	int recoil;
	int multSpeed;
	int delay;
	int loadingTime;
	int ammo;
	int createOnExp;
	int dirtEffect;
	int leaveShells;
	int leaveShellDelay;
	bool playReloadSound;
	bool wormExplode;
	bool explGround;
	bool wormCollide;
	int fireCone;
	bool collideWithObjects;
	bool affectByExplosions;
	int bounce;
	int timeToExplo;
	int timeToExploV;
	int hitDamage;
	int bloodOnHit;
	int startFrame;
	int numFrames;
	bool loopAnim;
	int shotType;
	int colorBullets;
	int splinterAmount;
	int splinterColour;
	int splinterType;
	int splinterScatter;
	int objTrailType;
	int objTrailDelay;
	int partTrailType;
	int partTrailObj;
	int partTrailDelay;

	int computedLoadingTime(Settings& settings);

	int id;
	//int computedLoadingTime;
	std::string name;
};

struct WObject : ExactObjectListBase
{
	void blowUpObject(Game& game, Worm* cause);
	void process(Game& game);

	fixed x, y;
	fixed velX, velY;
	int id;
	Worm* owner;
	int curFrame;
	int timeLeft;
};


#endif // LIERO_WEAPON_HPP

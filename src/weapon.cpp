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

#include "weapon.hpp"
#include "game.hpp"
#include "sfx.hpp"
#include "math.hpp"
#include "gfx.hpp"
#include "constants.hpp"
#include <iostream>

int Weapon::computedLoadingTime(Settings& settings)
{
	int ret = (settings.loadingTime * loadingTime) / 100;
	if(ret == 0)
		ret = 1;
	return ret;
}

void Weapon::fire(Game& game, int angle, fixed velX, fixed velY, int speed, fixed x, fixed y, Worm* owner)
{
	WObject* obj = game.wobjects.newObjectReuse();
	
	
	
	obj->id = id;
	obj->x = x;
	obj->y = y;
	obj->owner = owner;

	if(distribution)
	{
		obj->velX = cosTable[angle] * speed / 100 + velX + game.rand(distribution * 2) - distribution;
		obj->velY = sinTable[angle] * speed / 100 + velY + game.rand(distribution * 2) - distribution;
	}
	else
	{
		obj->velX = cosTable[angle] * speed / 100 + velX;
		obj->velY = sinTable[angle] * speed / 100 + velY;
	}
	
	if(startFrame >= 0)
	{
		if(shotType == STNormal)
		{
			if(loopAnim)
			{
				if(numFrames)
					obj->curFrame = game.rand(numFrames + 1);
				else
					obj->curFrame = game.rand(2);
			}
			else
				obj->curFrame = 0;
		}
		else if(shotType == STDType1)
		{
			if(angle > 64)
				--angle;
				
			int curFrame = (angle - 12) >> 3;
			if(curFrame < 0)
				curFrame = 0;
			else if(curFrame > 12)
				curFrame = 12;
			obj->curFrame = curFrame;
		}
		else if(shotType == STDType2 || shotType == STSteerable)
		{
			obj->curFrame = angle;
		}
		else
			obj->curFrame = 0;
	}
	else
	{
		obj->curFrame = colorBullets - game.rand(2);
	}
	
	obj->timeLeft = timeToExplo;
	
	if(timeToExploV)
		obj->timeLeft -= game.rand(timeToExploV);
}

void WObject::blowUpObject(Game& game, Worm* cause)
{
	Common& common = *game.common;
	Weapon& w = common.weapons[id];
	
	fixed x = this->x;
	fixed y = this->y;
	fixed velX = this->velX;
	fixed velY = this->velY;
	
	game.wobjects.free(this);
	
	if(w.createOnExp >= 0)
	{
		common.sobjectTypes[w.createOnExp].create(game, ftoi(x), ftoi(y), cause);
	}
	
	if(w.exploSound >= 0)
	{
		game.soundPlayer->play(w.exploSound);
	}
	
	int splinters = w.splinterAmount;
	
	if(splinters > 0)
	{
		if(w.splinterScatter == 0)
		{
			for(int i = 0; i < splinters; ++i)
			{
				int angle = game.rand(128);
				int colorSub = game.rand(2);
				common.nobjectTypes[w.splinterType].create2(
					game,
					angle,
					0, 0,
					x, y,
					w.splinterColour - colorSub,
					cause);
			}
		}
		else
		{
			for(int i = 0; i < splinters; ++i)
			{
				int colorSub = game.rand(2);
				common.nobjectTypes[w.splinterType].create1(
					game,
					velX, velY,
					x, y,
					w.splinterColour - colorSub,
					cause);
			}
		}
	}
	
	if(w.dirtEffect >= 0)
	{
		int ix = ftoi(x), iy = ftoi(y);
		drawDirtEffect(common, game.rand, game.level, w.dirtEffect, ftoi(x) - 7, ftoi(y) - 7);
		if(game.settings->shadow)
			correctShadow(common, game.level, Rect(ix - 10, iy - 10, ix + 11, iy + 11));
	}
}

void WObject::process(Game& game)
{
	int iter = 0;
	bool bounced = false;
	bool doExplode = false;
	bool doRemove = false;
	
	Common& common = *game.common;
	Weapon& w = common.weapons[id];
	
	// As liero would do this while rendering, we try to do it as early as possible
	if(common.H[HRemExp]
	&& id == common.C[RemExpObject] - 1)
	{
		if(owner->pressed(Worm::Change)
		&& owner->pressed(Worm::Fire))
		{
			timeLeft = 0;
		}
	}
	
	do
	{
		++iter;
		x += velX;
		y += velY;
				
		if(w.shotType == 2)
		{
			fixed dirX = cosTable[curFrame];
			fixed dirY = sinTable[curFrame];
			fixed newVelX = dirX * w.speed / 100;
			fixed newVelY = dirY * w.speed / 100;
			
			if(owner->visible
			&& owner->pressed(Worm::Up))
			{
				newVelX += w.addSpeed * dirX / 100;
				newVelY += w.addSpeed * dirY / 100;
			}
			
			velX = ((velX * 8) + newVelX) / 9;
			velY = ((velY * 8) + newVelY) / 9; // TODO: Read from EXE
		}
		else if(w.shotType == 3)
		{
			fixed dirX = cosTable[curFrame];
			fixed dirY = sinTable[curFrame];
			fixed addVelX = dirX * w.addSpeed / 100;
			fixed addVelY = dirY * w.addSpeed / 100;
			
			velX += addVelX;
			velY += addVelY;
			
			if(w.distribution)
			{
				velX += game.rand(w.distribution * 2) - w.distribution; // TODO: We should do game.rand(w.distribution * 2) here, no? Original doesn't
				velY += game.rand(w.distribution * 2) - w.distribution;
			}
		}
		
		
		if(w.bounce > 0)
		{
			int ix = ftoi(x);
			int iy = ftoi(y);
			int inewX = ftoi(x + velX);
			int inewY = ftoi(y + velY);
			
			if(!game.level.inside(inewX, iy)
			|| game.pixelMat(inewX, iy).dirtRock())
			{
				if(w.bounce != 100)
				{
					velX = -velX * w.bounce / 100;
					velY = (velY * 4) / 5; // TODO: Read from EXE
				}
				else
					velX = -velX;
					
				bounced = true;
			}
			
			if(!game.level.inside(ix, inewY)
			|| game.pixelMat(ix, inewY).dirtRock())
			{
				if(w.bounce != 100)
				{
					velY = -velY * w.bounce / 100;
					velX = (velX * 4) / 5; // TODO: Read from EXE
				}
				else
					velY = -velY;
					
				bounced = true;
			}
		}
		
		if(w.multSpeed != 100)
		{
			velX = velX * w.multSpeed / 100;
			velY = velY * w.multSpeed / 100;
		}
		
		if(w.objTrailType >= 0
		&& (game.cycles % w.objTrailDelay) == 0)
		{
			common.sobjectTypes[w.objTrailType].create(game, ftoi(x), ftoi(y), owner);
		}
		
		if(w.partTrailObj >= 0
		&& (game.cycles % w.partTrailDelay) == 0)
		{
			if(w.partTrailType == 1)
			{
				common.nobjectTypes[w.partTrailObj].create1(
					game,
					velX / common.C[SplinterLarpaVelDiv], velY / common.C[SplinterLarpaVelDiv],
					x, y,
					0,
					owner);
			}
			else
			{
				int angle = game.rand(128);
				common.nobjectTypes[w.partTrailObj].create2(
					game,
					angle,
					velX / common.C[SplinterCracklerVelDiv], velY / common.C[SplinterCracklerVelDiv],
					x, y,
					0,
					owner);
			}
		}
		
		if(w.collideWithObjects)
		{
			for(Game::WObjectList::iterator i = game.wobjects.begin(); i != game.wobjects.end(); ++i)
			{
				if(i->id != id
				|| i->owner != owner)
				{
					if(x >= i->x - itof(2)
					&& x <= i->x + itof(2)
					&& y >= i->y - itof(2)
					&& y <= i->y + itof(2))
					{
						i->velX += velX * w.blowAway / 100;
						i->velY += velY * w.blowAway / 100;
					}
				}
			}
			
			for(Game::NObjectList::iterator i = game.nobjects.begin(); i != game.nobjects.end(); ++i)
			{
				if(i->id != id
				|| i->owner != owner)
				{
					if(x >= i->x - itof(2)
					&& x <= i->x + itof(2)
					&& y >= i->y - itof(2)
					&& y <= i->y + itof(2))
					{
						i->velX += velX * w.blowAway / 100;
						i->velY += velY * w.blowAway / 100;
					}
				}
			}
		}
		
		int inewX = ftoi(x + velX);
		int inewY = ftoi(y + velY);
		
		if(inewX < 0)
			x = 0;
		if(inewY < 0)
			y = 0;
		if(inewX >= game.level.width)
			x = itof(game.level.width - 1);
		if(inewY >= game.level.height)
			y = itof(game.level.height - 1);
			
		if(!game.level.inside(inewX, inewY)
		|| game.pixelMat(inewX, inewY).dirtRock())
		{
			if(w.bounce == 0)
			{
				if(w.explGround)
				{
					doExplode = true;
				}
				else
				{
					velX = 0;
					velY = 0;
				}
			}
		}
		else
		{
			velY += w.gravity; // The original tested w.gravity first, which doesn't seem like a gain
			
			if(w.numFrames > 0)
			{
				if((game.cycles & 7) == 0)
				{
					if(!w.loopAnim)
					{
						if(++curFrame > w.numFrames)
							curFrame = 0;
					}
					else
					{
						if(velX < 0)
						{
							if(--curFrame < 0)
								curFrame = w.numFrames;
						}
						else if(velX > 0)
						{
							if(++curFrame > w.numFrames)
								curFrame = 0;
						}
					}
				}
			}
		}
		
		if(w.timeToExplo > 0)
		{
			if(--timeLeft < 0)
				doExplode = true;
		}
		
		for(std::size_t i = 0; i < game.worms.size(); ++i)
		{
			Worm& worm = *game.worms[i];
			
			// TODO: The original tests wobjblood, which may not be 0 when w.bloodOnHit is.
			// Change to use that here too.
			
			if((w.hitDamage || w.blowAway || w.bloodOnHit || w.wormCollide)
			&& checkForSpecWormHit(ftoi(x), ftoi(y), w.detectDistance, worm))
			{
				worm.velX += (velX * w.blowAway) / 100;
				worm.velY += (velY * w.blowAway) / 100;
				
				worm.health -= w.hitDamage;
				if(worm.health <= 0) // Original has worm.health < 0 which is wrong
				{
					worm.lastKilledBy = owner;
				}
				
				int bloodAmount = w.bloodOnHit * game.settings->blood / 100;
				
				for(int i = 0; i < bloodAmount; ++i)
				{
					int angle = game.rand(128);
					common.nobjectTypes[6].create2(game, angle, velX / 3, velY / 3, x, y, 0, &worm);
				}
								
				if(w.hitDamage > 0
				&& worm.health > 0
				&& game.rand(3) == 0)
				{
					int snd = game.rand(3) + 18; // NOTE: MUST be outside the unpredictable branch below
					if(!game.soundPlayer->isPlaying(&worm))
					{
						game.soundPlayer->play(snd, &worm);
					}
				}
				
				if(w.wormCollide)
				{
					if(game.rand(w.wormCollide) == 0)
					{
						if(w.wormExplode)
							doExplode = true;
							
						doRemove = true;
					}
				}
			}
		}

		if(doExplode)
			blowUpObject(game, owner);
		else if(doRemove)
			game.wobjects.free(this);
	}
	while(w.shotType == Weapon::STLaser
	//&& !doExplode
	&& used // TEMP
	&& (iter < 8 || w.id == 28));
}

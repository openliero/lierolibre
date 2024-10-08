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

#include "nobject.hpp"
#include "game.hpp"
#include "gfx.hpp"
#include "sfx.hpp"
#include "bobject.hpp"
#include <iostream>

void NObjectType::create1(Game& game, fixed velX, fixed velY, int x, int y, int color, Worm* owner)
{
	NObject& obj = *game.nobjects.newObjectReuse();
	
	obj.id = id;
	obj.owner = owner;
	obj.x = x;
	obj.y = y;
	
	obj.velX = velX;
	obj.velY = velY;
	
	if(distribution)
	{
		obj.velX += distribution - game.rand(distribution * 2);
		obj.velY += distribution - game.rand(distribution * 2);
	}
	
	if(startFrame > 0)
	{
		obj.curFrame = game.rand(numFrames + 1);
	}
	else if(color != 0)
	{
		obj.curFrame = color;
	}
	else
	{
		obj.curFrame = colorBullets;
	}
	
	obj.timeLeft = timeToExplo;
	
	if(timeToExploV)
		obj.timeLeft -= game.rand(timeToExploV);
	
}

void NObjectType::create2(Game& game, int angle, fixed velX, fixed velY, fixed x, fixed y, int color, Worm* owner)
{
	NObject& obj = *game.nobjects.newObjectReuse();
	
	

	obj.id = id;
	obj.owner = owner;
	obj.x = x;
	obj.y = y;
	
	int realSpeed = speed - game.rand(speedV);
		
	obj.velX = (cosTable[angle] * realSpeed) / 100 + velX;
	obj.velY = (sinTable[angle] * realSpeed) / 100 + velY;
	
	if(distribution)
	{
		obj.velX += game.rand(distribution * 2) - distribution;
		obj.velY += game.rand(distribution * 2) - distribution;
	}
	
	obj.x += obj.velX;
	obj.y += obj.velY;
	
	if(startFrame > 0)
	{
		obj.curFrame = game.rand(numFrames + 1);
	}
	else if(color != 0)
	{
		obj.curFrame = color;
	}
	else
	{
		obj.curFrame = colorBullets;
	}
	
	obj.timeLeft = timeToExplo;
	
	if(timeToExploV)
		obj.timeLeft -= game.rand(timeToExploV);
}

void NObject::process(Game& game)
{
	Common& common = *game.common;
	
	bool bounced = false;
	bool doExplode = false;
	
	x += velX;
	y += velY;
	
	int inewX = ftoi(x + velX);
	int inewY = ftoi(y + velY);
	
	int ix = ftoi(x);
	int iy = ftoi(y);
	
	if(id >= 20 && id <= 21)
		inewY += 2; // Special flag exception, TODO: Check indexes of flags
		
	NObjectType& t = common.nobjectTypes[id];
		
	if(t.bounce > 0)
	{
		if(!game.level.inside(inewX, iy)
		|| game.pixelMat(inewX, iy).dirtRock())
		{
			velX = -velX * t.bounce / 100;
			velY = (velY * 4) / 5; // TODO: Read from EXE
			bounced = true;
		}
		
		if(!game.level.inside(ix, inewY)
		|| game.pixelMat(ix, inewY).dirtRock())
		{
			velY = -velY * t.bounce / 100;
			velX = (velX * 4) / 5; // TODO: Read from EXE
			bounced = true;
		}
		
		
	}
	
	if(t.bloodTrail
	&& t.bloodTrailDelay > 0
	&& (game.cycles % t.bloodTrailDelay) == 0)
	{
		game.createBObject(x, y, velX / 4, velY / 4); // TODO: Read from EXE
	}
	
	// Original didn't have this. Essential fix!
	inewX = ftoi(x + velX);
	inewY = ftoi(y + velY);
	
	if(id >= 20 && id <= 21)
		inewY += 2; // Special flag exception, TODO: Check indexes of flags
	
	if(inewX < 0) x = 0;
	if(inewY < 0) y = 0;
	if(inewX >= game.level.width) x = itof(game.level.width);
	if(inewY >= game.level.height) y = itof(game.level.height);
	
	if(!game.level.inside(inewX, inewY)
	|| game.pixelMat(inewX, inewY).dirtRock())
	{
		velX = 0;
		velY = 0;
		
		if(t.explGround)
		{
			if(t.startFrame > 0 && t.drawOnMap)
			{
				blitImageOnMap(
					common,
					game.level,
					common.smallSprites.spritePtr(t.startFrame + curFrame),
					ix - 3,
					iy - 3,
					7,
					7);
				if(game.settings->shadow)
					correctShadow(common, game.level, Rect(ix - 8, iy - 8, ix + 9, iy + 9)); // This seems like an overly large rectangle
			}
			
			doExplode = true;
		}
	}
	else
	{
		if(!bounced
		&& t.leaveObjDelay != 0
		&& t.leaveObj >= 0 // NOTE: AFAIK, this doesn't exist in Liero, but some TCs seem to forget to set leaveObjDelay to 0 when not using this trail
		&& (game.cycles % t.leaveObjDelay) == 0)
		{
			common.sobjectTypes[t.leaveObj].create(game, ftoi(x), ftoi(y), owner);
		}
		
		velY += t.gravity;
	}
	
	if(t.numFrames > 0)
	{
		if((game.cycles & 7) == 0) // TODO: Read from EXE
		{
			if(velX > 0)
			{
				++curFrame;
				if(curFrame > t.numFrames)
					curFrame = 0;
			}
			else if(velX < 0)
			{
				--curFrame;
				if(curFrame < 0)
					curFrame = t.numFrames;
			}
		}
	}
	
	if(t.timeToExplo > 0)
	{
		if(--timeLeft <= 0)
			doExplode = true;
	}
	
	if(!doExplode)
	{
		if(t.hitDamage > 0
		|| (id >= 20 && id <= 21)) // Flags
		{
			for(std::size_t i = 0; i < game.worms.size(); ++i)
			{
				Worm& w = *game.worms[i];
				
				if(checkForSpecWormHit(ftoi(x), ftoi(y), t.detectDistance, w))
				{
					w.velX += t.blowAway * velX / 100;
					w.velY += t.blowAway * velY / 100;
					w.health -= t.hitDamage;
					
					if(game.settings->gameMode == Settings::GMCtF)
					{
						/* TODO
						if(objnum == 21)
						{
						if(o == 1)
						{
						if(lastkilled == 0)
						{
						if(cGame::cWorm[1].flag == false)
						{
							cGame::cObject[w].m_iObjectNum = -1;
							cGame::cWorm[1].flag = true;
						} // 5BEC
						}
						}
						} else if(objnum == 22)
						{
						if(o == 0)
						{
						if(lastkilled == 1)
						{
						if(cGame::cWorm[0].flag == false)
						{
							cGame::cObject[w].m_iObjectNum = -1;
							cGame::cWorm[0].flag = true;
						} // 5C1D
						}
						}
						}
						*/
					}
					else if(game.settings->gameMode == Settings::GMSimpleCtF)
					{
						/*
						if(objnum == 21)
						{
						if(o == 1)
						{
						if(cGame::cWorm[1].flag == 0)
						{
						cGame::cObject[w].m_iObjectNum = -1;
						cGame::cWorm[1].flag = 1;
						} // 5C4E
						}
						} else if(objnum == 22)
						{
						if(o == 0)
						{
						if(cGame::cWorm[0].flag == 0)
						{
						cGame::cObject[w].m_iObjectNum = -1;
						cGame::cWorm[0].flag = 1;
						} // 5C78
						}
						}
						*/
					}
					
					if(w.health <= 0)
						w.lastKilledBy = owner;
						
					if(t.hitDamage > 0)
					{
						if(w.health > 0
						&& game.rand(3) == 0)
						{
							int snd = 18 + game.rand(3); // NOTE: MUST be outside the unpredictable branch below
							if(!game.soundPlayer->isPlaying(&w))
							{
								game.soundPlayer->play(snd, &w);
							}
						}
					}
					
					int blood = t.bloodOnHit * game.settings->blood / 100;
					
					for(int i = 0; i < blood; ++i)
					{
						int angle = game.rand(128); 
						common.nobjectTypes[6].create2(
							game,
							angle,
							velX / 3, velY / 3,
							x, y,
							0,
							owner);
					}
										
					if(t.wormExplode)
						doExplode = true;
					if(t.wormDestroy
					&& !doExplode)
					{
						if(used) // Temp
							game.nobjects.free(this);
					}
				}
				
			}
		}
	}
	
	if(doExplode)
	{
		if(t.createOnExp >= 0)
		{
			common.sobjectTypes[t.createOnExp].create(game, ftoi(x), ftoi(y), owner);
		}
		
		if(t.dirtEffect >= 0)
		{
			drawDirtEffect(common, game.rand, game.level, t.dirtEffect, ftoi(x) - 7, ftoi(y) - 7);
			
			if(game.settings->shadow)
				correctShadow(common, game.level, Rect(ftoi(x) - 10, ftoi(y) - 10, ftoi(x) + 11, ftoi(y) + 11));
		}
		
		if(t.splinterAmount > 0)
		{
			for(int i = 0; i < t.splinterAmount; ++i)
			{
				int angle = game.rand(128);
				int colorSub = game.rand(2);
				common.nobjectTypes[t.splinterType].create2(
					game,
					angle,
					0, 0,
					x, y,
					t.splinterColour - colorSub,
					owner);
			}
		}
		
		if(used) // Temp
			game.nobjects.free(this);
	}
}

/*


   
*/
   

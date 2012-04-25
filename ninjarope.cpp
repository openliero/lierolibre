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

#include "worm.hpp"
#include "constants.hpp"
#include "game.hpp"
#include "gfx/color.hpp"
#include "math.hpp"
//#include <cmath>

void Ninjarope::process(Worm& owner)
{
	Game& game = owner.game;
	Common& common = *game.common;
	
	if(out)
	{
		x += velX;
		y += velY;
		
		int ix = ftoi(x), iy = ftoi(y);
		
		anchor = 0;
		for(std::size_t i = 0; i < game.worms.size(); ++i)
		{
			Worm& w = *game.worms[i];
			
			if(&w != &owner
			&& checkForSpecWormHit(ix, iy, 1, w))
			{
				anchor = &w;
				break;
			}
		}
		
		fixed forceX, forceY;
		
		fixed diffX = x - owner.x;
		fixed diffY = y - owner.y;
		
		forceX = (diffX << common.C[NRForceShlX]) / common.C[NRForceDivX];
		forceY = (diffY << common.C[NRForceShlY]) / common.C[NRForceDivY];
		
		curLen = (vectorLength(ftoi(diffX), ftoi(diffY)) + 1) << common.C[NRForceLenShl];
		
		if(ix <= 0
		|| ix >= game.level.width - 1
		|| iy <= 0
		|| iy >= game.level.height - 1
		|| common.materials[game.level.pixel(ix, iy)].dirtRock())
		{
			if(!attached)
			{
				length = common.C[NRAttachLength];
				attached = true;
				
				if(game.level.inside(ix, iy))
				{
					PalIdx pix = game.level.pixel(ix, iy);
					
					if(common.materials[pix].anyDirt())
					{
						for(int i = 0; i < 11; ++i) // TODO: Check 11 and read from exe
						{
							common.nobjectTypes[2].create2(
								game,
								game.rand(128),
								0, 0,
								x, y,
								pix,
								&owner);
						}
					}
				}
			}
			
			
			velX = 0;
			velY = 0;
		}
		else if(anchor)
		{
			if(!attached)
			{
				length = common.C[NRAttachLength]; // TODO: Should this value be separate from the non-worm attaching?
				attached = true;
			}
			
			if(curLen > length)
			{
				anchor->velX -= forceX / curLen;
				anchor->velY -= forceY / curLen;
			}
			
			velX = anchor->velX;
			velY = anchor->velY;
			x = anchor->x;
			y = anchor->y;
		}
		else
		{
			attached = false;
		}
		
		if(attached)
		{
			// curLen can't be 0

			if(curLen > length)
			{
				owner.velX += forceX / curLen;
				owner.velY += forceY / curLen;
			}
		}
		else
		{
			velY += common.C[NinjaropeGravity];

			if(curLen > length)
			{
				velX -= forceX / curLen;
				velY -= forceY / curLen;
			}
		}
	}
}

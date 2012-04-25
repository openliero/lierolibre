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

#include "bobject.hpp"

#include "gfx/color.hpp"
#include "game.hpp"
#include "constants.hpp"

void Game::createBObject(fixed x, fixed y, fixed velX, fixed velY)
{
	BObject& obj = *bobjects.newObjectReuse();
	
	obj.color = rand(common->C[NumBloodColours]) + common->C[FirstBloodColour];
	obj.x = x;
	obj.y = y;
	obj.velX = velX;
	obj.velY = velY;
}

bool BObject::process(Game& game)
{
	Common& common = *game.common;
	
	x += velX;
	y += velY;
	
	int ix = ftoi(x);
	int iy = ftoi(y);
	
	if(!game.level.inside(ix, iy))
	{
		return false;
	}
	else
	{
		PalIdx c = game.level.pixel(ix, iy);
		Material m = common.materials[c];
		
		if(m.background())
			velY += common.C[BObjGravity];
			
		if((c >= 1 && c <= 2)
		|| (c >= 77 && c <= 79)) // TODO: Read from EXE
		{
			game.level.pixel(ix, iy) = 77 + game.rand(3);
			return false;
		}
		/* This can't happen!
		else if(iy >= game.level.height)
		{
			// Nothing
		}*/
		else if(m.anyDirt())
		{
			game.level.pixel(ix, iy) = 82 + game.rand(3);
			return false;
		}
		else if(m.rock())
		{
			game.level.pixel(ix, iy) = 85 + game.rand(3);
			return false;
		}
	}
	
	return true;
}

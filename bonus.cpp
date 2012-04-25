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

#include "bonus.hpp"
#include "game.hpp"
#include "constants.hpp"
#include <iostream>
#include <cstdlib>

void Bonus::process(Game& game)
{
	Common& common = *game.common;
	
	y += velY;
	
	int ix = ftoi(x), iy = ftoi(y);
	
	if(game.level.inside(ix, iy + 1)
	&& common.materials[game.level.pixel(ix, iy + 1)].background())
	{
		velY += common.C[BonusGravity];
	}
		
	int inewY = ftoi(y + velY);
	if(inewY < 0 || inewY >= game.level.height - 1
	|| common.materials[game.level.pixel(ix, inewY)].dirtRock())
	{
		velY = -(velY * common.C[BonusBounceMul]) / common.C[BonusBounceDiv];
		
		if(std::abs(velY) < 100) // TODO: Read from EXE
			velY = 0;
	}
	
	if(--timer <= 0)
	{
		common.sobjectTypes[common.bonusSObjects[frame]].create(game, ix, iy, 0);
		if(used)
			game.bonuses.free(this);
	}
}

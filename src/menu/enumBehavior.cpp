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


#include "enumBehavior.hpp"

#include "menu.hpp"
#include "menuItem.hpp"
#include "../common.hpp"
#include "../text.hpp"
#include "../sfx.hpp"

bool EnumBehavior::onLeftRight(Menu& menu, int item, int dir)
{
	if(brokenLeftRight)
		return false; // Left/right doesn't work for this item
	if(dir > 0)
		sfx.play(25);
	else
		sfx.play(26);
		
	change(menu, item, dir);
		
	return false;
}

int EnumBehavior::onEnter(Menu& menu, int item)
{
	sfx.play(27);
	
	change(menu, item, 1);
	return -1;
}

void EnumBehavior::change(Menu& menu, int item, int dir)
{
	uint32_t range = max - min + 1;
	uint32_t newV = ((v + dir + range - min) % range) + min;
	
	if(newV != v)
	{
		v = newV;
		onUpdate(menu, item);
	}
}

void EnumBehavior::onUpdate(Menu& menu, int item)
{
	MenuItem& i = menu.items[item];
	i.value = toString(v);
	i.hasValue = true;
}

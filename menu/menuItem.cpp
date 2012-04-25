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

#include "menuItem.hpp"

#include "../common.hpp"
#include "../gfx.hpp"

void MenuItem::draw(Common& common, int x, int y, bool selected, bool disabled, bool centered, int valueOffsetX)
{
	int wid = common.font.getDims(string);
	int valueWid = common.font.getDims(value);
	if(centered)
		x -= (wid >> 1);
	
	if(selected)
	{
		drawRoundedBox(x, y, 0, 7, wid);
		if(hasValue)
			drawRoundedBox(x + valueOffsetX - (valueWid >> 1), y, 0, 7, valueWid);
	}
	else
	{
		common.font.drawText(string, x + 3, y + 2, 0);
		if(hasValue)
			common.font.drawText(value, x + valueOffsetX - (valueWid >> 1) + 3, y + 2, 0);
	}
	
	PalIdx c;
	
	if(disabled)
		c = disColour;
	else if(selected)
		c = 168;
	else
		c = color;
		
	common.font.drawText(string, x + 2, y + 1, c);
	if(hasValue)
		common.font.drawText(value, x + valueOffsetX - (valueWid >> 1) + 2, y + 1, c);
}


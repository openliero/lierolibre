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


#include "hiddenMenu.hpp"

#include "arrayEnumBehavior.hpp"

#include "../gfx.hpp"
#include "../sfx.hpp"

struct ExtensionsSwitchBehavior : BooleanSwitchBehavior
{
	ExtensionsSwitchBehavior(Common& common, bool& v)
	: BooleanSwitchBehavior(common, v)
	{
	}
	
	void onUpdate(Menu& menu, int item)
	{
		BooleanSwitchBehavior::onUpdate(menu, item);
		
		gfx.updateExtensions(v);
	}
};

struct Depth32Behavior : BooleanSwitchBehavior
{
	Depth32Behavior(Common& common, bool& v)
	: BooleanSwitchBehavior(common, v)
	{
	}
	
	int onEnter(Menu& menu, int item)
	{
		BooleanSwitchBehavior::onEnter(menu, item);
		gfx.setVideoMode();
		return -1;
	}
	
	bool onLeftRight(Menu& menu, int item, int dir)
	{
		BooleanSwitchBehavior::onLeftRight(menu, item, dir);
		gfx.setVideoMode();
		return true;
	}
};

struct ReplaySelectBehavior : ItemBehavior
{
	int onEnter(Menu& menu, int item)
	{
		sfx.play(27);
		int ret = gfx.selectReplay();
		sfx.play(27);
		return ret;
	}
};

static std::string const scaleFilterNames[Settings::SfMax] =
{
	"Nearest",
	"Scale2X"
};

ItemBehavior* HiddenMenu::getItemBehavior(Common& common, int item)
{
	switch(item)
	{
		case Extensions:
			return new ExtensionsSwitchBehavior(common, gfx.settings->extensions);
		case RecordReplays:
			return new BooleanSwitchBehavior(common, gfx.settings->recordReplays);
		case Replays:
			return new ReplaySelectBehavior();
		case LoadPowerLevels:
			return new BooleanSwitchBehavior(common, gfx.settings->loadPowerlevelPalette);
		case ScalingFilter:
			return new ArrayEnumBehavior(common, gfx.settings->scaleFilter, scaleFilterNames);
		case FullscreenW:
			return new IntegerBehavior(common, gfx.settings->fullscreenW, 0, 9999, 0);
		case FullscreenH:
			return new IntegerBehavior(common, gfx.settings->fullscreenH, 0, 9999, 0);
		case Depth32:
			return new Depth32Behavior(common, gfx.settings->depth32);
		default:
			return Menu::getItemBehavior(common, item);
	}
}

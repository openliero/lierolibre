/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
 * Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
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

#ifndef LIERO_GAME_HPP
#define LIERO_GAME_HPP

#include <vector>
#include "level.hpp"
#include "settings.hpp"
#include "weapon.hpp"
#include "sobject.hpp"
#include "nobject.hpp"
#include "bobject.hpp"
#include "rand.hpp"
#include "bonus.hpp"
#include "sfx.hpp"
#include "constants.hpp"
#include <string>
#include <gvl/resman/shared_ptr.hpp>
#include "common.hpp"

struct Viewport;
struct Worm;


struct Game
{
	Game(gvl::shared_ptr<Common> common, gvl::shared_ptr<Settings> settings);
	~Game();

	void onKey(Uint32 key, bool state);
	Worm* findControlForKey(uint32_t key, Worm::Control& control);
	void releaseControls();
	void processFrame();
	void gameLoop();
	void focus();
	void updateSettings();

	void createBObject(fixed x, fixed y, fixed velX, fixed velY);
	void createBonus();

	void clearViewports();
	void addViewport(Viewport*);
	void processViewports();
	void drawViewports(bool isReplay = false);
	void clearWorms();
	void addWorm(Worm*);
	void resetWorms();
	void draw(bool isReplay = false);
	void startGame();
	bool isGameOver();
	void createDefaults();

	Material pixelMat(int x, int y)
	{
		return common->materials[level.pixel(x, y)];
	}

	Level level;

	gvl::shared_ptr<Common> common;
	gvl::shared_ptr<SoundPlayer> soundPlayer;
	gvl::shared_ptr<Settings> settings;
	int screenFlash;
	bool gotChanged;
	Worm* lastKilled; // Last killed worm  !CLONING
	bool paused;
	int cycles;
	Rand rand;

	std::vector<Viewport*> viewports;
	std::vector<Worm*> worms;

	typedef ExactObjectList<Bonus, 99> BonusList;
	typedef ExactObjectList<WObject, 600> WObjectList;
	typedef ExactObjectList<SObject, 700> SObjectList;
	typedef ExactObjectList<NObject, 600> NObjectList;
	typedef FastObjectList<BObject> BObjectList;
	BonusList bonuses;
	WObjectList wobjects;
	SObjectList sobjects;
	NObjectList nobjects;
	BObjectList bobjects;
};

bool checkRespawnPosition(Game& game, int x2, int y2, int oldX, int oldY, int x, int y);

//extern Game game;

#endif // LIERO_GAME_HPP


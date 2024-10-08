/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
 * Copyright (c) 2011-2012, Martin Erik Werner <martinerikwerner@gmail.com>
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

#ifndef LIERO_GFX_HPP
#define LIERO_GFX_HPP

#include <SDL/SDL.h>
#include <gvl/resman/shared_ptr.hpp>
#include <gvl/math/rect.hpp>

#include <cstdio>
#include <cassert>

#include "gfx/font.hpp"
#include "gfx/blit.hpp"
#include "gfx/color.hpp"
#include "menu/menu.hpp"
#include "menu/hiddenMenu.hpp"
#include "rect.hpp"
#include "rand.hpp"
#include "keys.hpp"
#include "settings.hpp"
#include "common.hpp"



struct Key
{
	Key(int sym, char ch)
	: sym(sym), ch(ch)
	{
	}

	int sym;
	char ch;
};



struct Game;
struct Controller;
struct Gfx;

struct PlayerMenu : Menu
{
	PlayerMenu(int x, int y)
	: Menu(x, y)
	{
	}

	virtual void drawItemOverlay(Common& common, int item, int x, int y, bool selected, bool disabled);

	virtual ItemBehavior* getItemBehavior(Common& common, int item);

	gvl::shared_ptr<WormSettings> ws;
};

struct SettingsMenu : Menu
{
	SettingsMenu(int x, int y)
	: Menu(x, y)
	{
	}

	virtual ItemBehavior* getItemBehavior(Common& common, int item);
};

enum
{
	MaResumeGame = 0,
	MaNewGame = 1,
	MaSettings = 2,
	MaQuit = 3,
	MaReplay = 4
};

struct Joystick {
	SDL_Joystick *sdlJoystick;
	bool btnState[MaxJoyButtons];

	void clearState() {
		for ( int i = 0; i < MaxJoyButtons; ++i ) btnState[i] = false;
	}
};

struct Gfx
{
	Gfx();

	void init();
	void setVideoMode();
	void setMaxVideoMode();
	void loadPalette();
	void loadMenus();
	void loadMenusFromCFG(std::string cfgFilePath);
	void writeMenusToCFG(std::string cfgFilePath);

	void process(Controller* controller = 0);
	void flip();

	void clear();
	void clearKeys();

	unsigned char& getScreenPixel(int x, int y)
	{
		return (static_cast<unsigned char*>(screenPixels) + y*screenPitch)[x];
	}


	/*
	bool testKeyOnce(int key)
	{
		bool state = keys[key];
		keys[key] = false;
		return state;
	}

	bool testKey(int key)
	{
		return keys[key];
	}

	void releaseKey(int key)
	{
		keys[key] = false;
	}*/

	bool testKeyOnce(Uint32 key)
	{
		bool state = dosKeys[key];
		dosKeys[key] = false;
		return state;
	}

	bool testKey(Uint32 key)
	{
		return dosKeys[key];
	}

	void releaseKey(Uint32 key)
	{
		dosKeys[key] = false;
	}

	void pressKey(Uint32 key)
	{
		dosKeys[key] = true;
	}

	void setKey(Uint32 key, bool state)
	{
		dosKeys[key] = state;
	}

	void toggleKey(Uint32 key)
	{
		dosKeys[key] = !dosKeys[key];
	}

	bool testSDLKeyOnce(SDLKey key)
	{
		Uint32 k = SDLToDOSKey(key);
		return k ? testKeyOnce(k) : false;
	}

	bool testSDLKey(SDLKey key)
	{
		Uint32 k = SDLToDOSKey(key);
		return k ? testKey(k) : false;
	}

	void releaseSDLKey(SDLKey key)
	{
		Uint32 k = SDLToDOSKey(key);
		if(k)
			dosKeys[k] = false;
	}



	SDL_keysym waitForKey();
	uint32_t waitForKeyEx();
	std::string getKeyName( uint32_t key );

	void saveSettings();
	bool loadSettings();

	void saveOPT(std::string);
	void loadOPT(std::string);

	void processEvent(SDL_Event& ev, Controller* controller = 0);
	//void settingEnter(int item);
	//void settingLeftRight(int change, int item);
	void updateSettingsMenu();
	//void setWormColours();
	int menuLoop();
	void mainLoop();
	void drawBasicMenu(/*int curSel*/);
	void playerSettings(int player);
	//void inputString(std::string& dest, std::size_t maxLen, int x, int y, bool onlyDigits = false);
	bool inputString(std::string& dest, std::size_t maxLen, int x, int y, int (*filter)(int) = 0, std::string const& prefix = "", bool centered = true);
	void inputInteger(int& dest, int min, int max, std::size_t maxLen, int x, int y);
	void selectLevel();
	int  selectReplay();
	void selectProfile(WormSettings& ws);
	void updateExtensions(bool enabled);
	void weaponOptions();
	void infoBox(std::string const& text, int x = 320/2, int y = 200/2, bool clearScreen = true);
	int fitScreen(int backW, int backH, int scrW, int scrH, int& offsetX, int& offsetY);

	Menu mainMenu;
	SettingsMenu settingsMenu;
	PlayerMenu playerMenu;
	HiddenMenu hiddenMenu;

	Menu* curMenu;
	std::string settingsFile; // Currently loaded settings file
	gvl::shared_ptr<Settings> settings;

	Palette pal;
	Palette origpal;

	//bool keys[SDLK_LAST];
	bool dosKeys[177];
	SDL_Surface* screen;
	SDL_Surface* back;
	std::vector<PalIdx> frozenScreen;
	unsigned char* screenPixels;
	unsigned int screenPitch;


	bool running;
	bool fullscreen;
	int fadeValue;
	Uint32 lastFrame;
	int menuCyclic;
	int desktopH, desktopW, windowW, windowH, storedWindowH, storedWindowW;
	int prevMag; // Previous magnification used for drawing
	gvl::rect lastUpdateRect; // Last region that was updated when flipping
	Rand rand; // PRNG for things that don't affect the game
	gvl::shared_ptr<Common> common;
	std::unique_ptr<Controller> controller;

	std::vector<Joystick> joysticks;
};

extern Gfx gfx;

#endif // LIERO_GFX_HPP

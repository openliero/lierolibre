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


#include "localController.hpp"

#include "../keys.hpp"
#include "../gfx.hpp"
#include "../reader.hpp"
#include "../filesystem.hpp"

#include <cctype>

LocalController::LocalController(gvl::shared_ptr<Common> common, gvl::shared_ptr<Settings> settings)
: game(common, settings)
, state(StateInitial)
, fadeValue(0)
, goingToMenu(false)
{
	game.createDefaults();
}

LocalController::~LocalController()
{
	endRecord();
}

void LocalController::onKey(int key, bool keyState)
{
	Worm::Control control;
	Worm* worm = game.findControlForKey(key, control);
	if(worm)
	{
		worm->cleanControlStates.set(control, keyState);
		
		if(control < Worm::MaxControl)
		{
			// Only real controls 
			worm->setControlState(control, keyState);
		}
		
		if(worm->cleanControlStates[WormSettings::Dig])
		{
			worm->press(Worm::Left);
			worm->press(Worm::Right);
		}
		else
		{
			if(!worm->cleanControlStates[Worm::Left])
				worm->release(Worm::Left);
			if(!worm->cleanControlStates[Worm::Right])
				worm->release(Worm::Right);
		}
	}
			
	if(key == DkEscape && !goingToMenu)
	{
		fadeValue = 31;
		goingToMenu = true;
	}
}

// Called when the controller loses focus. When not focused, it will not receive key events among other things.
void LocalController::unfocus()
{
	if(replay.get())
		replay->unfocus();
	if(state == StateWeaponSelection)
		ws->unfocus();
}

// Called when the controller gets focus.
void LocalController::focus()
{
	if(state == StateGameEnded)
	{
		goingToMenu = true;
		fadeValue = 0;
		return;
	}
	if(state == StateWeaponSelection)
		ws->focus();
	if(replay.get())
		replay->focus();
	if(state == StateInitial)
		changeState(StateWeaponSelection);
	game.focus();
	goingToMenu = false;
	fadeValue = 0;
}

bool LocalController::process()
{
	if(state == StateWeaponSelection)
	{
		if(ws->processFrame())
			changeState(StateGame);
	}
	else if(state == StateGame || state == StateGameEnded)
	{
		int realFrameSkip = inverseFrameSkip ? !(cycles % frameSkip) : frameSkip;
		for(int i = 0; i < realFrameSkip && (state == StateGame || state == StateGameEnded); ++i)
		{
			for(std::size_t i = 0; i < game.worms.size(); ++i)
			{
				Worm& worm = *game.worms[i];
				if(worm.ai.get())
					worm.ai->process();
			}
			if(replay.get())
			{
				try
				{
					replay->recordFrame();
				}
				catch(std::runtime_error& e)
				{
					Console::writeWarning(std::string("Error recording replay frame: ") + e.what());
					Console::writeWarning("Replay recording aborted");
					replay.reset();
				}
			}
			game.processFrame();
			
			if(game.isGameOver())
			{
				changeState(StateGameEnded);
			}
		}
	}
	
	//CommonController::process();
	
	if(goingToMenu)
	{
		if(fadeValue > 0)
			fadeValue -= 1;
		else
		{
			if(state == StateGameEnded)
				endRecord();
			return false;
		}
	}
	else
	{
		if(fadeValue < 33)
		{
			fadeValue += 1;
		}
	}
	
	return true;
}

void LocalController::draw()
{
	if(state == StateWeaponSelection)
	{
		ws->draw();
	}
	else if(state == StateGame || state == StateGameEnded || state == StateInitial)
	{
		game.draw();
	}
	gfx.fadeValue = fadeValue;
}

void LocalController::changeState(State newState)
{
	if(state == newState)
		return;

	// NOTE: We prepare new state before destroying the old.
	// e.g. weapon selection is destroyed first after we successfully
	// started recording.
	
	// NOTE: Must do this here before starting recording!
	if(state == StateWeaponSelection)
	{
		ws->finalize();
	}
	
	if(newState == StateWeaponSelection)
	{
		ws.reset(new WeaponSelection(game));
	}
	else if(newState == StateGame)
	{
		// NOTE: This must be done before the replay recording starts below
		for(std::size_t i = 0; i < game.worms.size(); ++i)
		{
			Worm& worm = *game.worms[i];
			worm.lives = game.settings->lives;
		}
		
		game.startGame();
		if(game.settings->extensions && game.settings->recordReplays)
		{
			try
			{
				std::time_t ticks = std::time(0);
				std::tm* now = std::localtime(&ticks);
				
				char buf[512];
				std::strftime(buf, sizeof(buf), " %Y-%m-%d %H.%M.%S.lrp", now);
				
				std::string prefix;
				for(std::size_t i = 0; i < 2; ++i)
				{
					Worm& worm = *game.worms[i];
					std::string const& name = worm.settings->name;
					int chars = 0;
					
					if(i > 0)
						prefix.push_back('-');
					for(std::size_t c = 0; c < name.size() && chars < 4; ++c, ++chars)
					{
						unsigned char ch = (unsigned char)name[c];
						if(std::isalnum(ch))
							prefix.push_back(ch);
					}
					
					
				}
				std::string path = joinPath(data_path->configdir(), prefix + buf);
				replay.reset(new ReplayWriter(gvl::stream_ptr(new gvl::fstream(path.c_str(), "wb"))));
				replay->beginRecord(game);
			}
			catch(std::runtime_error& e)
			{
				//Console::writeWarning();
				gfx.infoBox(std::string("Error starting replay recording: ") + e.what());
				goingToMenu = true;
				fadeValue = 0;
				return;
			}
		}
		
	}
	else if(newState == StateGameEnded)
	{
		if(!goingToMenu)
		{
			fadeValue = 180;
			goingToMenu = true;
		}
	}
	
	if(state == StateWeaponSelection)
	{
		fadeValue = 33;
		ws.reset();
	}
	
	state = newState;
}

void LocalController::endRecord()
{
	if(replay.get())
	{
		replay.reset();
	}
}
	
void LocalController::swapLevel(Level& newLevel)
{
	currentLevel()->swap(newLevel);
}

Level* LocalController::currentLevel()
{
	return &game.level;
}

Game* LocalController::currentGame()
{
	return &game;
}
	
bool LocalController::running()
{
	return state != StateGameEnded && state != StateInitial;
}

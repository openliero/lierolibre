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

#include "replayController.hpp"

#include "../game.hpp"

ReplayController::ReplayController(gvl::shared_ptr<Common> common, gvl::stream_ptr source)
: state(StateInitial)
, fadeValue(0)
, goingToMenu(false)
, replay(new ReplayReader(source))
, common(common)
{
}

void ReplayController::onKey(int key, bool keyState)
{
	if(key == DkEscape && !goingToMenu)
	{
		fadeValue = 31;
		goingToMenu = true;
	}
}

// Called when the controller loses focus. When not focused, it will not receive key events among other things.
void ReplayController::unfocus()
{
}

// Called when the controller gets focus.
void ReplayController::focus()
{
	if(state == StateGameEnded)
	{
		goingToMenu = true;
		fadeValue = 0;
		return;
	}
	if(state == StateInitial)
	{
		try
		{
			game = replay->beginPlayback(common);
		}
		catch(std::runtime_error& e)
		{
			//Console::writeWarning(std::string("Error starting replay playback: ") + e.what());
			gfx.infoBox(std::string("Error starting replay playback: ") + e.what());
			goingToMenu = true;
			fadeValue = 0;
			return;
		}
		// Changing state first when game is available
		changeState(StateGame);
	}
	game->focus();
	goingToMenu = false;
	fadeValue = 0;
}

bool ReplayController::process()
{
	if(state == StateGame || state == StateGameEnded)
	{
		int realFrameSkip = inverseFrameSkip ? !(cycles % frameSkip) : frameSkip;
		for(int i = 0; i < realFrameSkip && (state == StateGame || state == StateGameEnded); ++i)
		{
			if(replay.get())
			{
				try
				{
					if(!replay->playbackFrame())
					{
						// End of replay
						changeState(StateGameEnded);
					}
				}
				catch(gvl::stream_error& e)
				{
					gfx.infoBox(std::string("Stream error in replay: ") + e.what());
					//Console::writeWarning(std::string("Stream error in replay: ") + e.what());
					changeState(StateGameEnded);
				}
				catch(gvl::archive_check_error& e)
				{
					gfx.infoBox(std::string("Archive error in replay: ") + e.what());
					//Console::writeWarning(std::string("Archive error in replay: ") + e.what());
					changeState(StateGameEnded);
				}
			}
			game->processFrame();
		}
		
		if(game->isGameOver()
		&& !goingToMenu)
		{
			fadeValue = 180;
			goingToMenu = true;
		}
	}
	
	CommonController::process();
	
	if(goingToMenu)
	{
		if(fadeValue > 0)
			fadeValue -= 1;
		else
			return false;
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

void ReplayController::draw()
{
	if(state == StateGame || state == StateGameEnded)
	{
		game->draw(true);
	}
	gfx.fadeValue = fadeValue;
}

void ReplayController::changeState(State newState)
{
	if(state == newState)
		return;
	
	if(newState == StateGame)
		game->startGame();
	else if(newState == StateGameEnded)
	{
		if(!goingToMenu)
		{
			fadeValue = 180;
			goingToMenu = true;
		}
		replay.reset();
	}

	state = newState;
}
	
void ReplayController::swapLevel(Level& newLevel)
{
	currentLevel()->swap(newLevel);
}

Level* ReplayController::currentLevel()
{
	if(game.get() && replay.get())
		return &game->level;
	return 0;
}

Game* ReplayController::currentGame()
{
	return game.get();
}


bool ReplayController::running()
{
	return state != StateGameEnded && state != StateInitial;
}

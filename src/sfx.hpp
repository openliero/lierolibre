/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
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

#ifndef LIERO_SFX_HPP
#define LIERO_SFX_HPP

#if !DISABLE_SOUND
#include <SDL/SDL_mixer.h>
#endif
#include <vector>
#include <gvl/resman/shared_ptr.hpp>

struct Sfx
{
	struct ChannelInfo
	{
		ChannelInfo()
		: id(0)
		{
		}

		void* id; // ID of the sound playing on this channel
	};

	Sfx()
	: initialized(false)
	{
	}
	~Sfx();

	void init();
	void deinit();
	void loadFromSND();

	void play(int sound, void* id = 0, int loops = 0);
	bool isPlaying(void* id);
	void playOn(int channel, int sound, void* id, int loops = 0);
	void stop(void* id);
#if !DISABLE_SOUND
	std::vector<Mix_Chunk> sounds;
	ChannelInfo channelInfo[8];
#endif
	bool initialized;
};

extern Sfx sfx;

struct SoundPlayer : gvl::shared
{
	virtual void play(int sound, void* id = 0, int loops = 0) = 0;
	virtual bool isPlaying(void* id) = 0;
	virtual void playOn(int channel, int sound, void* id, int loops = 0) = 0;
	virtual void stop(void* id) = 0;
};

struct DefaultSoundPlayer : SoundPlayer
{
	void play(int sound, void* id = 0, int loops = 0)
	{
		sfx.play(sound, id, loops);
	}

	bool isPlaying(void* id)
	{
		return sfx.isPlaying(id);
	}

	void playOn(int channel, int sound, void* id, int loops = 0)
	{
		return sfx.playOn(channel, sound, id, loops);
	}

	void stop(void* id)
	{
		sfx.stop(id);
	}
};

struct NullSoundPlayer : SoundPlayer
{
	void play(int sound, void* id, int loops)
	{
	}

	bool isPlaying(void* id)
	{
		return false;
	}

	void playOn(int channel, int sound, void* id, int loops)
	{
	}

	void stop(void* id)
	{
	}
};

#endif // LIERO_SFX_HPP

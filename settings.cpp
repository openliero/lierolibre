/*
 * Copyright (c) 2010, Erik Lindroos <gliptic@gmail.com>
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

#include "settings.hpp"

#include "reader.hpp"
#include "keys.hpp"
#include "gfx.hpp"
#include "filesystem.hpp"

#include <gvl/io/fstream.hpp>
#include <gvl/serialization/context.hpp>
#include <gvl/serialization/archive.hpp>

#include <gvl/crypt/gash.hpp>

int const Settings::wormAnimTab[] =
{
	0,
	7,
	0,
	14
};

Extensions::Extensions()
: extensions(false)
, recordReplays(true)
, loadPowerlevelPalette(true)
, scaleFilter(Settings::SfNearest)
, depth32(true)
, bloodParticleMax(700)
, fullscreenW(640)
, fullscreenH(480)
{
}

Settings::Settings()
: maxBonuses(4)
, blood(100)
, timeToLose(600)
, flagsToWin(20)
, gameMode(0)
, shadow(true)
, loadChange(false)
, namesOnBonuses(false)
, regenerateLevel(false)
, lives(15)
, loadingTime(100)
, randomLevel(true)
, map(true)
, screenSync(true)

{
	std::memset(weapTable, 0, sizeof(weapTable));

	wormSettings[0].reset(new WormSettings);
	wormSettings[1].reset(new WormSettings);

	wormSettings[0]->color = 32;
	wormSettings[1]->color = 41;

	unsigned char defControls[2][7] =
	{
		{0x13, 0x21, 0x20, 0x22, 0x1D, 0x2A, 0x38},
		{0xA0, 0xA8, 0xA3, 0xA5, 0x75, 0x90, 0x36}
	};

	unsigned char defRGB[2][3] =
	{
		{26, 26, 63},
		{15, 43, 15}
	};

	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			wormSettings[i]->controls[j] = defControls[i][j];
		}

		for(int j = 0; j < 3; ++j)
		{
			wormSettings[i]->rgb[j] = defRGB[i][j];
		}
	}
}

bool Settings::load(std::string const& path)
{
	FILE* opt = tolerantFOpen(path.c_str(), "rb");

	if(!opt)
		return false;

	std::size_t size = fileLength(opt);

	if(size < 155)
		return false; // .dat is too short

	gvl::octet_stream_reader reader(gvl::stream_ptr(new gvl::fstream(opt)));
	gvl::default_serialization_context context;

	archive_liero(gvl::in_archive<gvl::default_serialization_context>(reader, context), *this);


	return true;
}

gvl::gash::value_type& Settings::updateHash()
{
	gvl::default_serialization_context context;
	gvl::hash_accumulator<gvl::gash> ha;

	archive(gvl::out_archive<gvl::default_serialization_context, gvl::hash_accumulator<gvl::gash> >(ha, context), *this);

	ha.flush();
	hash = ha.final();
	return hash;
}

void Settings::save(std::string const& path)
{
	FILE* opt = fopen(path.c_str(), "wb");
	gvl::octet_stream_writer writer(gvl::stream_ptr(new gvl::fstream(opt)));

	gvl::default_serialization_context context;

	archive_liero(gvl::out_archive<gvl::default_serialization_context>(writer, context), *this);
}

void Settings::generateName(WormSettings& ws)
{
	FILE* f = fopen(data_path->file("NAMES.DAT").c_str(), "rb");

	if(!f)
		return;

	std::vector<std::string> names;

	std::size_t len = fileLength(f);

	std::vector<char> chars(len);

	checkedFread(&chars[0], 1, len, f);

	fclose(f);

	std::size_t begin = 0;
	for(std::size_t i = 0; i < len; ++i)
	{
		if(chars[i] == '\r'
		|| chars[i] == '\n')
		{
			if(i > begin)
			{
				names.push_back(std::string(chars.begin() + begin, chars.begin() + i));
			}

			begin = i + 1;
		}
	}

	if(!names.empty())
	{
		ws.name = names[gfx.rand(Uint32(names.size()))];
		ws.randomName = true;
	}
}

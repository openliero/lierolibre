/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
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

#include "reader.hpp"
#include <SDL/SDL.h>
#include <map>
#include <stdexcept>
#include <gvl/support/platform.hpp> // For GVL_WINDOWS
#include "filesystem.hpp"

std::string lieroOPT;
std::string lieroCFG;

DataPath* data_path = NULL;

namespace
{

struct ReaderFile
{
	unsigned int lastTouch;
	FILE* f;
};

typedef std::map<std::string, ReaderFile> ReaderFileMap;

std::string lieroEXE;
std::string lieroCHR;
std::string lieroSND;

ReaderFileMap readerFiles;

void closeReaderFile(ReaderFileMap::iterator i)
{
	fclose(i->second.f);
	readerFiles.erase(i);
}


}

FILE* openFile(std::string const& name)
{
	ReaderFileMap::iterator i = readerFiles.find(name);
	if(i != readerFiles.end())
	{
		i->second.lastTouch = SDL_GetTicks();
		return i->second.f;
	}

	FILE* f = tolerantFOpen(name.c_str(), "rb");
	if(!f)
		throw std::runtime_error("Could not open '" + name + '\'');
	ReaderFile& rf = readerFiles[name];
	rf.f = f;
	rf.lastTouch = SDL_GetTicks();
	return f;
}

FILE* openLieroEXE()
{
	return openFile(lieroEXE);
}

FILE* openLieroSND()
{
	return openFile(lieroSND);
}

FILE* openLieroCHR()
{
	return openFile(lieroCHR);
}

void processReader()
{
	unsigned int now = SDL_GetTicks();
	for(ReaderFileMap::iterator i = readerFiles.begin(); i != readerFiles.end(); )
	{
		ReaderFileMap::iterator cur = i;
		++i;

		if((now - cur->second.lastTouch) > 5000)
		{
			closeReaderFile(cur);
		}
	}
}

void closeAllCachedFiles()
{
	for(ReaderFileMap::iterator i = readerFiles.begin(); i != readerFiles.end(); )
	{
		ReaderFileMap::iterator cur = i;
		++i;
		closeReaderFile(cur);
	}
}

void setLieroPath(std::string const& path)
{
	delete data_path;
	data_path = new DataPath(path);

	lieroCHR = data_path->file("LIERO.CHR");
	lieroSND = data_path->file("LIERO.SND");
	lieroOPT = data_path->file("LIERO.OPT");
}

void setLieroEXE(std::string const& path)
{
	lieroEXE = path;
}

// $HOME takes priority, copies to $HOME, needs setLieroPath() first
void setLieroCFG(std::string const& path)
{
	DataPath dp_tmp(path);
#if GVL_WINDOWS
	lieroCFG = dp_tmp.file("lierocfg.txt");
#else
	lieroCFG = dp_tmp.file("liero.cfg");
#endif
}

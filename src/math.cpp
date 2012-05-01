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

#include "math.hpp"
#include "reader.hpp"
#include <cmath>
#include <gvl/math/ieee.hpp>

#include "configHelper.hpp"


// TODO: Move to Common or hardcode, I don't think any TC is or would like to change these tables
fixed sinTable[128];
fixed cosTable[128];

int vectorLength(int x, int y)
{
	// x*x + y*y fits exactly in a double, so we don't need
	// to use gA.
	return int(gSqrt(double(x*x) + double(y*y)));
}

void loadTablesFromEXE()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C41E, SEEK_SET);

	for(int i = 0; i < 128; ++i)
	{
		cosTable[i] = readSint32(exe);
		sinTable[i] = readSint32(exe);
	}
}

void loadTablesFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &tables = cfg.lookup("Tables");

	for(int i = 0; i < 128; ++i)
	{
		sinTable[i] = tables["sinTable"][i];
		cosTable[i] = tables["cosTable"][i];
	}
}

void writeTablesToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	ConfigHelper cfgHelp;
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &tables = cfgHelp.getSubgroup(root, "Tables");

	libconfig::Setting &sintables = cfgHelp.mkArray(tables, "sinTable");
	for(int i = 0; i < 128; ++i)
	{
		sintables.add(libconfig::Setting::TypeInt) = sinTable[i];
	}

	libconfig::Setting &costables = cfgHelp.mkArray(tables, "cosTable");
	for(int i = 0; i < 128; ++i)
	{
		costables.add(libconfig::Setting::TypeInt) = cosTable[i];
	}

	cfg.writeFile(cfgFilePath.c_str());
}


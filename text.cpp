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

#include "text.hpp"
#include <cctype>

char const* timeToString(int sec)
{
	static char ret[6];
	
	ret[0] = '0' + (sec / 600);
	ret[1] = '0' + (sec % 600) / 60;
	ret[2] = ':';
	ret[3] = '0' + (sec % 60) / 10;
	ret[4] = '0' + (sec % 10);
	ret[5] = 0;
	
	return ret;
}

char const* timeToStringEx(int ms)
{
	static char ret[9];
	
	ret[0] = '0' + (ms / 600000);
	ret[1] = '0' + (ms % 600000) / 60000;
	ret[2] = ':';
	ret[3] = '0' + (ms % 60000) / 10000;
	ret[4] = '0' + (ms % 10000) / 1000;
	ret[5] = '.';
	ret[6] = '0' + (ms % 1000) / 100;
	ret[7] = '0' + (ms % 100) / 10;
	ret[8] = 0;
	
	return ret;
}

int safeToUpper(char ch)
{
	return std::toupper(static_cast<unsigned char>(ch));
}

bool ciCompare(std::string const& a, std::string const& b)
{
	if(a.size() != b.size())
		return false;
		
	for(std::size_t i = 0; i < a.size(); ++i)
	{
		if(safeToUpper(a[i]) != safeToUpper(b[i]))
			return false;
	}
	
	return true;
}

bool ciLess(std::string const& a, std::string const& b)
{
	for(std::size_t i = 0; i < a.size(); ++i)
	{
		if(i >= b.size()) // a is longer, thus a > b
			return false;
		int ach = safeToUpper(a[i]);
		int bch = safeToUpper(b[i]); 
		if(ach < bch)
			return true;
		else if(ach > bch)
			return false;
	}
	
	return b.size() > a.size(); // if b is longer, then a < b, otherwise a == b
}

int unicodeToDOS(int c)
{
	int table[][2] =
	{
		{229, 0x86},
		{228, 0x84},
		{246, 0x94},
		{197, 0x8f},
		{196, 0x8e},
		{214, 0x99}
	};
	
	for(std::size_t i = 0; i < sizeof(table) / sizeof(*table); ++i)
	{
		if(table[i][0] == c)
			return table[i][1];
	}
	
	return c & 0x7f; // Return ASCII
}

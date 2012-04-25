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

#ifndef LIERO_TEXT_HPP
#define LIERO_TEXT_HPP

#include <string>
#include <cstdio>

inline std::string toString(int v)
{
	char buf[20];
	std::sprintf(buf, "%d", v);
	return buf;
}

char const* timeToString(int sec);
char const* timeToStringEx(int ms);

inline void rtrim(std::string& str)
{
	std::string::size_type e = str.find_last_not_of(" \t\r\n");
	if(e == std::string::npos)
		str.clear();
	else
		str.erase(e + 1);
}

inline void findReplace(std::string& str, std::string const& find, std::string const& replace)
{
	std::string::size_type p = str.find(find);
	if(p != std::string::npos)
		str.replace(p, find.size(), replace);
}

bool ciCompare(std::string const& a, std::string const& b);
bool ciLess(std::string const& a, std::string const& b);
int unicodeToDOS(int c);

#endif // LIERO_TEXT_HPP

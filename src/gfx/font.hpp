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

#ifndef UUID_B06B65B783A849C7B4E509A9676180F8
#define UUID_B06B65B783A849C7B4E509A9676180F8

#include <vector>
#include <string>

struct Font
{
	struct Char
	{
		unsigned char data[8*7];
		int width;
	};

	Font()
	: chars(250)
	{
	}

	void loadFromEXE();
	void loadFromCFG(std::string cfgFilePath);
	void writeToCFG(std::string cfgFilePath);
	void drawText(char const* str, std::size_t len, int x, int y, int color);
	int getDims(char const* str, std::size_t len, int* height = 0);
	void drawChar(unsigned char ch, int x, int y, int color);

	void drawText(std::string const& str, int x, int y, int color)
	{
		drawText(str.data(), str.size(), x, y, color);
	}

	int getDims(std::string const& str, int* height = 0)
	{
		return getDims(str.data(), str.size(), height);
	}

	void drawFramedText(std::string const& text, int x, int y, int color);

	std::vector<Char> chars;
};

#endif // UUID_B06B65B783A849C7B4E509A9676180F8

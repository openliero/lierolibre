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

#include "console.hpp"
//#include "game.hpp"
//#include "constants.hpp"
#include <gvl/support/platform.hpp>
#include <iostream>

#if GVL_WIN32
#include "windows.h"

namespace Console
{

namespace
{
HANDLE stdIn;
HANDLE stdOut;
CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
}

WORD dosToWinForeColours[16] =
{
	0,
	FOREGROUND_BLUE,
	FOREGROUND_GREEN,
	FOREGROUND_BLUE | FOREGROUND_GREEN,
	FOREGROUND_RED,
	FOREGROUND_RED  | FOREGROUND_BLUE,
	FOREGROUND_RED  | FOREGROUND_GREEN,
	FOREGROUND_RED  | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY,
	
	FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FOREGROUND_BLUE  | FOREGROUND_GREEN  | FOREGROUND_INTENSITY,
	FOREGROUND_RED   | FOREGROUND_INTENSITY,
	FOREGROUND_RED   | FOREGROUND_BLUE   | FOREGROUND_INTENSITY,
	FOREGROUND_RED   | FOREGROUND_GREEN  | FOREGROUND_INTENSITY,
	FOREGROUND_RED   | FOREGROUND_GREEN  | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};

WORD dosToWinBackColours[16] =
{
	0,
	BACKGROUND_BLUE,
	BACKGROUND_GREEN,
	BACKGROUND_BLUE | BACKGROUND_GREEN,
	BACKGROUND_RED,
	BACKGROUND_RED  | BACKGROUND_BLUE,
	BACKGROUND_RED  | BACKGROUND_GREEN,
	BACKGROUND_RED  | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY,
	
	BACKGROUND_BLUE  | BACKGROUND_INTENSITY,
	BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BACKGROUND_BLUE  | BACKGROUND_GREEN  | BACKGROUND_INTENSITY,
	BACKGROUND_RED   | BACKGROUND_INTENSITY,
	BACKGROUND_RED   | BACKGROUND_BLUE   | BACKGROUND_INTENSITY,
	BACKGROUND_RED   | BACKGROUND_GREEN  | BACKGROUND_INTENSITY,
	BACKGROUND_RED   | BACKGROUND_GREEN  | BACKGROUND_BLUE | BACKGROUND_INTENSITY
};

void init()
{
	stdIn = GetStdHandle(STD_INPUT_HANDLE);
	stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		
	GetConsoleScreenBufferInfo(stdOut, &bufferInfo);
}

void setAttributes(int attr)
{
	WORD f = dosToWinForeColours[attr & 0xf] | dosToWinBackColours[(attr >> 4) & 0xf];
	
	SetConsoleTextAttribute(stdOut, f);
}

int getAttributes()
{
	WORD const allFore = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD const allBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
	
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(stdOut, &info);
	
	int fore = 0x7;
	int back = 0x0;
	
	for(int i = 0; i < 16; ++i)
	{
		if((info.wAttributes & allFore) == dosToWinForeColours[i])
			fore = i;
		if((info.wAttributes & allBack) == dosToWinBackColours[i])
			back = i;
	}
	
	return (back << 4) | fore;
}

void write(std::string const& str)
{
	DWORD dummy;
	WriteConsole(stdOut, str.data(), DWORD(str.size()), &dummy, 0);
}

void writeLine(std::string const& str)
{
	DWORD dummy;
	WriteConsole(stdOut, str.data(), DWORD(str.size()), &dummy, 0);
	WriteConsole(stdOut, "\r\n", 2, &dummy, 0);
}

void writeTextBar(std::string const& str, int barFormat)
{
	char const* ptr = str.data();
	std::size_t len = str.size();
	if(ptr[0] == 0)
	{
		setAttributes(ptr[1] + (ptr[2] << 4));
		ptr += 3;
		len -= 3;
	}
		
	DWORD dummy;
	WriteConsole(stdOut, ptr, DWORD(len), &dummy, 0);
	
	setAttributes(barFormat);
	
	int left = bufferInfo.dwSize.X - int(len);
	
	for(int i = 0; i < left; ++i)
		WriteConsole(stdOut, " ", 1, &dummy, 0);
}

void waitForAnyKey()
{
	FlushConsoleInputBuffer(stdIn);
	INPUT_RECORD input[1];	
	do
	{
		DWORD read = 0;
		ReadConsoleInput(stdIn, input, 1, &read);
	}
	while(input[0].EventType != KEY_EVENT);
}

void clear()
{
	DWORD dummy;
	COORD ul = {0, 0};
	
	FillConsoleOutputAttribute(
		stdOut, 0, int(bufferInfo.dwSize.X) * bufferInfo.dwSize.Y,
		ul, &dummy);
	
	FillConsoleOutputCharacter(
		stdOut, 32, int(bufferInfo.dwSize.X) * bufferInfo.dwSize.Y,
		ul, &dummy);
		
	SetConsoleCursorPosition(stdOut, ul);
}

}

#else

namespace Console
{

void init()
{
	
}

void setAttributes(int attr)
{

}

int getAttributes()
{
	return 0x07;
}

void write(std::string const& str)
{
	std::cout << str;
}

void writeLine(std::string const& str)
{
	std::cout << str << std::endl;
}

void writeTextBar(std::string const& str, int barFormat)
{
	std::cout << str << std::endl;
}

void waitForAnyKey()
{
	
}

void clear()
{
	
}

}

#endif

namespace Console
{

void writeWarning(std::string const& str)
{
	Console::LocalAttributes la(0x4f);
	Console::write("WARNING: ");
	Console::writeLine(str);
}

}

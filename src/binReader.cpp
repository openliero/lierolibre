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

// Compile via: g++ -c -lSDL binReader.cpp

#include <stdexcept>

// Needed for cross-platform *int32 definitions
#include <SDL/SDL.h>

#include "binReader.hpp"

using namespace std;

void checkedFread(void* ptr, size_t size, size_t count, FILE* f)
{
	if(fread(ptr, size, count, f) != count)
		throw runtime_error("fread failed to read fully");
}

string readPascalString(FILE* f)
{
	unsigned char length;
	checkedFread(&length, 1, 1, f);
	char txt[256];
	checkedFread(txt, 1, length, f);
	return string(txt, length);
}

string readPascalString(FILE* f, unsigned char fieldLen)
{
	char txt[256];
	checkedFread(txt, 1, fieldLen, f);
	unsigned char length = static_cast<unsigned char>(txt[0]);
	return string(txt + 1, length);
}

void writePascalString(FILE* f, string const& str, unsigned char fieldLen)
{
	int len = int(str.size() < fieldLen ? str.size() : fieldLen - 1);
	size_t zeroes = fieldLen - 1 - len;
	fputc(len, f);
	fwrite(str.data(), 1, len, f);
	for(size_t i = 0; i < zeroes; ++i)
		fputc(0, f);
}

string readPascalStringAt(FILE* f, int location)
{
	unsigned char length;
	fseek(f, location, SEEK_SET);
	checkedFread(&length, 1, 1, f);
	char txt[256];
	checkedFread(txt, 1, length, f);
	return string(txt, length);
}

Uint32 readUint8(FILE* f)
{
	unsigned char temp[1];
	checkedFread(temp, 1, 1, f);
	return temp[0];
}

void writeUint8(FILE* f, Uint32 v)
{
	fputc(v & 0xff, f);
}

Sint32 readSint8(FILE* f)
{
	char temp[1];
	checkedFread(temp, 1, 1, f);
	return temp[0];
}

Uint32 readUint16(FILE* f)
{
	unsigned char temp[2];
	checkedFread(temp, 1, 2, f);
	return temp[0] + (temp[1] << 8);
}

void writeUint16(FILE* f, Uint32 v)
{
	fputc(v & 0xff, f);
	fputc((v >> 8) & 0xff, f);
}

Sint32 readSint16(FILE* f)
{
	unsigned char temp[2];
	checkedFread(temp, 1, 2, f);
	return temp[0] + (static_cast<char>(temp[1]) << 8);
}

Uint32 readUint32(FILE* f)
{
	unsigned char temp[4];
	checkedFread(temp, 1, 4, f);
	return temp[0] + (temp[1] << 8) + (temp[2] << 16) + (temp[3] << 24);
}

Sint32 readSint32(FILE* f)
{
	unsigned char temp[4];
	checkedFread(temp, 1, 4, f);
	return temp[0] + (temp[1] << 8) + (temp[2] << 16) + (static_cast<char>(temp[3]) << 24);
}


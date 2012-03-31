// Compile via: g++ -c -ovarreader -lSDL varreader.cpp

#include <stdexcept>

// Needed for cross-platform *int32 definitions
#include <SDL/SDL.h>

#include "varreader.hpp"

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


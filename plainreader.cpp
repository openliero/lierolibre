// Compile & run via: g++ -oplainreader plainreader.cpp && ./plainreader

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

// Needed for cross-platform *int32 definitions
#include <SDL/SDL.h>

#include "plainreader.hpp"

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

struct Material
{
	enum {
		Dirt = 1<<0,
		Dirt2 = 1<<1,
		Rock = 1<<2,
		Background = 1<<3,
		SeeShadow = 1<<4,
		WormM = 1<<5
	};

	bool dirt() { return (flags & Dirt) != 0; }
	bool dirt2() { return (flags & Dirt2) != 0; }
	bool rock() { return (flags & Rock) != 0; }
	bool background() { return (flags & Background) != 0; }
	bool seeShadow() { return (flags & SeeShadow) != 0; }

	// Constructed
	bool dirtRock() { return (flags & (Dirt | Dirt2 | Rock)) != 0; }
	bool anyDirt() { return (flags & (Dirt | Dirt2)) != 0; }
	bool dirtBack() { return (flags & (Dirt | Dirt2 | Background)) != 0; }
	bool worm() { return (flags & WormM) != 0; }

	int flags;
};

int stuff(void)
{

	FILE* exe = fopen("../liero-data/LIERO.EXE", "rb");
	if (exe == NULL)
		throw runtime_error("unable to open LIERO.EXE");

	string copyright1 = readPascalStringAt(exe, 0xFB60);

	Material materials[256];
	fseek(exe, 0x01C2E0, SEEK_SET);
	for(int i = 0; i < 256; ++i)
		materials[i].flags = 0;
	unsigned char bits[32];

	for(int i = 0; i < 5; ++i) {
		checkedFread(bits, 1, 32, exe);

		for(int j = 0; j < 256; ++j) {
			int bit = ((bits[j >> 3] >> (j & 7)) & 1);
			materials[j].flags |= bit << i;
		}
	}

	fseek(exe, 0x01AEA8, SEEK_SET);

	checkedFread(bits, 1, 32, exe);

	for(int j = 0; j < 256; ++j) {
		int bit = ((bits[j >> 3] >> (j & 7)) & 1);
		materials[j].flags |= bit << 5;
	}

	fclose(exe);
	cout << "copyright1 =  " << copyright1 << endl;
	cout << "materials = ";
	for(int i = 0; i < 256; ++i)
		cout << materials[i].flags << " ";
	cout << endl;
	return 1;
}


int main(int argc, char *argv[])
{
	stuff();
}

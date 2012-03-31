// Compile & run via: g++ varreader plainreader.cpp -oplainreader && ./plainreader

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>

// Needed for cross-platform *int32 definitions
#include <SDL/SDL.h>

#include "plainreader.hpp"
#include "varreader.hpp"

using namespace std;

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

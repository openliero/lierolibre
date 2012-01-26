// Compile & run via: g++ -oplainreader plainreader.cpp && ./plainreader
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include "plainreader.hpp"
using namespace std;

void checkedFread(void* ptr, std::size_t size, std::size_t count, FILE* f)
{
	if(fread(ptr, size, count, f) != count)
		throw std::runtime_error("fread failed to read fully");
}

string readPascalStringAt(FILE* f, int location)
{
	unsigned char length;
	fseek(f, location, SEEK_SET);
	checkedFread(&length, 1, 1, f);
	char txt[256];
	checkedFread(txt, 1, length, f);
	return std::string(txt, length);
}

int getstuff(void)
{
	FILE* exe = fopen("../liero-data/LIERO.EXE", "rb");
	string copyright1 = readPascalStringAt(exe, 0xFB60);
	fclose(exe);
	cout << "copyright1: " << copyright1 << endl;
	return 1;
}


int main(int argc, char *argv[])
{
	getstuff();
}

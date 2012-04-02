// Compile & run via: g++ varreader plainreader.cpp -oplainreader && ./plainreader

#include <iostream>
#include <stdexcept>

// Needed for cross-platform *int32 definitions
#include <SDL/SDL.h>

// INI config file
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

//int->string conversion
#include <sstream>

#include "plainreader.hpp"
#include "varreader.hpp"

bool Material::dirt() { return (flags & Dirt) != 0; }
bool Material::dirt2() { return (flags & Dirt2) != 0; }
bool Material::rock() { return (flags & Rock) != 0; }
bool Material::background() { return (flags & Background) != 0; }
bool Material::seeShadow() { return (flags & SeeShadow) != 0; }

// Constructed
bool Material::dirtRock() { return (flags & (Dirt | Dirt2 | Rock)) != 0; }
bool Material::anyDirt() { return (flags & (Dirt | Dirt2)) != 0; }
bool Material::dirtBack() { return (flags & (Dirt | Dirt2 | Background)) != 0; }
bool Material::worm() { return (flags & WormM) != 0; }

int stuff(void)
{

	FILE* exe = fopen("../liero-data/LIERO.EXE", "rb");
	if (exe == NULL)
		throw std::runtime_error("unable to open LIERO.EXE");

	std::string copyright1 = readPascalStringAt(exe, 0xFB60);

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

	namespace bpt = boost::property_tree;
	bpt::ptree root;
	bpt::ptree stuff;
	bpt::ptree cfgmaterials;

	stuff.put("copyright1", copyright1);

	for (int i = 0; i < 256; ++i) {
		std::stringstream ss;
		std::string number;
		ss << i;
		number = ss.str();
		cfgmaterials.put(number, materials[i].flags);
	}

	root.push_front(bpt::ptree::value_type("stuff", stuff));
	root.push_front(bpt::ptree::value_type("cfgmaterials",
							cfgmaterials));

	write_ini(std::cout, root);

	std::cout << "copyright1 =  " << copyright1 << std::endl;
	std::cout << "materials = ";
	for(int i = 0; i < 256; ++i)
		std::cout << materials[i].flags << " ";
	std::cout << std::endl;
	return 1;
}


int main(int argc, char *argv[])
{
	stuff();
}

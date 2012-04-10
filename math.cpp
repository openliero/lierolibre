#include "math.hpp"
#include "reader.hpp"
#include <cmath>
#include <gvl/math/ieee.hpp>


// TODO: Move to Common or hardcode, I don't think any TC is or would like to change these tables
fixed sinTable[128];
fixed cosTable[128];

int vectorLength(int x, int y)
{
	// x*x + y*y fits exactly in a double, so we don't need
	// to use gA.
	return int(gSqrt(double(x*x) + double(y*y)));
}

void loadTablesFromEXE()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C41E, SEEK_SET);

	for(int i = 0; i < 128; ++i)
	{
		cosTable[i] = readSint32(exe);
		sinTable[i] = readSint32(exe);
	}
}

void loadTablesFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath);
	const libconfig::Setting &tables = cfg.lookup("Tables");

	for(int i = 0; i < 128; ++i)
	{
		sinTable[i] = tables["sinTable"][i];
		cosTable[i] = tables["cosTable"][i];
	}
}
void loadTablesFromCFG()
{
	loadTablesFromCFG("liero.cfg");
}

void writeTablesToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath);
	ConfigHelper cfgHelp;
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &tables = cfgHelp.getSubgroup(root, "Tables");

	libconfig::Setting &sintables = cfgHelp.getArray(tables, "sinTable");
	for(int i = 0; i < 128; ++i)
	{
		sintables.add(Setting::TypeInt) = sinTable[i];
	}

	libconfig::Setting &costables = cfgHelp.getArray(tables, "cosTable");
	for(int i = 0; i < 128; ++i)
	{
		costables.add(Setting::TypeInt) = cosTable[i];
	}
}
void writeTablesToCFG()
{
	writeTablesToCFG("liero.cfg")
}


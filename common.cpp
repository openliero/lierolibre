#include "common.hpp"
#include <libconfig.h++>

#include "reader.hpp"
#include "rand.hpp"
#include "gfx.hpp"
#include "to_string.hpp"
#include "configHelper.hpp"

int Common::fireConeOffset[2][7][2] =
{
	{{-3, 1}, {-4, 0}, {-4, -2}, {-4, -4}, {-3, -5}, {-2, -6}, {0, -6}},
	{{3, 1}, {4, 0}, {4, -2}, {4, -4}, {3, -5}, {2, -6}, {0, -6}},
};

int stoneTab[3][4] =
{
	{98, 60, 61, 62},
	{63, 75, 85, 86},
	{89, 90, 97, 96}
};

void Texts::loadFromEXE()
{
	FILE* exe = openLieroEXE();

	random = readPascalStringAt(exe, 0xD6E3);
	random2 = readPascalStringAt(exe, 0xD413);
	regenLevel = readPascalStringAt(exe, 0xD41A);
	reloadLevel = readPascalStringAt(exe, 0xD42D);

	copyright1 = readPascalStringAt(exe, 0xFB60);
	// Get rid of NULL + 2 garbage bytes...
	copyright1.erase(0, 3);

	copyright2 = readPascalStringAt(exe, 0xE693);
	saveoptions = readPascalStringAt(exe, 0xE6BB);
	loadoptions = readPascalStringAt(exe, 0xE6CC);
	curOptNoFile = readPascalStringAt(exe, 0xE6DD);
	curOpt = readPascalStringAt(exe, 0xE6FA);

	fseek(exe, 0x1B2BA, SEEK_SET);
	for(int i = 0; i < 4; ++i)
	{
		gameModes[i] = readPascalString(exe, 17);
	}

	gameModeSpec[0] = readPascalStringAt(exe, 0xD3EC);
	gameModeSpec[1] = readPascalStringAt(exe, 0xD3F2);
	gameModeSpec[2] = readPascalStringAt(exe, 0xD3FF);

	onoff[0] = readPascalStringAt(exe, 0x1AE84);
	onoff[1] = readPascalStringAt(exe, 0x1AE88);

	controllers[0] = readPascalStringAt(exe, 0x1B204);
	controllers[1] = readPascalStringAt(exe, 0x1B20A);

	fseek(exe, 0x1B2FE, SEEK_SET);
	for(int i = 0; i < 3; ++i)
	{
		weapStates[i] = readPascalString(exe, 13);
	}

	fseek(exe, 0x209A6, SEEK_SET);
	for(int i = 1; i < 177; ++i) // First key starts at 1
	{
		keyNames[i] = readPascalString(exe, 13);
	}

	selWeap = readPascalStringAt(exe, 0xA9C0);
	levelRandom = readPascalStringAt(exe, 0xA9D5);
	levelIs1 = readPascalStringAt(exe, 0xA9E3);
	levelIs2 = readPascalStringAt(exe, 0xA9EC);
	randomize = readPascalStringAt(exe, 0xA9F4);
	done = readPascalStringAt(exe, 0xA9EE);

	reloading = readPascalStringAt(exe, 0x7583);
	pressFire = readPascalStringAt(exe, 0x7590);

	kills = readPascalStringAt(exe, 0x75A4);
	lives = readPascalStringAt(exe, 0x75AC);

	selLevel = readPascalStringAt(exe, 0xD6F2);

	weapon = readPascalStringAt(exe, 0xD700);
	availability = readPascalStringAt(exe, 0xD707);
	noWeaps = readPascalStringAt(exe, 0xD714);

	fseek(exe, 0xFC5B, SEEK_SET);
	copyrightBarFormat = readUint8(exe);
}

void Texts::loadFromCFG()
{
	libconfig::Config cfg;
	cfg.readFile("liero.cfg");
	const libconfig::Setting &texts = cfg.lookup("Texts");

	random = (char const*)texts["random"];
	random2 = (char const*)texts["random2"];
	regenLevel = (char const*)texts["regenLevel"];
	reloadLevel = (char const*)texts["reloadLevel"];

	copyright1 = (char const*)texts["copyright1"];
	copyright2 = (char const*)texts["copyright2"];
	saveoptions = (char const*)texts["saveoptions"];
	loadoptions = (char const*)texts["loadoptions"];
	curOptNoFile = (char const*)texts["curOptNoFile"];
	curOpt = (char const*)texts["curOpt"];

	const libconfig::Setting &sgmodes = texts["gameModes"];
	for(int i = 0; i < 4; ++i)
	{
		gameModes[i] = (char const*)sgmodes["gameModes" + to_string(i)];
	}

	const libconfig::Setting &sgmspec = texts["gameModeSpec"];
	gameModeSpec[0] = (char const*)sgmspec["gameModeSpec0"];
	gameModeSpec[1] = (char const*)sgmspec["gameModeSpec1"];
	gameModeSpec[2] = (char const*)sgmspec["gameModeSpec2"];

	const libconfig::Setting &sonoff = texts["onoff"];
	onoff[0] = (char const*)sonoff["onoff0"];
	onoff[1] = (char const*)sonoff["onoff1"];

	const libconfig::Setting &scontrollers = texts["controllers"];
	controllers[0] = (char const*)scontrollers["controllers0"];
	controllers[1] = (char const*)scontrollers["controllers1"];

	const libconfig::Setting &swstates = texts["weapStates"];
	for(int i = 0; i < 3; ++i)
	{
		 weapStates[i] = (char const*)swstates["weapStates" + to_string(i)];
	}

	const libconfig::Setting &sknames = texts["keyNames"];
	for(int i = 1; i < 177; ++i) // First key starts at 1
	{
		keyNames[i] = (char const*)sknames["keyNames" + to_string(i)];
	}

	selWeap = (char const*)texts["selWeap"];
	levelRandom = (char const*)texts["levelRandom"];
	levelIs1 = (char const*)texts["levelIs1"];
	levelIs2 = (char const*)texts["levelIs2"];
	randomize = (char const*)texts["randomize"];
	done = (char const*)texts["done"];

	reloading = (char const*)texts["reloading"];
	pressFire = (char const*)texts["pressFire"];

	kills = (char const*)texts["kills"];
	lives = (char const*)texts["lives"];

	selLevel = (char const*)texts["selLevel"];

	weapon = (char const*)texts["weapon"];
	availability = (char const*)texts["availability"];
	noWeaps = (char const*)texts["noWeaps"];

	copyrightBarFormat = (int)texts["copyrightBarFormat"];
}

void Texts::writeToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &texts = cfgHelp.getSubgroup(root, "Texts");

	cfgHelp.put(texts, "random", random);
	cfgHelp.put(texts, "random2", random2);
	cfgHelp.put(texts, "regenLevel", regenLevel);
	cfgHelp.put(texts, "reloadLevel", reloadLevel);

	cfgHelp.put(texts, "copyright1", copyright1);
	cfgHelp.put(texts, "copyright2", copyright2);
	cfgHelp.put(texts, "saveoptions", saveoptions);
	cfgHelp.put(texts, "loadoptions", loadoptions);
	cfgHelp.put(texts, "curOptNoFile", curOptNoFile);
	cfgHelp.put(texts, "curOpt", curOpt);

	libconfig::Setting &sgmodes = cfgHelp.getSubgroup(texts, "gameModes");
	for(int i = 0; i < 4; ++i)
	{
		cfgHelp.put(sgmodes, "gameModes" + to_string(i), gameModes[i]);
	}

	libconfig::Setting &sgmspec = cfgHelp.getSubgroup(texts, "gameModeSpec");
	cfgHelp.put(sgmspec, "gameModeSpec0", gameModeSpec[0]);
	cfgHelp.put(sgmspec, "gameModeSpec1", gameModeSpec[1]);
	cfgHelp.put(sgmspec, "gameModeSpec2", gameModeSpec[2]);

	libconfig::Setting &sonoff = cfgHelp.getSubgroup(texts, "onoff");
	cfgHelp.put(sonoff, "onoff0", onoff[0]);
	cfgHelp.put(sonoff, "onoff1", onoff[1]);

	libconfig::Setting &scontrollers = cfgHelp.getSubgroup(texts, "controllers");
	cfgHelp.put(scontrollers, "controllers0", controllers[0]);
	cfgHelp.put(scontrollers, "controllers1", controllers[1]);

	libconfig::Setting &swstates = cfgHelp.getSubgroup(texts, "weapStates");
	for(int i = 0; i < 3; ++i)
	{
		cfgHelp.put(swstates, "weapStates" + to_string(i), weapStates[i]);
	}

	libconfig::Setting &sknames = cfgHelp.getSubgroup(texts, "keyNames");
	for(int i = 1; i < 177; ++i) // First key starts at 1
	{
		cfgHelp.put(sknames, "keyNames" + to_string(i), keyNames[i]);
	}

	cfgHelp.put(texts, "selWeap", selWeap);
	cfgHelp.put(texts, "levelRandom", levelRandom);
	cfgHelp.put(texts, "levelIs1", levelIs1);
	cfgHelp.put(texts, "levelIs2", levelIs2);
	cfgHelp.put(texts, "randomize", randomize);
	cfgHelp.put(texts, "done", done);

	cfgHelp.put(texts, "reloading", reloading);
	cfgHelp.put(texts, "pressFire", pressFire);

	cfgHelp.put(texts, "kills", kills);
	cfgHelp.put(texts, "lives", lives);

	cfgHelp.put(texts, "selLevel", selLevel);

	cfgHelp.put(texts, "weapon", weapon);
	cfgHelp.put(texts, "availability", availability);
	cfgHelp.put(texts, "noWeaps", noWeaps);

	cfgHelp.put(texts, "copyrightBarFormat", copyrightBarFormat);

	cfg.writeFile(cfgFilePath.c_str());
}

void Texts::writeToCFG(void)
{
	writeToCFG("liero.cfg");
}

void Common::loadPalette()
{
	FILE* exe = openLieroEXE();

	std::fseek(exe, 132774, SEEK_SET);

	exepal.read(exe);


	std::fseek(exe, 0x1AF0C, SEEK_SET);
	for(int i = 0; i < 4; ++i)
	{
		colorAnim[i].from = readUint8(exe);
		colorAnim[i].to = readUint8(exe);
	}
}

void Common::loadPaletteFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &palette = cfg.lookup("Palette");

	exepal.readFromCFG(cfgFilePath);

	const libconfig::Setting &scanim = palette["colorAnim"];
	for(int i = 0; i < 4; ++i)
	{
		colorAnim[i].from = (int)scanim["colorAnim" + to_string(i) + "from"];
		colorAnim[i].to = (int)scanim["colorAnim" + to_string(i) + "to"];
	}
}

void Common::loadPaletteFromCFG()
{
	loadPaletteFromCFG("liero.cfg");
}

void Common::writePaletteToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;

	exepal.writeToCFG(cfgFilePath);

	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &palette = cfgHelp.getSubgroup(root, "Palette");
	libconfig::Setting &scanim = cfgHelp.getSubgroup(palette, "colorAnim");
	for(int i = 0; i < 4; ++i)
	{
		cfgHelp.put(scanim, "colorAnim" + to_string(i) + "from", colorAnim[i].from);
		cfgHelp.put(scanim, "colorAnim" + to_string(i) + "to", colorAnim[i].to);

	cfg.writeFile(cfgFilePath.c_str());
	}
}

void Common::writePaletteToCFG()
{
	writePaletteToCFG("liero.cfg");
}

void Common::loadMaterials()
{
	FILE* exe = openLieroEXE();

	std::fseek(exe, 0x01C2E0, SEEK_SET);

	for(int i = 0; i < 256; ++i)
	{
		materials[i].flags = 0;
	}

	unsigned char bits[32];

	for(int i = 0; i < 5; ++i)
	{
		checkedFread(bits, 1, 32, exe);

		for(int j = 0; j < 256; ++j)
		{
			int bit = ((bits[j >> 3] >> (j & 7)) & 1);
			materials[j].flags |= bit << i;
		}
	}

	std::fseek(exe, 0x01AEA8, SEEK_SET);

	checkedFread(bits, 1, 32, exe);

	for(int j = 0; j < 256; ++j)
	{
		int bit = ((bits[j >> 3] >> (j & 7)) & 1);
		materials[j].flags |= bit << 5;
	}
}

void Common::loadMaterialsFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &smaterials = cfg.lookup("Materials");

	for(int i = 0; i < 256; ++i)
	{
		const libconfig::Setting &smflags = smaterials["flags" + to_string(i)];
		materials[i].flags = smflags;
	}
}

void Common::loadMaterialsFromCFG()
{
	loadMaterialsFromCFG("liero.cfg");
}

void Common::writeMaterialsToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &smaterials = cfgHelp.getSubgroup(root, "Materials");

	for(int i = 0; i < 256; ++i)
	{
		cfgHelp.put(smaterials, "flags" + to_string(i), materials[i].flags);
	}
	cfg.writeFile(cfgFilePath.c_str());
}

void Common::writeMaterialsToCFG()
{
	writeMaterialsToCFG("liero.cfg");
}

struct Read32
{
	static inline int run(FILE* f)
	{
		return readSint32(f);
	}
};

struct Read16
{
	static inline int run(FILE* f)
	{
		return readSint16(f);
	}
};

struct Read8
{
	static inline int run(FILE* f)
	{
		return readUint8(f);
	}
};

struct ReadBool
{
	static inline bool run(FILE* f)
	{
		return readUint8(f) != 0;
	}
};

template<typename T>
struct Dec
{
	static inline int run(FILE* f)
	{
		return T::run(f) - 1;
	}
};

template<typename Reader, typename T, int N, typename U>
inline void readMembers(FILE* f, T(&arr)[N], U (T::*mem))
{
	for(int i = 0; i < N; ++i)
	{
		(arr[i].*mem) = Reader::run(f);
	}
}

void Common::loadWeapons()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 112806, SEEK_SET);

	readMembers<Read8>(exe, weapons, &Weapon::detectDistance);
	readMembers<ReadBool>(exe, weapons, &Weapon::affectByWorm);
	readMembers<Read8>(exe, weapons, &Weapon::blowAway);

	for(int i = 0; i < 40; ++i)
	{
		weapOrder[i + 1] = readUint8(exe) - 1;
	}

	readMembers<Read16>(exe, weapons, &Weapon::gravity);
	readMembers<ReadBool>(exe, weapons, &Weapon::shadow);
	readMembers<ReadBool>(exe, weapons, &Weapon::laserSight);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::launchSound);
	readMembers<ReadBool>(exe, weapons, &Weapon::loopSound);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::exploSound);
	readMembers<Read16>(exe, weapons, &Weapon::speed);
	readMembers<Read16>(exe, weapons, &Weapon::addSpeed);
	readMembers<Read16>(exe, weapons, &Weapon::distribution);
	readMembers<Read8>(exe, weapons, &Weapon::parts);
	readMembers<Read8>(exe, weapons, &Weapon::recoil);
	readMembers<Read16>(exe, weapons, &Weapon::multSpeed);
	readMembers<Read16>(exe, weapons, &Weapon::delay);
	readMembers<Read16>(exe, weapons, &Weapon::loadingTime);
	readMembers<Read8>(exe, weapons, &Weapon::ammo);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::createOnExp);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::dirtEffect);
	readMembers<Read8>(exe, weapons, &Weapon::leaveShells);
	readMembers<Read8>(exe, weapons, &Weapon::leaveShellDelay);
	readMembers<ReadBool>(exe, weapons, &Weapon::playReloadSound);
	readMembers<ReadBool>(exe, weapons, &Weapon::wormExplode);
	readMembers<ReadBool>(exe, weapons, &Weapon::explGround);
	readMembers<ReadBool>(exe, weapons, &Weapon::wormCollide);
	readMembers<Read8>(exe, weapons, &Weapon::fireCone);
	readMembers<ReadBool>(exe, weapons, &Weapon::collideWithObjects);
	readMembers<ReadBool>(exe, weapons, &Weapon::affectByExplosions);
	readMembers<Read8>(exe, weapons, &Weapon::bounce);
	readMembers<Read16>(exe, weapons, &Weapon::timeToExplo);
	readMembers<Read16>(exe, weapons, &Weapon::timeToExploV);
	readMembers<Read8>(exe, weapons, &Weapon::hitDamage);
	readMembers<Read8>(exe, weapons, &Weapon::bloodOnHit);
	readMembers<Read16>(exe, weapons, &Weapon::startFrame);
	readMembers<Read8>(exe, weapons, &Weapon::numFrames);
	readMembers<ReadBool>(exe, weapons, &Weapon::loopAnim);
	readMembers<Read8>(exe, weapons, &Weapon::shotType);
	readMembers<Read8>(exe, weapons, &Weapon::colorBullets);
	readMembers<Read8>(exe, weapons, &Weapon::splinterAmount);
	readMembers<Read8>(exe, weapons, &Weapon::splinterColour);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::splinterType);
	readMembers<Read8>(exe, weapons, &Weapon::splinterScatter);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::objTrailType);
	readMembers<Read8>(exe, weapons, &Weapon::objTrailDelay);
	readMembers<Read8>(exe, weapons, &Weapon::partTrailType);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::partTrailObj);
	readMembers<Read8>(exe, weapons, &Weapon::partTrailDelay);

	fseek(exe, 0x1B676, SEEK_SET);
	for(int i = 0; i < 40; ++i)
	{
		weapons[i].name = readPascalString(exe, 14);
		weapons[i].id = i;
	}

	// Special objects
	fseek(exe, 115218, SEEK_SET);
	readMembers<Dec<Read8> >(exe, sobjectTypes, &SObjectType::startSound);
	//fseek(exe, 115232, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::numSounds);
	//fseek(exe, 115246, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::animDelay);
	//fseek(exe, 115260, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::startFrame);
	//fseek(exe, 115274, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::numFrames);
	//fseek(exe, 115288, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::detectRange);
	//fseek(exe, 115302, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::damage);
	//fseek(exe, 0x1C274, SEEK_SET);
	readMembers<Read32>(exe, sobjectTypes, &SObjectType::blowAway); // blowAway has 13 slots, not 14. The last value will overlap with shadow.
	fseek(exe, 115368, SEEK_SET);
	readMembers<ReadBool>(exe, sobjectTypes, &SObjectType::shadow);
	//fseek(exe, 115382, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::shake);
	//fseek(exe, 115396, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::flash);
	//fseek(exe, 115410, SEEK_SET); // Was 115409
	readMembers<Dec<Read8> >(exe, sobjectTypes, &SObjectType::dirtEffect);

	for(int i = 0; i < 14; ++i) // TODO: Unhardcode
	{
		sobjectTypes[i].id = i;
	}

	fseek(exe, 111430, SEEK_SET);

	readMembers<Read8>(exe, nobjectTypes, &NObjectType::detectDistance);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::gravity);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::speed);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::speedV);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::distribution);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::blowAway);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bounce);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::hitDamage);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::wormExplode);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::explGround);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::wormDestroy);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bloodOnHit);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::startFrame);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::numFrames);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::drawOnMap);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::colorBullets);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::createOnExp);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::affectByExplosions);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::dirtEffect);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::splinterAmount);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::splinterColour);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::splinterType);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::bloodTrail);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bloodTrailDelay);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::leaveObj);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::leaveObjDelay);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::timeToExplo);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::timeToExploV);

	for(int i = 0; i < 24; ++i) // TODO: Unhardcode
	{
		nobjectTypes[i].id = i;
	}
}

void Common::loadWeaponsFromCFG(std::string cfgFilePath)
{
	FILE* exe = openLieroEXE();

	fseek(exe, 112806, SEEK_SET);

	readMembers<Read8>(exe, weapons, &Weapon::detectDistance);
	readMembers<ReadBool>(exe, weapons, &Weapon::affectByWorm);
	readMembers<Read8>(exe, weapons, &Weapon::blowAway);

	for(int i = 0; i < 40; ++i)
	{
		weapOrder[i + 1] = readUint8(exe) - 1;
	}

	readMembers<Read16>(exe, weapons, &Weapon::gravity);
	readMembers<ReadBool>(exe, weapons, &Weapon::shadow);
	readMembers<ReadBool>(exe, weapons, &Weapon::laserSight);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::launchSound);
	readMembers<ReadBool>(exe, weapons, &Weapon::loopSound);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::exploSound);
	readMembers<Read16>(exe, weapons, &Weapon::speed);
	readMembers<Read16>(exe, weapons, &Weapon::addSpeed);
	readMembers<Read16>(exe, weapons, &Weapon::distribution);
	readMembers<Read8>(exe, weapons, &Weapon::parts);
	readMembers<Read8>(exe, weapons, &Weapon::recoil);
	readMembers<Read16>(exe, weapons, &Weapon::multSpeed);
	readMembers<Read16>(exe, weapons, &Weapon::delay);
	readMembers<Read16>(exe, weapons, &Weapon::loadingTime);
	readMembers<Read8>(exe, weapons, &Weapon::ammo);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::createOnExp);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::dirtEffect);
	readMembers<Read8>(exe, weapons, &Weapon::leaveShells);
	readMembers<Read8>(exe, weapons, &Weapon::leaveShellDelay);
	readMembers<ReadBool>(exe, weapons, &Weapon::playReloadSound);
	readMembers<ReadBool>(exe, weapons, &Weapon::wormExplode);
	readMembers<ReadBool>(exe, weapons, &Weapon::explGround);
	readMembers<ReadBool>(exe, weapons, &Weapon::wormCollide);
	readMembers<Read8>(exe, weapons, &Weapon::fireCone);
	readMembers<ReadBool>(exe, weapons, &Weapon::collideWithObjects);
	readMembers<ReadBool>(exe, weapons, &Weapon::affectByExplosions);
	readMembers<Read8>(exe, weapons, &Weapon::bounce);
	readMembers<Read16>(exe, weapons, &Weapon::timeToExplo);
	readMembers<Read16>(exe, weapons, &Weapon::timeToExploV);
	readMembers<Read8>(exe, weapons, &Weapon::hitDamage);
	readMembers<Read8>(exe, weapons, &Weapon::bloodOnHit);
	readMembers<Read16>(exe, weapons, &Weapon::startFrame);
	readMembers<Read8>(exe, weapons, &Weapon::numFrames);
	readMembers<ReadBool>(exe, weapons, &Weapon::loopAnim);
	readMembers<Read8>(exe, weapons, &Weapon::shotType);
	readMembers<Read8>(exe, weapons, &Weapon::colorBullets);
	readMembers<Read8>(exe, weapons, &Weapon::splinterAmount);
	readMembers<Read8>(exe, weapons, &Weapon::splinterColour);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::splinterType);
	readMembers<Read8>(exe, weapons, &Weapon::splinterScatter);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::objTrailType);
	readMembers<Read8>(exe, weapons, &Weapon::objTrailDelay);
	readMembers<Read8>(exe, weapons, &Weapon::partTrailType);
	readMembers<Dec<Read8> >(exe, weapons, &Weapon::partTrailObj);
	readMembers<Read8>(exe, weapons, &Weapon::partTrailDelay);

	fseek(exe, 0x1B676, SEEK_SET);
	for(int i = 0; i < 40; ++i)
	{
		weapons[i].name = readPascalString(exe, 14);
		weapons[i].id = i;
	}

	// Special objects
	fseek(exe, 115218, SEEK_SET);
	readMembers<Dec<Read8> >(exe, sobjectTypes, &SObjectType::startSound);
	//fseek(exe, 115232, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::numSounds);
	//fseek(exe, 115246, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::animDelay);
	//fseek(exe, 115260, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::startFrame);
	//fseek(exe, 115274, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::numFrames);
	//fseek(exe, 115288, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::detectRange);
	//fseek(exe, 115302, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::damage);
	//fseek(exe, 0x1C274, SEEK_SET);
	readMembers<Read32>(exe, sobjectTypes, &SObjectType::blowAway); // blowAway has 13 slots, not 14. The last value will overlap with shadow.
	fseek(exe, 115368, SEEK_SET);
	readMembers<ReadBool>(exe, sobjectTypes, &SObjectType::shadow);
	//fseek(exe, 115382, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::shake);
	//fseek(exe, 115396, SEEK_SET);
	readMembers<Read8>(exe, sobjectTypes, &SObjectType::flash);
	//fseek(exe, 115410, SEEK_SET); // Was 115409
	readMembers<Dec<Read8> >(exe, sobjectTypes, &SObjectType::dirtEffect);

	for(int i = 0; i < 14; ++i) // TODO: Unhardcode
	{
		sobjectTypes[i].id = i;
	}

	fseek(exe, 111430, SEEK_SET);

	readMembers<Read8>(exe, nobjectTypes, &NObjectType::detectDistance);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::gravity);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::speed);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::speedV);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::distribution);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::blowAway);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bounce);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::hitDamage);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::wormExplode);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::explGround);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::wormDestroy);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bloodOnHit);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::startFrame);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::numFrames);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::drawOnMap);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::colorBullets);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::createOnExp);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::affectByExplosions);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::dirtEffect);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::splinterAmount);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::splinterColour);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::splinterType);
	readMembers<ReadBool>(exe, nobjectTypes, &NObjectType::bloodTrail);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::bloodTrailDelay);
	readMembers<Dec<Read8> >(exe, nobjectTypes, &NObjectType::leaveObj);
	readMembers<Read8>(exe, nobjectTypes, &NObjectType::leaveObjDelay);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::timeToExplo);
	readMembers<Read16>(exe, nobjectTypes, &NObjectType::timeToExploV);

	for(int i = 0; i < 24; ++i) // TODO: Unhardcode
	{
		nobjectTypes[i].id = i;
	}
}

void Common::loadTextures()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C208, SEEK_SET);
	readMembers<ReadBool>(exe, textures, &Texture::nDrawBack);
	fseek(exe, 0x1C1EA, SEEK_SET);
	readMembers<Read8>(exe, textures, &Texture::mFrame);
	fseek(exe, 0x1C1F4, SEEK_SET);
	readMembers<Read8>(exe, textures, &Texture::sFrame);
	fseek(exe, 0x1C1FE, SEEK_SET);
	readMembers<Read8>(exe, textures, &Texture::rFrame);
}

void Common::loadOthers()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C1E2, SEEK_SET);

	for(int i = 0; i < 2; ++i)
	for(int j = 0; j < 2; ++j)
		bonusRandTimer[j][i] = readUint16(exe);

	fseek(exe, 0x1AEEE + 2, SEEK_SET);

	for(int i = 0; i < 2; ++i)
	for(int j = 0; j < 7; ++j)
		aiParams.k[i][j] = readUint16(exe);

	fseek(exe, 0x1C1E0, SEEK_SET);

	for(int i = 0; i < 2; ++i)
		bonusSObjects[i] = readUint8(exe) - 1;
}

void Common::loadGfxFromEXE()
{
	FILE* exe = openLieroEXE();

	fseek(exe, 0x1C1DE, SEEK_SET);
	bonusFrames[0] = readUint8(exe);
	bonusFrames[1] = readUint8(exe);
}

void Common::loadGfxFromCHR()
{
	FILE* gfx = openLieroCHR();

	fseek(gfx, 10, SEEK_SET); // Skip some header

	largeSprites.read(gfx, 16, 16, 110);
	fseek(gfx, 4, SEEK_CUR); // Extra stuff

	smallSprites.read(gfx, 7, 7, 130);
	fseek(gfx, 4, SEEK_CUR); // Extra stuff

	textSprites.read(gfx, 4, 4, 26);
}

void Common::loadGfxExtra()
{
	Rand rand;

	for(int y = 0; y < 16; ++y)
	for(int x = 0; x < 16; ++x)
	{
		int idx = y * 16 + x;
		largeSprites.spritePtr(73)[idx] = rand(4) + 160;
		largeSprites.spritePtr(74)[idx] = rand(4) + 160;

		largeSprites.spritePtr(87)[idx] = rand(4) + 12;
		largeSprites.spritePtr(88)[idx] = rand(4) + 12;

		largeSprites.spritePtr(82)[idx] = rand(4) + 94;
		largeSprites.spritePtr(83)[idx] = rand(4) + 94;
	}

	wormSprites.allocate(16, 16, 2 * 2 * 21);

	for(int i = 0; i < 21; ++i)
	{
		for(int y = 0; y < 16; ++y)
		for(int x = 0; x < 16; ++x)
		{
			PalIdx pix = (largeSprites.spritePtr(16 + i) + y*16)[x];

			(wormSprite(i, 1, 0) + y*16)[x] = pix;
			if(x == 15)
				(wormSprite(i, 0, 0) + y*16)[15] = 0;
			else
				(wormSprite(i, 0, 0) + y*16)[14 - x] = pix;

			if(pix >= 30 && pix <= 34)
				pix += 9; // Change worm color

			(wormSprite(i, 1, 1) + y*16)[x] = pix;

			if(x == 15)
				(wormSprite(i, 0, 1) + y*16)[15] = 0; // A bit haxy, but works
			else
				(wormSprite(i, 0, 1) + y*16)[14 - x] = pix;
		}
	}

	fireConeSprites.allocate(16, 16, 2 * 7);

	for(int i = 0; i < 7; ++i)
	{
		for(int y = 0; y < 16; ++y)
		for(int x = 0; x < 16; ++x)
		{
			PalIdx pix = (largeSprites.spritePtr(9 + i) + y*16)[x];

			(fireConeSprite(i, 1) + y*16)[x] = pix;

			if(x == 15)
				(fireConeSprite(i, 0) + y*16)[15] = 0;
			else
				(fireConeSprite(i, 0) + y*16)[14 - x] = pix;

		}
	}
}

void Common::loadGfx()
{
	loadGfxFromEXE();
	loadGfxFromCHR();
	loadGfxExtra();
}

void Common::loadGfxFromCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	cfg.readFile(cfgFilePath.c_str());
	const libconfig::Setting &sgfx = cfg.lookup("Gfx");

	bonusFrames[0] = static_cast<int>(sgfx["bonusFrames"][0]);
	bonusFrames[1] = static_cast<int>(sgfx["bonusFrames"][1]);

	loadGfxFromCHR();
	loadGfxExtra();
}

void Common::loadGfxFromCFG()
{
	loadGfxFromCFG("liero.cfg");
}

void Common::writeGfxToCFG(std::string cfgFilePath)
{
	libconfig::Config cfg;
	ConfigHelper cfgHelp;
	cfg.readFile(cfgFilePath.c_str());
	libconfig::Setting &root = cfg.getRoot();
	libconfig::Setting &sgfx = cfgHelp.getSubgroup(root, "Gfx");

	libconfig::Setting &sgbframes = cfgHelp.mkArray(sgfx, "bonusFrames");
	sgbframes.add(libconfig::Setting::TypeInt) = bonusFrames[0];
	sgbframes.add(libconfig::Setting::TypeInt) = bonusFrames[1];

	cfg.writeFile(cfgFilePath.c_str());
}

void Common::writeGfxToCFG()
{
	writeGfxToCFG("liero.cfg");
}

void Common::drawTextSmall(char const* str, int x, int y)
{
	for(; *str; ++str)
	{
		unsigned char c = *str - 'A';

		if(c < 26)
		{
			blitImage(gfx.screen, textSprites.spritePtr(c), x, y, 4, 4);
		}

		x += 4;
	}
}

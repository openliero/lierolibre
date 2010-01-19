#include "settings.hpp"

#include "reader.hpp"
#include "keys.hpp"
#include "gfx.hpp"
#include "filesystem.hpp"

#include <gvl/io/fstream.hpp>
#include <gvl/serialization/context.hpp>
#include <gvl/serialization/archive.hpp>

#include <gvl/crypt/gash.hpp>

int const Settings::wormAnimTab[] =
{
	0,
	7,
	0,
	14
};

Extensions::Extensions()
: extensions(false)
, recordReplays(true)
, loadPowerlevelPalette(true)
, scaleFilter(Settings::SfNearest)
, depth32(true)
, bloodParticleMax(700)
, fullscreenW(640)
, fullscreenH(480)
{
}

Settings::Settings()
: maxBonuses(4)
, blood(100)
, timeToLose(600)
, flagsToWin(20)
, gameMode(0)
, shadow(true)
, loadChange(false)
, namesOnBonuses(false)
, regenerateLevel(false)
, lives(15)
, loadingTime(100)
, randomLevel(true)
, map(true)
, screenSync(true)

{
	std::memset(weapTable, 0, sizeof(weapTable));
	
	wormSettings[0].reset(new WormSettings);
	wormSettings[1].reset(new WormSettings);
	
	wormSettings[0]->color = 32;
	wormSettings[1]->color = 41;
	
	//wormSettings[0]->selWeapX = 50;
	//wormSettings[1]->selWeapX = 210;
	
	unsigned char defControls[2][7] =
	{
		{0x13, 0x21, 0x20, 0x22, 0x1D, 0x2A, 0x38},
		{0xA0, 0xA8, 0xA3, 0xA5, 0x75, 0x90, 0x36}
	};
	
	unsigned char defRGB[2][3] =
	{
		{26, 26, 63},
		{15, 43, 15}
	};
	
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			wormSettings[i]->controls[j] = defControls[i][j];
		}
		
		for(int j = 0; j < 3; ++j)
		{
			wormSettings[i]->rgb[j] = defRGB[i][j];
		}
	}
}

bool Settings::load(std::string const& path)
{
	FILE* opt = tolerantFOpen(path.c_str(), "rb");
	
	if(!opt)
		return false;
		
	std::size_t size = fileLength(opt);
	
	if(size < 155)
		return false; // .dat is too short
	
	gvl::stream_reader reader(gvl::stream_ptr(new gvl::fstream(opt)));
	gvl::default_serialization_context context;
	
	archive_liero(gvl::in_archive<gvl::default_serialization_context>(reader, context), *this);
	
#if 0
	maxBonuses = readUint8(opt);
	loadingTime = readUint16(opt);
	lives = readUint16(opt);
	timeToLose = readUint16(opt);
	flagsToWin = readUint16(opt);
	
	screenSync = readUint8(opt) != 0;
	map = readUint8(opt) != 0;
	wormSettings[0]->controller = readUint8(opt) & 0x1;
	wormSettings[1]->controller = readUint8(opt) & 0x1;
	randomLevel = readUint8(opt) != 0;
	blood = readUint16(opt);
	gameMode = readUint8(opt);
	namesOnBonuses = readUint8(opt) != 0;
	regenerateLevel = readUint8(opt) != 0;
	shadow = readUint8(opt) != 0;
	
	//fread(weapTable, 1, 40, opt);
	
	for(int i = 0; i < 40; ++i)
	{
		weapTable[i] = limit<0, 3>(fgetc(opt));
	}
	
	for(int i = 0; i < 2; ++i)
	for(int j = 0; j < 3; ++j)
		wormSettings[i]->rgb[j] = readUint8(opt) & 63;
		
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			wormSettings[i]->weapons[j] = readUint8(opt);
		}
	}

	wormSettings[0]->health = readUint16(opt);
	wormSettings[1]->health = readUint16(opt);

	for(int i = 0; i < 2; ++i)
	{
		wormSettings[i]->name = readPascalString(opt, 21);
	}
	
	//fgetc(opt); // What's this?
	
	loadChange = readUint8(opt) != 0;
	
	// 0x7B-83 is the string LIERO
	
	fseek(opt, 0x84, SEEK_SET);
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			wormSettings[i]->controls[j] = limit<0, 177>(readUint8(opt));
		}
	}
	
	levelFile = readPascalString(opt, 9);
	
	for(int i = 0; i < 2; ++i)
	{
		if(wormSettings[i]->name.empty())
			generateName(*wormSettings[i]);
		else
			wormSettings[i]->randomName = false;
	}
	
	fclose(opt);
#endif
	
	return true;
}

gvl::gash::value_type& Settings::updateHash()
{
	gvl::default_serialization_context context;
	gvl::hash_accumulator<gvl::gash> ha;
	
	archive(gvl::out_archive<gvl::default_serialization_context, gvl::hash_accumulator<gvl::gash> >(ha, context), *this);
	
	ha.flush();
	hash = ha.final();
	return hash;
}

void Settings::save(std::string const& path)
{
	{
		FILE* opt = fopen(path.c_str(), "wb");
		gvl::stream_writer writer(gvl::stream_ptr(new gvl::fstream(opt)));
	
		gvl::default_serialization_context context;
		
		archive_liero(gvl::out_archive<gvl::default_serialization_context>(writer, context), *this);
	}
	
#if 0
	writeUint8(opt, maxBonuses);
	writeUint16(opt, loadingTime);
	writeUint16(opt, lives);
	writeUint16(opt, timeToLose);
	writeUint16(opt, flagsToWin);
	
	writeUint8(opt, screenSync);
	writeUint8(opt, map);
	writeUint8(opt, wormSettings[0]->controller);
	writeUint8(opt, wormSettings[1]->controller);
	writeUint8(opt, randomLevel);
	writeUint16(opt, blood);
	writeUint8(opt, gameMode);
	writeUint8(opt, namesOnBonuses);
	writeUint8(opt, regenerateLevel);
	writeUint8(opt, shadow);
	
	fwrite(weapTable, 1, 40, opt);
	
	for(int i = 0; i < 2; ++i)
	for(int j = 0; j < 3; ++j)
		writeUint8(opt, wormSettings[i]->rgb[j]);
		
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			writeUint8(opt, wormSettings[i]->weapons[j]);
		}
	}

	writeUint16(opt, wormSettings[0]->health);
	writeUint16(opt, wormSettings[1]->health);

	for(int i = 0; i < 2; ++i)
	{
		if(wormSettings[i]->randomName)
			writePascalString(opt, "", 21);
		else
			writePascalString(opt, wormSettings[i]->name, 21);
	}
	
	//fputc(0, opt); // What's this?
	
	writeUint8(opt, loadChange);
	
	char const lieroStr[] = "\x05LIERO\0\0";
	
	fwrite(lieroStr, 1, sizeof(lieroStr), opt);
	
	//fseek(opt, 0x84, SEEK_SET);
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 7; ++j)
		{
			writeUint8(opt, wormSettings[i]->controls[j]);
		}
	}
	
	writePascalString(opt, levelFile, 9);
	
	fclose(opt);
#endif
}

void Settings::generateName(WormSettings& ws)
{
	FILE* f = fopen(joinPath(lieroEXERoot, "NAMES.DAT").c_str(), "rb");
	
	if(!f)
		return;
		
	std::vector<std::string> names;
	
	std::size_t len = fileLength(f);
	
	std::vector<char> chars(len);
	
	checkedFread(&chars[0], 1, len, f);
	
	fclose(f);
	
	std::size_t begin = 0;
	for(std::size_t i = 0; i < len; ++i)
	{
		if(chars[i] == '\r'
		|| chars[i] == '\n')
		{
			if(i > begin)
			{
				names.push_back(std::string(chars.begin() + begin, chars.begin() + i));
			}
			
			begin = i + 1;
		}
	}
	
	if(!names.empty())
	{
		ws.name = names[gfx.rand(Uint32(names.size()))];
		ws.randomName = true;
	}
}

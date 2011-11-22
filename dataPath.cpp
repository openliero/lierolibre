// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
#include <iostream>
#include <fstream>
//#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>

DataPath::DataPath(string a_readonly_path)
{
	readonly_path = a_readonly_path;
	delimitor = '/';
	configdotdir = string(getenv("HOME")) + delimitor + ".liero";

	// Map of files we may want to return path to
	// should be read from plaintext file
	// true means writable, false read-only
	file_access_map.insert(pair<string, bool>("LIERO.EXE", false));
	file_access_map.insert(pair<string, bool>("LIERO.CHR", false));
	file_access_map.insert(pair<string, bool>("LIERO.SND", false));
	file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
	file_access_map.insert(pair<string, bool>("LIERO.DAT", true));
}

string DataPath::file(string filename)
{
	fstream file_writable;
	ifstream file_readonly;

	string filepath_readonly = readonly_path + delimitor + filename;
	string filepath_writable = configdotdir + delimitor + filename;
	bool file_shouldbe_writable = file_access_map.find(filename)->second;

	if(file_shouldbe_writable) {
		file_writable.open(filepath_writable.c_str(), ios::in);
		if(file_writable.is_open()) {
			// File exists in configdir
			return filepath_writable;
		} else {
			// file does not exist in configdir
			file_readonly.open(filepath_readonly.c_str());
			if(file_readonly.is_open()) {
				// file exists in readonly
				mkdir(configdotdir.c_str(), 0777);
				file_writable.open(
					filepath_writable.c_str(), ios::out);
				file_writable << file_readonly.rdbuf();
				return filepath_writable;
			} else {
				// file does not exist anywhere
				// throw meep
			}
		}
	} else {
		// file should not be writable
		file_readonly.open(filepath_readonly.c_str());
		if(file_readonly.is_open()) {
			// file exists in readonly
			return filepath_readonly;
		} else {
			// file does not exist anywhere
			// throw meep
		}
	}
}

string DataPath::configdir(void)
{
	mkdir(configdotdir.c_str(), 0777);
	return configdotdir;
}

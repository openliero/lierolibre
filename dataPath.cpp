// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
//#include <iostream>
#include <fstream>
//#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>

string DataPath::create_configdir(string directory)
{
	if (mkdir(directory.c_str(), 0777) == 0) {
		return directory;
	} else if (errno == EEXIST) {
		return directory;
	} else {
		return "ECONFIGDIR";
	}
}



DataPath::DataPath(string a_readonly_path)
{
	readonly_path = a_readonly_path;
	configdotdir = string(getenv("HOME")) + '/' + ".liero";

	// Map of files we may want to return path to
	// should probably be read from plaintext file
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

	string filepath_readonly = readonly_path + '/' + filename;
	string filepath_writable = configdotdir + '/' + filename;
	bool file_shouldbe_writable = file_access_map.find(filename)->second;

	if (file_shouldbe_writable) {
		file_writable.open(filepath_writable.c_str(), ios::binary | ios::in);
		if (file_writable.is_open()) {
			// File exists in configdir
			return filepath_writable;
		} else {
			// file does not exist in configdir
			file_readonly.open(filepath_readonly.c_str(), ios::binary);
			if (file_readonly.is_open()) {
				// file exists in readonly
				if (DataPath::create_configdir(configdotdir)
								== "ECONFIGDIR") {
					return "ECONFIGDIR";
				}
				// error handling
				file_writable.open(
					filepath_writable.c_str(),
								ios::binary | ios::out);
				if (file_writable.is_open()) {
					file_writable << file_readonly.rdbuf();
					// error handling
					return filepath_writable;
				} else {
				// couldn't open writable file
				// throw meep
				return "ENOTOPEN";
				}
			} else {
				// file does not exist anywhere
				// throw meep
				return "ENOFILE";
			}
		}
	} else {
		// file should not be writable
		file_readonly.open(filepath_readonly.c_str());
		if (file_readonly.is_open()) {
			// file exists in readonly
			return filepath_readonly;
		} else {
			// file does not exist anywhere
			// throw meep
			return "ENOFILE";
		}
	}
}

string DataPath::configdir(void)
{
	return DataPath::create_configdir(configdotdir);
/*
	if (mkdir(configdotdir.c_str(), 0777) == 0) {
		return configdotdir;
	} else if (errno == EEXIST) {
		return configdotdir;
	} else {
		return "ECONFIGDIR";
	}
*/
}

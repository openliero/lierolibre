// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include <cerrno>
using namespace std;

string create_configdir(string directory)
{
	if (mkdir(directory.c_str(), 0777) == 0) {
		return directory;
	} else if (errno == EEXIST) {
		return directory;
	} else {
		throw runtime_error("Unable to create configdir '"
						 + directory + "'");
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
	file_access_map.insert(pair<string, bool>("NAMES.DAT", false));
	file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
	file_access_map.insert(pair<string, bool>("LIERO.DAT", true));
	file_access_map.insert(pair<string, bool>("config.ini", true));
}

string DataPath::file(string filename)
{
	fstream file_writable;
	ifstream file_readonly;

	string filepath_readonly = readonly_path + '/' + filename;
	string filepath_writable = configdotdir + '/' + filename;
	if (file_access_map.count(filename) == 0) {
		if (filename.substr(filename.find_last_of(".") + 1)
								== "DAT") {
			// file ends with .DAT
			return filepath_writable;
		} else {
			throw runtime_error("Unknown file '" + filename + "'");
		}
	}
	bool file_shouldbe_writable = file_access_map.find(filename)->second;

	if (file_shouldbe_writable) {
		file_writable.open(filepath_writable.c_str(),
						ios::binary | ios::in);
		if (file_writable.is_open()) {
			// File exists in configdir
			return filepath_writable;
		} else {
			// file does not exist in configdir
			file_readonly.open(filepath_readonly.c_str(),
								ios::binary);
			if (file_readonly.is_open()) {
				// file exists in readonly
				create_configdir(configdotdir);
				file_writable.open( filepath_writable.c_str(),
						ios::binary | ios::out);
				if (file_writable.is_open()) {
					file_writable
						<< file_readonly.rdbuf();
					// error handling
					return filepath_writable;
				} else {
				// couldn't open writable file
				throw runtime_error("Could not open file '"
							+ filepath_writable
							+ "' for writing");
				}
			} else {
				// file does not exist anywhere
				throw runtime_error("Could not open file '"
					+ filepath_writable + "'");
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
			throw runtime_error("Could not open file '"
					+ filepath_readonly + "'");
		}
	}
}

string DataPath::configdir(void)
{
	return create_configdir(configdotdir);
}

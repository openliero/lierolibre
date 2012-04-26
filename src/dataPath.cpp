/*
 * Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
 * This software is released under the The BSD-2-Clause License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include <cerrno>
#include "filesystem.hpp"
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
	if (isDir(a_readonly_path))
		readonly_path = a_readonly_path; // Don't getRoot on a dir
	else
		readonly_path = getRoot(a_readonly_path);

	configdotdir = string(getenv("HOME")) + '/' + ".lierolibre";

	// Map of files we may want to return path to
	// should probably be read from plaintext file
	// true means writable, false read-only
	file_access_map.insert(pair<string, bool>("LIERO.EXE", false));
	file_access_map.insert(pair<string, bool>("LIERO.CHR", false));
	file_access_map.insert(pair<string, bool>("LIERO.SND", false));
	file_access_map.insert(pair<string, bool>("NAMES.DAT", false));
	file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
	file_access_map.insert(pair<string, bool>("LIERO.DAT", true));
	file_access_map.insert(pair<string, bool>("liero.cfg", true));
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

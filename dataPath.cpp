// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

DataPath::DataPath(string a_readonly_path) {
	readonly_path = a_readonly_path;
	delimitor = '/';
}

string DataPath::file(string a_filename) {
	string filename = a_filename;
	string filename_path;

	// lookup status (r/w) of filename
	// if status is ro {
		filename_path.append(readonly_path);
		filename_path.append(1, delimitor);
		filename_path.append(filename);
		return filename_path;
	// }
}

string DataPath::configdir(void) {
	const string home = "HOME";
	const string homedir = getenv(home.c_str());
	const string lierodir = ".liero";
	string configdir;
	configdir.append(homedir);
	configdir.append(1, delimitor);
	configdir.append(lierodir);
//	printf("delim: %s", delimitor.c_str());
//	printf("configir = %s\n", configdir.c_str());
	mkdir(configdir.c_str(), 0777);
	return configdir;
}

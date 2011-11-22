// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

DataPath::DataPath(string a_lieroexe) {
	lieroexe = a_lieroexe;
}

string DataPath::file(string filename) {
	return "";
}

string DataPath::configdir(void) {
	const string home = "HOME";
	const string homedir = getenv(home.c_str());
	const string dotdir = "/.liero";
	string configdir;
	configdir.append(homedir);
	configdir.append(dotdir);
	mkdir(configdir.c_str(), 0777);
	return configdir;
}

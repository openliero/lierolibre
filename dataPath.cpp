// Compile via ~$ g++ -c dataPath.cpp
#include "dataPath.hpp"

DataPath::DataPath(string a_lieroexe) {
	lieroexe = a_lieroexe;
}

string DataPath::file(string filename) {
	return "";
}

string DataPath::configdir(void) {
	return "/tmp";
}

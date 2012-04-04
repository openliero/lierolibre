// Compile via:
// g++ -c to_string.o config.cpp

#include <fstream>
#include <iostream>
#include <stdexcept>

// INI config file
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "config.hpp"

// int->string conversion, this is available in c++11
//#include "to_string.hpp"

// getRoot
//#include "filesystem.hpp"

#include "dataPath.hpp"

using namespace std;
namespace bpt = boost::property_tree;

Config::Config(string a_configfile)
{
	configFile.open(a_configfile.c_str());
	if (!configFile.is_open())
		throw runtime_error("unable to open " + a_configfile);

	read_ini(configFile, configPtree);
}

void Config::writeOut()
{
	write_ini(configFile, configPtree);
}

void Config::writeOut(std::string a_configfile)
{
	ofstream configFileOut;
	configFileOut.open(a_configfile.c_str(), ios::out);
	if (!configFileOut.is_open())
		throw runtime_error("unable to open " + a_configfile);

	write_ini(configFileOut, configPtree);
}

string Config::getString(string variable)
{
	return configPtree.get<std::string>(variable);
}

string Config::getString(string variable, string defaultValue)
{
	return configPtree.get(variable, defaultValue);
}

int Config::getInt(string variable)
{
	return configPtree.get<int>(variable);
}

int Config::getInt(string variable, int defaultValue)
{
	return configPtree.get(variable, defaultValue);
}

void Config::put(string variable, string value)
{
	configPtree.put(variable, value);
}

void Config::put(string variable, int value)
{
	configPtree.put(variable, value);
}


// Compile via:
// g++ -c config.cpp

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

//#include "dataPath.hpp"

using namespace std;
namespace bpt = boost::property_tree;

Config::Config(string a_configFile)
{
	configFilePath = a_configFile;
}

void Config::read()
{
	ifstream configFile(configFilePath.c_str());
	if (configFile.is_open()) {
		read_ini(configFile, configPtree);
	} else {
		configFile.close();
		throw runtime_error("unable to open " + configFilePath + " for reading");
	}
}

void Config::write(std::string a_configFilePath)
{
	ofstream configFile(a_configFilePath.c_str(), ios::out);
	if (configFile.is_open()) {
		write_ini(configFile, configPtree);
	} else {
		configFile.close();
		throw runtime_error("unable to open " + a_configFilePath + " for writing");
	}
}

void Config::write(void)
{
	write(configFilePath);
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


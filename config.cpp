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
#include "filesystem.hpp"

#include "dataPath.hpp"

using namespace std;
namespace bpt = boost::property_tree;

Config::Config(string a_configfile)
{
	configfile.open(a_configfile.c_str());
	if (!configfile.is_open())
		throw runtime_error("unable to open " + a_configfile);

	read_ini(configfile, config_ptree);
}

string Config::getstring(string variable)
{
	return config_ptree.get<std::string>(variable);
}

int Config::getint(string variable)
{
	return config_ptree.get<int>(variable);
}

void Config::put(string variable, string value)
{
	config_ptree.put(variable, value);
}

void Config::put(string variable, int value)
{
	config_ptree.put(variable, value);
}


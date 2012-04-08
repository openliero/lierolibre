#include "configHelper.hpp"
#include <libconfig.h++>
#include <limits>
#include <SDL/SDL.h>
#include <stdexcept>

using namespace std;
using namespace libconfig;

void ConfigHelper::lookupValue(const libconfig::Setting &node, std::string variable, Uint8 &destVariable)
{
	int value;
	node.lookupValue(variable, value);
	if(value <= numeric_limits<Uint8>::max() && value >= numeric_limits<Uint8>::min())
	{
		destVariable = static_cast<Uint8>(value);
	} else {
		throw overflow_error("Config value '" + variable + "' is too big");
	}
}

void ConfigHelper::lookupValue(libconfig::Setting &node, std::string variable, Uint8 &destVariable)
{
	int value;
	node.lookupValue(variable, value);
	if(value <= numeric_limits<Uint8>::max() && value >= numeric_limits<Uint8>::min())
	{
		destVariable = static_cast<Uint8>(value);
	} else {
		throw overflow_error("Config value '" + variable + "' is too big");
	}
}

void ConfigHelper::put(Setting &node, string variable, string value)
{
	if(!node.exists(variable))
	{
		node.add(variable, Setting::TypeString) = value;
	} else {
		Setting &var = node[variable];
		var = value;
	}
}

void ConfigHelper::put(Setting &node, string variable, int value)
{
	if(!node.exists(variable))
	{
		node.add(variable, Setting::TypeInt) = value;
	} else {
		Setting &var = node[variable];
		var = value;
	}
}

void ConfigHelper::put(Setting &node, string variable, Uint8 value)
{
	if(!node.exists(variable))
	{
		node.add(variable, Setting::TypeInt) = value;
	} else {
		Setting &var = node[variable];
		var = value;
	}
}

Setting& ConfigHelper::getSubgroup(Setting &node, string groupName)
{
	if(!node.exists(groupName))
	{
		node.add(groupName, Setting::TypeGroup);
	}
	return node[groupName];
}


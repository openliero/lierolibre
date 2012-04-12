#include "configHelper.hpp"
#include <libconfig.h++>
#include <limits>
#include <SDL/SDL.h>
#include <stdexcept>

using namespace std;
using namespace libconfig;

template<typename N, typename I, typename D>
void ConfigHelper::getValue(N &node, I index, D &destVariable)
{
	int value = node[index];
	if(value <= numeric_limits<D>::max() && value >= numeric_limits<D>::min())
	{
		destVariable = static_cast<D>(value);
	} else {
		throw overflow_error("Config value is too big");
	}
}

template void ConfigHelper::getValue<const libconfig::Setting, int, Uint8>(const libconfig::Setting &node, int index, Uint8 &destVariable);

template void ConfigHelper::getValue<const libconfig::Setting, char const*, Uint8>(const libconfig::Setting &node, char const* variable, Uint8 &destVariable);

template void ConfigHelper::getValue<const libconfig::Setting, std::string, Uint8>(const libconfig::Setting &node, std::string variable, Uint8 &destVariable);


template void ConfigHelper::getValue<libconfig::Setting, int, Uint8>(libconfig::Setting &node, int index, Uint8 &destVariable);

template void ConfigHelper::getValue<libconfig::Setting, char const*, Uint8>(libconfig::Setting &node, char const* variable, Uint8 &destVariable);

template void ConfigHelper::getValue<libconfig::Setting, std::string, Uint8>(libconfig::Setting &node, std::string variable, Uint8 &destVariable);

/* nice templates, but they expose too many arguments
template<typename V>
void ConfigHelper::put(Setting &node, string variable, Setting::Type type, V value)
{
	if(!node.exists(variable))
	{
		node.add(variable, type) = value;
	} else {
		node[variable] = value;
	}
}

template void ConfigHelper::put<bool>(Setting &node, string variable, Setting::Type type, bool value);

template void ConfigHelper::put<Uint8>(Setting &node, string variable, Setting::Type type, Uint8 value);

template void ConfigHelper::put<int>(Setting &node, string variable, Setting::Type type, int value);

template void ConfigHelper::put<string>(Setting &node, string variable, Setting::Type type, string value);
*/

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

void ConfigHelper::put(Setting &node, string variable, bool value)
{
	if(!node.exists(variable))
	{
		node.add(variable, Setting::TypeBoolean) = value;
	} else {
		Setting &var = node[variable];
		var = value;
	}
}

Setting& ConfigHelper::mkArray(Setting &node, string arrayName)
{
	if(node.exists(arrayName))
	{
		node.remove(arrayName);
	}
	return node.add(arrayName, Setting::TypeArray);
}

Setting& ConfigHelper::getSubgroup(Setting &node, string groupName)
{
	if(!node.exists(groupName))
	{
		node.add(groupName, Setting::TypeGroup);
	}
	return node[groupName];
}


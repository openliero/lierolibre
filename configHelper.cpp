#include "configHelper.hpp"
#include <libconfig.h++>
#include <limits>
#include <SDL/SDL.h>
#include <stdexcept>

using namespace std;
using namespace libconfig;

// This templateification is somewhat unnecessay, could just use getUint8()
template<typename Dest, typename Node, typename Idx>
Dest ConfigHelper::getValue(Node &node, Idx index)
{
	int value = node[index];
	if(value <= numeric_limits<Dest>::max() && value >= numeric_limits<Dest>::min())
	{
		return static_cast<Dest>(value);
	} else {
		throw overflow_error("Config value is too big");
	}
}

template Uint8 ConfigHelper::getValue<Uint8, const Setting, int>(const Setting &node, int index);

template Uint8 ConfigHelper::getValue<Uint8, const Setting, char const*>(const Setting &node, char const* index);

template Uint8 ConfigHelper::getValue<Uint8, const Setting, string>(const Setting &node, string index);

// Non-const
template Uint8 ConfigHelper::getValue<Uint8, Setting, int>(Setting &node, int index);

template Uint8 ConfigHelper::getValue<Uint8, Setting, char const*>(Setting &node, char const* index);

template Uint8 ConfigHelper::getValue<Uint8, Setting, string>(Setting &node, string index);


// Since we still need specialisation per value type (Setting::Type),
// no need to templateify these
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

Setting& ConfigHelper::mkList(Setting &node, string listName)
{
	if(node.exists(listName))
	{
		node.remove(listName);
	}
	return node.add(listName, Setting::TypeList);
}

Setting& ConfigHelper::getSubgroup(Setting &node, string groupName)
{
	if(!node.exists(groupName))
	{
		node.add(groupName, Setting::TypeGroup);
	}
	return node[groupName];
}


#include "configHelper.hpp"
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

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

Setting& ConfigHelper::getSubgroup(Setting &node, string groupName)
{
	if(!node.exists(groupName))
	{
		node.add(groupName, Setting::TypeGroup);
	}
	return node[groupName];
}


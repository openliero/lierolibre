#include "to_string.hpp"

#include <sstream>
#include <string>
#include <stdexcept>

std::string to_string(int value)
{
	std::ostringstream result;
	if (!(result << value))
		throw  BadConversion("to_string()");

	return result.str();
}

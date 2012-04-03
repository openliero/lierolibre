// Compile using:
// g++ -c -o to_string to_string.cpp
#include <sstream>
#include <string>

std::string to_string(int value)
{
	std::ostringstream result;
	result << value;
	return result.str();
}


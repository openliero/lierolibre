#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>


class DataPath
{
public:
	std::string path_readonly(std::string filename);
	std::string path_configdir();
};

#endif //DATA_PATH_HPP

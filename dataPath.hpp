#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
using namespace std;


class DataPath
{
public:
	string path_readonly(string filename);

	string path_configdir(void);
};

#endif //DATA_PATH_HPP

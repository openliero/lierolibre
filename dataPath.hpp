#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
using namespace std;


class DataPath
{
public:
	DataPath(string a_readonly_path);

	string file(string a_filename);

	string configdir(void);

private:
	string a_readonly_path;
	string readonly_path;
	char delimitor;
};

#endif //DATA_PATH_HPP

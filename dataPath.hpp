#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
#include <map>
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
	// map: <filename, writable?>
	std::map<string, bool> file_access_map;
};

#endif //DATA_PATH_HPP

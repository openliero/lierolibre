#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
#include <map>
using namespace std;


class DataPath
{
public:
	DataPath(string a_readonly_path);

	string file(string filename);

	string configdir(void);

private:
	string readonly_path;
	string configdotdir;
	// map: <filename, writable?>
	map<string, bool> file_access_map;

	string create_configdir(string directory);
};

#endif //DATA_PATH_HPP

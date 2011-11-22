#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
using namespace std;


class DataPath
{
public:
	DataPath(string a_lieroexe);

	string file(string filename);

	string configdir(void);

private:
	string lieroexe;
};

#endif //DATA_PATH_HPP

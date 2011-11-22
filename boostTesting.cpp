// Compile & run with:
// ~$ g++ -lboost_unit_test_framework -lboost_filesystem dataPath.o -oboosttest boostTesting.cpp && ./boosttest --loglevel=test_suite

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataPath
#include <boost/test/unit_test.hpp>
#include "boost/filesystem.hpp"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "dataPath.hpp"

using namespace boost::filesystem;

struct DirectorySetup
{
	public:
		map<string, bool> file_access_map;
		string template_string;
		char c_temp_homedir[FILENAME_MAX];
		char c_temp_readonlydir[FILENAME_MAX];
		char c_temp_configdir[FILENAME_MAX];

		string temp_homedir;
		string temp_readonlydir;

		string temp_configdir;
		string original_home;
	DirectorySetup()
	{
//		cout << "begin DirectorySetup" << endl;
		file_access_map.insert(pair<string, bool>("LIERO.EXE", false));
		file_access_map.insert(pair<string, bool>("LIERO.CHR", false));
		file_access_map.insert(pair<string, bool>("LIERO.SND", false));
		file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
		file_access_map.insert(pair<string, bool>("LIERO.DAT", true));

		template_string = "/tmp/liero_tmp_XXXXXX";

		strcpy(c_temp_homedir, template_string.c_str());
		strcpy(c_temp_readonlydir, template_string.c_str());


		temp_homedir = mkdtemp(c_temp_homedir);
		temp_readonlydir = mkdtemp(c_temp_readonlydir);

		temp_configdir = temp_homedir + '/' + ".liero";
		create_directory(temp_configdir);

		setenv("HOME", temp_homedir.c_str(), 1);

	}

	~DirectorySetup()
	{
//	cout << "teardown DirectorySetup" << endl;
	setenv("HOME", original_home.c_str(), 1);
	remove_all(temp_homedir);
	remove_all(temp_readonlydir);
	}
};

struct FilesInReadonlySetup : virtual DirectorySetup
{
	public:
		map<string, bool>::iterator file_access_pair;
		fstream file;
		string filepath;
	FilesInReadonlySetup()
	{
//		cout << "begin FilesInReadonlySetup" << endl;
		for(file_access_pair = file_access_map.begin();
			file_access_pair != file_access_map.end();
			file_access_pair++) {
			filepath = temp_readonlydir + '/'
				 + file_access_pair->first;
			file.open(filepath.c_str(), ios::out);
			if(file.is_open()) {
				file << "readonly "
					<< file_access_pair->first << endl;
				file.close();
			} else {
				cout << "Can't write to file: " << file << endl;
			}
		}
	}
	~FilesInReadonlySetup()
	{
//		cout << "teardown FilesInReadonlySetup" << endl;
	}
};

struct FilesInWritableSetup : virtual DirectorySetup
{
	public:
		map<string, bool>::iterator file_access_pair;
		fstream file;
		string filepath;
	FilesInWritableSetup()
	{
//		cout << "begin FilesInWritableSetup" << endl;
		for(file_access_pair = file_access_map.begin();
			file_access_pair != file_access_map.end();
			file_access_pair++) {
			if(file_access_pair->second) {
				filepath = temp_configdir + '/'
					+ file_access_pair->first;
				file.open(filepath.c_str(), ios::out);
				if(file.is_open()) {
					file << "writable "
						<< file_access_pair->first
						<< endl;
					file.close();
				} else {
					cout << "Can't write to file: "
						 << file << endl;
				}
			}
		}
	}
	~FilesInWritableSetup()
	{
//		cout << "teardown FilesInWritableSetup" << endl;
	}
};

struct AllFilesSetup : FilesInWritableSetup, FilesInReadonlySetup
{
	AllFilesSetup()
	{
//		cout << "begin AllFilesSetup" << endl;
	}
	~AllFilesSetup()
	{
//		cout << "teardown AllFilesSetup" << endl;
	}
};

const char *home = "HOME";
const char *dotdir = "/.liero";
const char *lierodat_fname = "/LIERO.DAT";
const char *lieroexe_fname = "/LIERO.EXE";
const char template_string[] = "/tmp/liero_tmp_XXXXXX";

map<string, bool> file_access_map;
void init_map()
{
file_access_map.insert(pair<string, bool>("LIERO.EXE", false));
file_access_map.insert(pair<string, bool>("LIERO.CHR", false));
file_access_map.insert(pair<string, bool>("LIERO.SND", false));
file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
file_access_map.insert(pair<string, bool>("LIERO.DAT", true));
}

map<string, bool>::iterator file_access_pair;


BOOST_FIXTURE_TEST_CASE(configdir_return_correct_path, DirectorySetup)
{
	DataPath data_path(temp_readonlydir);

	BOOST_CHECK_EQUAL(data_path.configdir(), temp_configdir);

//	printf("### end test configdir_return_correct_path\n");
}

BOOST_FIXTURE_TEST_CASE(configdir_can_create_file, DirectorySetup)
{
	string configfile_path;
	fstream configfile;

	DataPath data_path(temp_readonlydir);

	configfile_path = data_path.configdir() + '/' + "RW";
	configfile.open(configfile_path.c_str(), ios::out);

	BOOST_CHECK(configfile.is_open());

//	printf("### end test configdir_can_create_file\n");
}

BOOST_FIXTURE_TEST_CASE(lieroexe_return_correct_path, FilesInReadonlySetup)
{
	string lieroexe_path;

	DataPath data_path(temp_readonlydir);

	lieroexe_path = temp_readonlydir + '/' + "LIERO.EXE";

	BOOST_CHECK_EQUAL(data_path.file("LIERO.EXE"), lieroexe_path);

//	printf("### end test lieroexe_return_correct_path\n");
}

BOOST_AUTO_TEST_CASE(files_in_map)
{
	char temp_readonlydir[FILENAME_MAX];
	char temp_configdir[FILENAME_MAX];
	char filepath_readonly[FILENAME_MAX];
	char filepath_writable[FILENAME_MAX];
        FILE *file_readonly;
        FILE *file_writable;
	init_map();

	strcpy(temp_readonlydir, template_string);
	strcpy(temp_configdir, template_string);
	mkdtemp(temp_readonlydir);
	mkdtemp(temp_configdir);

	for(file_access_pair = file_access_map.begin(); file_access_pair != file_access_map.end(); file_access_pair++) {
		strcpy(filepath_readonly, temp_readonlydir);
		strcat(filepath_readonly, file_access_pair->first.c_str());
		if(file_access_pair->second) {
			// file should be writable
			setenv(home, temp_configdir, 1);
			strcpy(filepath_writable, temp_configdir);
			strcat(filepath_writable, "/");
			strcat(filepath_writable, file_access_pair->first.c_str());
		} else {
			// file should not be writable
		}
	}

	remove_all(temp_readonlydir);
	remove_all(temp_configdir);

//	printf("### end test files_in_map\n");
}


// Compile & run with:
// ~$ g++ -lboost_unit_test_framework -lboost_filesystem dataPath.o -oboosttestfixtures boostTestingFixtures.cpp && ./boosttestfixtures

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataPathFixtures
#include <boost/test/unit_test.hpp>
#include "boost/filesystem.hpp"

#include <stdlib.h>
#include <stdio.h>

#include "dataPath.hpp"

using namespace boost::filesystem;

struct CreateFolders
{
	
const char *home = "HOME";
const char *dotdir = "/.liero";
const char *lierodat_fname = "/LIERO.DAT";
const char *lieroexe_fname = "/LIERO.EXE";
const char template_string[] = "/tmp/liero_tmp_XXXXXX";

map<string, bool> mfile_access_map;
mfile_access_map.insert(pair<string, bool>("LIERO.EXE", false));
mfile_access_map.insert(pair<string, bool>("LIERO.CHR", false));
mfile_access_map.insert(pair<string, bool>("LIERO.SND", false));
mfile_access_map.insert(pair<string, bool>("LIERO.OPT", true));
mfile_access_map.insert(pair<string, bool>("LIERO.DAT", true));

map<string, bool>:iterator file_access_pair;


BOOST_AUTO_TEST_CASE(configdir_return_correct_path)
{
	char configdir[FILENAME_MAX];
	char tempdir[FILENAME_MAX];

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
	setenv(home, tempdir, 1);

        strcpy(configdir, tempdir);
	strcat(configdir, dotdir);

	DataPath data_path("/usr/lib/liero");

	BOOST_CHECK(strcmp(data_path.configdir().c_str(), configdir) == 0);
//	printf("data_path.configdir().c_str() = %s and configdir = %s\n\n", data_path.configdir().c_str(), configdir);

	remove_all(tempdir);

	printf("### end test configdir_return_correct_path\n\n");
}

BOOST_AUTO_TEST_CASE(configdir_can_create_file)
{
	const char *configdir;
	char configfile_path[FILENAME_MAX];
	char tempdir[FILENAME_MAX];
        FILE *configfile;

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
	setenv(home, tempdir, 1);

	DataPath data_path("/usr/lib/liero");
	configdir = data_path.configdir().c_str();

	strcpy(configfile_path, configdir);
	strcat(configfile_path, lierodat_fname);

	BOOST_CHECK(configfile = fopen(configfile_path, "w+"));
	fclose(configfile);

	remove_all(tempdir);

	printf("### end test configdir_can_create_file\n\n");
}

BOOST_AUTO_TEST_CASE(lieroexe_return_correct_path)
{
	char tempdir[FILENAME_MAX];
	char lieroexe_path[FILENAME_MAX];
        FILE *lieroexe;

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
//	printf("tempdir: %s\n", tempdir);
	strcpy(lieroexe_path, tempdir);
	strcat(lieroexe_path, lieroexe_fname);
//	printf("lieroexe_path: %s\n", lieroexe_path);
	lieroexe = fopen(lieroexe_path, "w+");
	fclose(lieroexe);

	DataPath data_path(tempdir);

//	printf("data_path.file(\"LIERO.EXE\").c_str(): %s\n", data_path.file("LIERO.EXE").c_str());
	BOOST_CHECK(strcmp(data_path.file("LIERO.EXE").c_str(), lieroexe_path) == 0);

	remove_all(tempdir);

	printf("### end test lieroexe_return_correct_path\n\n");
}

BOOST_AUTO_TEST_CASE(files_in_map)
{
	char temp_readonlydir[FILENAME_MAX];
	char temp_configdir[FILENAME_MAX];
	char filepath_readonly[FILENAME_MAX];
	char filepath_writable[FILENAME_MAX];
        FILE *file_readonly;
        FILE *file_writable;

	strcpy(temp_readonlydir, template_string);
	strcpy(temp_configdir, template_string);
	mkdtemp(temp_readonlydir);
	mkdtemp(temp_configdir);

	for(file_access_pair = file_access_map.begin(), file_access_pair != file_access_map.end(), file_access_pair++) {
		strcpy(filepath_readonly, temp_readonlydir);
		strcat(filepath_readonly, file_access_pair->first);
		if(file_access_pair->second) {
			// file should be writable
			setenv(home, temp_configdir, 1);
			strcpy(filepath_writable, temp_configdir);
			strcat(filepath_writable, '/');
			strcat(filepath_writable, file_access_pair->first.c_str());
		} else {
			// file should not be writable
		}
	}

	remove_all(tempdir);

	printf("### end test files_in_map\n\n");
}


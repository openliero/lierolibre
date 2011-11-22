// Compile & run with:
// ~$ g++ -lboost_unit_test_framework -lboost_filesystem dataPath.o -oboosttest boostTesting.cpp && ./boosttest

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataPath
#include <boost/test/unit_test.hpp>
#include "boost/filesystem.hpp"

#include <stdlib.h>
#include <stdio.h>

#include "dataPath.hpp"

using namespace boost::filesystem;

const char *home_varname = "HOME";
const char *dotdir = "/.liero";
const char *afile = "/LIERO.DAT";
char template_string[] = "/tmp/lireo_configdir_tmp_XXXXXX";
char *tempdir;

BOOST_AUTO_TEST_CASE(configdir_return_correct_path)
{
	char *configdir;

	tempdir = mkdtemp(template_string);
	setenv("HOME", tempdir, 1);
        strcpy(configdir, tempdir);
	strcat(configdir, dotdir);
	DataPath data_path;

	BOOST_CHECK(data_path.path_configdir().c_str() == configdir);

	remove_all(tempdir);
}

BOOST_AUTO_TEST_CASE(configdir_can_create_file)
{
	const char *configdir;
	char *configfile_path;
        FILE *configfile;

	tempdir = mkdtemp(template_string);
	setenv("HOME", tempdir, 1);
	DataPath data_path;
	configdir = data_path.path_configdir().c_str();
	strcpy(configfile_path, configdir);
	strcat(configfile_path, afile);


	BOOST_CHECK(configfile = fopen(configfile_path, "w+"));
	fclose(configfile);

	remove_all(tempdir);
}

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

const char *home = "HOME";
const char *dotdir = "/.liero";
const char *afile = "/LIERO.DAT";
const char template_string[] = "/tmp/liero_configdir_tmp_XXXXXX";

BOOST_AUTO_TEST_CASE(configdir_return_correct_path)
{
	char configdir[500];
	char tempdir[500];

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
	setenv(home, tempdir, 1);

        strcpy(configdir, tempdir);
	strcat(configdir, dotdir);

	DataPath data_path("/usr/lib/liero");

	BOOST_CHECK(strcmp(data_path.configdir().c_str(), configdir) == 0);

	remove_all(tempdir);
}

BOOST_AUTO_TEST_CASE(configdir_can_create_file)
{
	const char *configdir;
	char configfile_path[500];
	char tempdir[500];
        FILE *configfile;

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
	setenv(home, tempdir, 1);
	printf("tempdir: %s\n", tempdir);

	DataPath data_path("/usr/lib/liero");
	configdir = data_path.configdir().c_str();

	strcpy(configfile_path, configdir);
	strcat(configfile_path, afile);
	printf("configfile_path: %s\n", configfile_path);

	BOOST_CHECK(configfile = fopen(configfile_path, "w+"));
	fclose(configfile);

	remove_all(tempdir);
}

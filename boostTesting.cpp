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
const char *lierodat_fname = "/LIERO.DAT";
const char *lieroexe_fname = "/LIERO.EXE";
const char template_string[] = "/tmp/liero_tmp_XXXXXX";

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

	printf("### end test configdir_return_correct_path\n\n");
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
	char tempdir[500];
	char lieroexe_path[500];
        FILE *lieroexe;

	strcpy(tempdir, template_string);
	mkdtemp(tempdir);
	printf("tempdir: %s\n", tempdir);
	strcpy(lieroexe_path, tempdir);
	strcat(lieroexe_path, lieroexe_fname);
	printf("lieroexe_path: %s\n", lieroexe_path);
	lieroexe = fopen(lieroexe_path, "w+");
	fclose(lieroexe);

	DataPath data_path(tempdir);


	BOOST_CHECK(strcmp(data_path.file("LIERO.EXE").c_str(), lieroexe_path) == 0);

	remove_all(tempdir);

	printf("### end test lieroexe_return_correct_path\n\n");
}

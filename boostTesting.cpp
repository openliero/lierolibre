// Compile & run with:
// ~$ g++ -lboost_unit_test_framework -lboost_filesystem dataPath.o -oboosttest boostTesting.cpp && ./boosttest --loglevel=test_suite

/*
 These are unit tests for dataPath.

 Copyright (c) 2011, Martin Erik Werner <martinerikwerner@gmail.com>
 This software is released under the The BSD-2-Clause License:

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

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
		string template_string;
		char c_temp_homedir[FILENAME_MAX];
		char c_temp_readonlydir[FILENAME_MAX];
		string temp_homedir;
		string temp_readonlydir;
		string temp_configdir;
		string original_home;

		map<string, bool> file_access_map;
		map<string, bool>::iterator file_access_pair;
		fstream file;
		string filepath;
	DirectorySetup()
	{
//		cout << "begin DirectorySetup" << endl;
		file_access_map.insert(pair<string, bool>("LIERO.EXE",
								false));
		file_access_map.insert(pair<string, bool>("LIERO.CHR",
								false));
		file_access_map.insert(pair<string, bool>("LIERO.SND",
								false));
		file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
		file_access_map.insert(pair<string, bool>("LIERO.DAT", true));

		template_string = "/tmp/liero_tmp_XXXXXX";
		strcpy(c_temp_homedir, template_string.c_str());
		strcpy(c_temp_readonlydir, template_string.c_str());

		temp_homedir = mkdtemp(c_temp_homedir);
		temp_readonlydir = mkdtemp(c_temp_readonlydir);

		original_home = getenv("HOME");
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

struct ConfigdirSetup : DirectorySetup
{
	ConfigdirSetup()
	{
		temp_configdir = temp_homedir + '/' + ".liero";

		create_directory(temp_configdir);
	}
};

struct FilesInReadonlySetup : virtual ConfigdirSetup
{
	FilesInReadonlySetup()
	{
//		cout << "begin FilesInReadonlySetup" << endl;
		// create all files with content "readonly FILENAME"
		for (file_access_pair = file_access_map.begin();
				file_access_pair != file_access_map.end();
				file_access_pair++) {
			filepath = temp_readonlydir + '/'
				 + file_access_pair->first;
			file.open(filepath.c_str(), ios::out);
			if (file.is_open()) {
				file << "readonly "
					<< file_access_pair->first << endl;
				file.close();
			} else {
				cout << "Can't write to file: "
							<< file << endl;
			}
		}
	}
	~FilesInReadonlySetup()
	{
//		cout << "teardown FilesInReadonlySetup" << endl;
	}
};

struct FilesInWritableSetup : virtual ConfigdirSetup
{
	FilesInWritableSetup()
	{
//		cout << "begin FilesInWritableSetup" << endl;
		// create all writable files with content "writable FILENAME"
		for (file_access_pair = file_access_map.begin();
				file_access_pair != file_access_map.end();
				file_access_pair++) {
			if (file_access_pair->second) {
				// file should be writable
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

BOOST_FIXTURE_TEST_CASE(configdir_exists__Path, ConfigdirSetup)
{
	DataPath data_path(temp_readonlydir);

	BOOST_CHECK_EQUAL(data_path.configdir(), temp_configdir);
}

BOOST_FIXTURE_TEST_CASE(configdir_exists__CreateFile, ConfigdirSetup)
{
	string configfile_path;
	fstream configfile;
	DataPath data_path(temp_readonlydir);

	configfile_path = data_path.configdir() + '/' + "W";
	configfile.open(configfile_path.c_str(), ios::out);
	BOOST_CHECK(configfile.is_open());
}

BOOST_FIXTURE_TEST_CASE(configdir_no_exists__CreateFile, DirectorySetup)
{
	string configfile_path;
	fstream configfile;
	DataPath data_path(temp_readonlydir);

	configfile_path = data_path.configdir() + '/' + "W";
	configfile.open(configfile_path.c_str(), ios::out);
	BOOST_CHECK(configfile.is_open());
}

BOOST_FIXTURE_TEST_CASE(lieroexe_no_exists__Error, ConfigdirSetup)
{
	DataPath data_path(temp_readonlydir);

	// test if error for no file anywhere is correct
	BOOST_CHECK_EQUAL(data_path.file("LIERO.EXE"), "ENOFILE");
}

BOOST_FIXTURE_TEST_CASE(lieroexe_ro_exists__Path_Nocopy, FilesInReadonlySetup)
{
	string lieroexe_path;
	string lieroexe_wrong_path;
	fstream lieroexe_wrong;
	DataPath data_path(temp_readonlydir);

	// test returned path
	lieroexe_path = temp_readonlydir + '/' + "LIERO.EXE";
	BOOST_CHECK_EQUAL(data_path.file("LIERO.EXE"), lieroexe_path);

	// make sure it wasn't copied to configdir
	lieroexe_wrong_path = temp_configdir + '/' + "LIERO.EXE";
	lieroexe_wrong.open(lieroexe_wrong_path.c_str(), ios::out|ios::in);
	BOOST_CHECK(!lieroexe_wrong.is_open());
}

BOOST_FIXTURE_TEST_CASE(lierodat_no_exists__Path, ConfigdirSetup)
{
	DataPath data_path(temp_readonlydir);

	BOOST_CHECK_EQUAL(data_path.file("LIERO.DAT"), "ENOFILE");
}

BOOST_FIXTURE_TEST_CASE(lierodat_ro_exists__Path_Writable_Contents,
							FilesInReadonlySetup)
{
	string lierodat_ro_path;
	string lierodat_rw_path;
	fstream lierodat_rw;
	fstream lierodat_ro;
	stringstream lierodat_ro_buffer;
	stringstream lierodat_rw_buffer;

	// save readonly contents to buffer
	lierodat_ro_path = temp_readonlydir + '/' + "LIERO.DAT";
	lierodat_ro.open(lierodat_ro_path.c_str(), ios::in);
	if (lierodat_ro.is_open()) {
		lierodat_ro_buffer << lierodat_ro.rdbuf();
		lierodat_ro.close();
	} else {
		cout << "Can't read readonly DAT" << endl;
	}

	DataPath data_path(temp_readonlydir);

	// test returned path
	lierodat_rw_path = temp_configdir + '/' + "LIERO.DAT";
	BOOST_CHECK_EQUAL(data_path.file("LIERO.DAT"), lierodat_rw_path);

	// test if file is rw
	lierodat_rw.open(lierodat_rw_path.c_str(), ios::out|ios::in);
	BOOST_CHECK(lierodat_rw.is_open());

	if (lierodat_rw.is_open()) {
		lierodat_rw_buffer << lierodat_rw.rdbuf();
		// convert both buffers to strings and compare
		BOOST_CHECK_EQUAL(lierodat_ro_buffer.str(),
						lierodat_rw_buffer.str());
		lierodat_rw.close();
	} else {
		BOOST_ERROR("Cant open rw after copying");
	}
}

BOOST_FIXTURE_TEST_CASE(lierodat_rw_exists__Path, FilesInWritableSetup)
{
	string lierodat_path;
	fstream lierodat;
	DataPath data_path(temp_readonlydir);

	// test returned path and if file is rw
	lierodat_path = temp_configdir + '/' + "LIERO.DAT";
	BOOST_CHECK_EQUAL(data_path.file("LIERO.DAT"), lierodat_path);
	lierodat.open(lierodat_path.c_str(), ios::out|ios::in);
	BOOST_CHECK(lierodat.is_open());
}

BOOST_FIXTURE_TEST_CASE(all_exists__NoOverwrite, AllFilesSetup)
{
	string lierodat_ro_path;
	string lierodat_rw_path;
	fstream lierodat_rw;
	fstream lierodat_ro;
	stringstream lierodat_buffer;
	string lierodat_ro_orig_content;
	string lierodat_rw_orig_content;

	// save readonly file content
	lierodat_ro_path = temp_readonlydir + '/' + "LIERO.DAT";
	lierodat_ro.open(lierodat_ro_path.c_str(), ios::in);
	if (lierodat_ro.is_open()) {
		lierodat_buffer << lierodat_ro.rdbuf();
		lierodat_ro.close();
		lierodat_ro_orig_content = lierodat_buffer.str();
		// clear buffer
		lierodat_buffer.str("");
	} else {
		cout << "Can't read readonly DAT" << endl;
	}

	// save writable file content
	lierodat_rw_path = temp_configdir + '/' + "LIERO.DAT";
	lierodat_rw.open(lierodat_rw_path.c_str(), ios::in);
	if(lierodat_rw.is_open()) {
		lierodat_buffer << lierodat_rw.rdbuf();
		lierodat_rw.close();
		lierodat_rw_orig_content = lierodat_buffer.str();
		// clear buffer
		lierodat_buffer.str("");
	} else {
		cout << "Can't read writable DAT" << endl;
	}

	DataPath data_path(temp_readonlydir);
	data_path.file("LIERO.DAT");

	lierodat_ro.open(lierodat_ro_path.c_str(), ios::in);
	if (lierodat_ro.is_open()) {
		lierodat_buffer << lierodat_ro.rdbuf();
		lierodat_ro.close();
		// check that file is unchanged
		BOOST_CHECK_EQUAL(lierodat_ro_orig_content,
						lierodat_buffer.str());
		// clear buffer
		lierodat_buffer.str("");
	} else {
		cout << "Can't read readonly DAT" << endl;
	}

	lierodat_rw.open(lierodat_rw_path.c_str(), ios::in);
	if (lierodat_rw.is_open()) {
		lierodat_buffer << lierodat_rw.rdbuf();
		lierodat_rw.close();
		// check that file is unchanged
		BOOST_CHECK_EQUAL(lierodat_rw_orig_content,
						lierodat_buffer.str());
		// clear buffer
		lierodat_buffer.str("");
	} else {
		cout << "Can't read writable DAT" << endl;
	}
}

BOOST_FIXTURE_TEST_CASE(all_exists__IncompleteFilename, AllFilesSetup)
{
	DataPath data_path(temp_readonlydir);
	BOOST_CHECK_EQUAL(data_path.file("LIE"), "ENOFILE");
}

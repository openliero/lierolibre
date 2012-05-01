// Compile & run with:
// ~$ g++ -lboost_unit_test_framework -lboost_system -lboost_filesystem dataPath.o filesystem.o -oboosttest boostTesting.cpp && ./boosttest --loglevel=test_suite

/*
 * These are unit tests for dataPath.
 *
 * Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
 * This software is released under the The BSD-2-Clause License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DataPath
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "dataPath.hpp"

using namespace boost::filesystem;
using namespace std;

string correct_message;

bool test_exception_message(exception const& ex) {
	return ex.what() == correct_message;
}

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
		vector<string> names_rw;
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
		file_access_map.insert(pair<string, bool>("NAMES.DAT",
								false));
		file_access_map.insert(pair<string, bool>("LIERO.OPT", true));
		file_access_map.insert(pair<string, bool>("LIERO.DAT", true));
		file_access_map.insert(pair<string, bool>("liero.cfg", true));
		file_access_map.insert(pair<string, bool>("liero.txt", true));

		names_rw.push_back("LIERO.DAT");
		names_rw.push_back("liero.cfg");
		names_rw.push_back("liero.txt");

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
		temp_configdir = temp_homedir + '/' + ".lierolibre";

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
	correct_message = "Could not open file '" + temp_readonlydir + '/'
						 + "LIERO.EXE"  + "'";

	BOOST_CHECK_EXCEPTION(throw data_path.file("LIERO.EXE"),
						runtime_error,
						test_exception_message);
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

BOOST_FIXTURE_TEST_CASE(liero_rwfile_no_exists__Error, ConfigdirSetup)
{
	DataPath data_path(temp_readonlydir);

	for  (int i = 0; i < names_rw.size(); ++i ) {
		correct_message = "Could not open file '" + temp_configdir + '/' + names_rw.at(i) + "'";
		BOOST_CHECK_EXCEPTION(throw data_path.file(names_rw.at(i)), runtime_error, test_exception_message);
	}
}

BOOST_FIXTURE_TEST_CASE(liero_rwfile_ro_exists__Path_Writable_Contents,
							FilesInReadonlySetup)
{
	for  (int i = 0; i < names_rw.size(); ++i ) {
		string path_ro;
		string path_rw;
		fstream f_rw;
		fstream f_ro;
		stringstream buf_ro;
		stringstream buf_rw;

		// save readonly contents to buffer
		path_ro = temp_readonlydir + '/' + names_rw.at(i);
		f_ro.open(path_ro.c_str(), ios::in);
		if (f_ro.is_open()) {
			buf_ro << f_ro.rdbuf();
			f_ro.close();
		} else {
			cout << "Can't read readonly '" + names_rw.at(i) + "'" << endl;
		}

		DataPath data_path(temp_readonlydir);

		// test returned path
		path_rw = temp_configdir + '/' + names_rw.at(i);
		BOOST_CHECK_EQUAL(data_path.file(names_rw.at(i)), path_rw);

		// test if file is rw
		f_rw.open(path_rw.c_str(), ios::out|ios::in);
		BOOST_CHECK(f_rw.is_open());

		if (f_rw.is_open()) {
			buf_rw << f_rw.rdbuf();
			// convert both buffers to strings and compare
			BOOST_CHECK_EQUAL(buf_ro.str(), buf_rw.str());
			f_rw.close();
		} else {
			BOOST_ERROR("Cant open rw after copying");
		}
	}
}

BOOST_FIXTURE_TEST_CASE(liero_rwfile_exists__Path, FilesInWritableSetup)
{
	DataPath data_path(temp_readonlydir);

	for  (int i = 0; i < names_rw.size(); ++i ) {
		string path;
		fstream f;

		// test returned path and if file is rw
		path = temp_configdir + '/' + names_rw.at(i);
		BOOST_CHECK_EQUAL(data_path.file(names_rw.at(i)), path);
		f.open(path.c_str(), ios::out|ios::in);
		BOOST_CHECK(f.is_open());
	}
}

BOOST_FIXTURE_TEST_CASE(all_exists__NoOverwrite, AllFilesSetup)
{
	for  (int i = 0; i < names_rw.size(); ++i ) {
		string path_ro;
		string path_rw;
		fstream f_rw;
		fstream f_ro;
		stringstream buf_ro;
		stringstream buf_rw;
		stringstream buf;
		string orig_content_ro;
		string orig_content_rw;

		// save readonly file content
		path_ro = temp_readonlydir + '/' + names_rw.at(i);
		f_ro.open(path_ro.c_str(), ios::in);
		if (f_ro.is_open()) {
			buf << f_ro.rdbuf();
			f_ro.close();
			orig_content_ro = buf.str();
			// clear buffer
			buf.str("");
		} else {
			cout << "Can't read readonly '" + names_rw.at(i) + "'" << endl;
		}

		// save writable file content
		path_rw = temp_configdir + '/' + names_rw.at(i);
		f_rw.open(path_rw.c_str(), ios::in);
		if(f_rw.is_open()) {
			buf << f_rw.rdbuf();
			f_rw.close();
			orig_content_rw = buf.str();
			// clear buffer
			buf.str("");
		} else {
			cout << "Can't read writable '" + names_rw.at(i) + "'" << endl;
		}

		DataPath data_path(temp_readonlydir);
		data_path.file(names_rw.at(i));

		f_ro.open(path_ro.c_str(), ios::in);
		if (f_ro.is_open()) {
			buf << f_ro.rdbuf();
			f_ro.close();
			// check that file is unchanged
			BOOST_CHECK_EQUAL(orig_content_ro, buf.str());
			// clear buffer
			buf.str("");
		} else {
			cout << "Can't read readonly '" + names_rw.at(i) + "'" << endl;
		}

		f_rw.open(path_rw.c_str(), ios::in);
		if (f_rw.is_open()) {
			buf << f_rw.rdbuf();
			f_rw.close();
			// check that file is unchanged
			BOOST_CHECK_EQUAL(orig_content_rw, buf.str());
			// clear buffer
			buf.str("");
		} else {
			cout << "Can't read writable '" + names_rw.at(i) + "'" << endl;
		}
	}
}

BOOST_FIXTURE_TEST_CASE(all_exists__IncompleteFilename, AllFilesSetup)
{
	DataPath data_path(temp_readonlydir);

	correct_message = "Unknown file 'LIE'";

	BOOST_CHECK_EXCEPTION(throw data_path.file("LIE"),
						runtime_error,
						test_exception_message);
}

BOOST_FIXTURE_TEST_CASE(all_exists__AnyDatPath_AnyDatRw, AllFilesSetup)
{
	string meepdat_path;
	fstream meepdat;
	DataPath data_path(temp_readonlydir);

	// test returned path and if file is rw
	meepdat_path = temp_configdir + '/' + "MEEP.DAT";
	BOOST_CHECK_EQUAL(data_path.file("MEEP.DAT"), meepdat_path);
	meepdat.open(meepdat_path.c_str(), ios::out);
	BOOST_CHECK(meepdat.is_open());
}

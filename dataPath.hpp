/* This object is intended to simplify integration into a GNU/Linux multi-user
 * system.
 * It contains two methods, file() and configdir().
 * The constructor requires a path to a directory containing the (readonly)
 * Liero data files.
 *
 * file() is used for getting the path to a file that Liero might want to read
 * or write to, it accepts a filename, e.g. "LIERO.DAT". When it is invoked it
 * goes through the following steps:
 * * Checks if the file should be writable or readonly, using an internally
 *   defined map
 * * If file should be readonly, checks if file exists, then returns its path
 * * If file should be writable, it makes sure the file exits in the
 *   $HOME/.lierolibre directory (by copying if need be), then returns its path
 * * Throws runtime_error()s if it is unable to provide the path.

 * configdir() is used simply for getting the path to the $HOME/.liero
 * directory, creating it if need be.
 * configdir() throws a runtime_error() if it is unable to provide the path.
 *
 * Unit tests for this object are avaialble in boostTesting.cpp
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

#ifndef DATA_PATH_HPP
#define DATA_PATH_HPP

#include <string>
#include <map>

class DataPath
{
public:
	DataPath(std::string a_readonly_path);

	std::string file(std::string filename);

	std::string configdir(void);

private:
	std::string readonly_path;
	std::string configdotdir;
	// map: <filename, writable?>
	std::map<std::string, bool> file_access_map;
};

#endif //DATA_PATH_HPP

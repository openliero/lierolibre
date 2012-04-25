/*
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

#include "argParse.hpp"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

ArgParse::ArgParse(int argc, char* argv[])
{
	// Declare the supported options.
	desc.add_options()
	("help,h", "produce help message")
	("sdlvideo,v", po::value<string>(), "set the SDL_VIDEODRIVER environemtn variable")
	("file,f", po::value<string>(), "read game variables from file")
	("dir,d", po::value<string>(), "load game data from separate directory")
	("write,w", po::value<string>(), "write game variables to file")
	;

	// First positional option is input file
	// second is data dir, third is output file
	po::positional_options_description p;
	p.add("file", 1).add("dir", 1).add("write", 1);

	// Export to "vm"
	po::store(po::command_line_parser(argc, argv)
		.options(desc).positional(p).run(), vm);
	po::notify(vm);
}

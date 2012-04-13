/*
 Copyright (c) 2012, Martin Erik Werner <martinerikwerner@gmail.com>
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

#ifndef CONFIG_HELPER_HPP
#define CONFIG_HELPER_HPP

#include <string>
#include <libconfig.h++>

// Fixed-width integer types
#include <SDL/SDL.h>

class ConfigHelper
{
public:
	template<typename Dest, typename Node, typename Idx>
	Dest getValue(Node &node, Idx index);

	void put(libconfig::Setting &node, std::string variable, bool value);
	void put(libconfig::Setting &node, std::string variable, Uint8 value);
	void put(libconfig::Setting &node, std::string variable, int value);
	void put(libconfig::Setting &node, std::string variable, std::string value);

	libconfig::Setting& mkArray(libconfig::Setting &node, std::string arrayName);
	libconfig::Setting& getSubgroup(libconfig::Setting &node, std::string groupName);
};

#endif // CONFIG_HELPER_HPP


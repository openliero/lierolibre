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

#ifndef LIERO_CONFIG_INIT_HPP
#define LIERO_CONFIG_INIT_HPP

#define CFGVERSION 1 // Bump in case of CFG file format changes

#include "configHelper.hpp"

#include <string>
#include <gvl/resman/shared_ptr.hpp>

#include "common.hpp"

class ConfigInit
{
public:
	ConfigInit(std::string filePath, gvl::shared_ptr<Common> a_common);
	ConfigInit(std::string filePath, std::string dirPath, gvl::shared_ptr<Common> a_common);

	void write(std::string cfgFilePath);

private:
	void loadFromEXE(std::string exeFilePath);
	void loadFromCFG(std::string cfgFilePath);
	bool upgradeCFG(std::string filePath, int version);
	void consoleBlurb();

	gvl::shared_ptr<Common> common;
};

#endif // LIERO_CONFIG_INIT_HPP

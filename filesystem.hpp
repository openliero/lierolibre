/*
 * Copyright (c) 2010, Erik Lindroos <gliptic@gmail.com>
 * Copyright (c) 2010, "basro"
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

#ifndef LIERO_FILESYSTEM_HPP
#define LIERO_FILESYSTEM_HPP

#include <string>
#include <cstdio>
#include <memory>

std::string changeLeaf(std::string const& path, std::string const& newLeaf);
std::string getRoot(std::string const& path);
std::string getBasename(std::string const& path);
std::string getExtension(std::string const& path);
void toUpperCase(std::string& str);
std::string joinPath(std::string const& root, std::string const& leaf);

bool fileExists(std::string const& path);

FILE* tolerantFOpen(std::string const& name, char const* mode);

std::size_t fileLength(FILE* f);

struct dir_itr_imp;
typedef std::auto_ptr<dir_itr_imp> dir_itr_imp_ptr;


void dir_itr_init( dir_itr_imp_ptr & m_imp, char const* dir_path );
std::string& dir_itr_dereference(dir_itr_imp_ptr const& m_imp );
std::string& dir_itr_alt_dereference(dir_itr_imp_ptr const& m_imp );
void dir_itr_increment( dir_itr_imp_ptr & m_imp );

struct DirectoryIterator
{
	dir_itr_imp_ptr m_imp;

	DirectoryIterator(std::string const& dir);
	~DirectoryIterator();

	operator void*()
	{
		return m_imp.get();
	}

	std::string const& operator*() const
	{
		return dir_itr_dereference( m_imp );
	}

	std::string const& alt() const
	{
		return dir_itr_alt_dereference( m_imp );
	}

	void operator++()
	{
		dir_itr_increment(m_imp);
	}
};

struct ScopedFile
{
	ScopedFile(FILE* f)
	: f(f)
	{
	}

	~ScopedFile()
	{
		if(f) fclose(f);
	}

	operator FILE*()
	{
		return f;
	}

	FILE* f;
};

#endif // LIERO_FILESYSTEM_HPP

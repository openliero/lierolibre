/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
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

#ifndef VAR_READER_HPP
#define VAR_READER_HPP

#include <SDL/SDL.h>
#include <string>

void checkedFread(void* ptr, size_t size, size_t count, FILE* f);

std::string readPascalString(FILE* f);
std::string readPascalString(FILE* f, unsigned char fieldLen);
std::string readPascalStringAt(FILE* f, int location);

void writePascalString(FILE* f, std::string const& str, unsigned char fieldLen);

Uint32 readUint8(FILE* f);
Sint32 readSint8(FILE* f);
Uint32 readUint16(FILE* f);
Sint32 readSint16(FILE* f);
Uint32 readUint32(FILE* f);
Sint32 readSint32(FILE* f);

void writeUint8(FILE* f, Uint32 v);
void writeUint16(FILE* f, Uint32 v);

#endif //VAR_READER_HPP

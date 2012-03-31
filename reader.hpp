#ifndef LIERO_READER_HPP
#define LIERO_READER_HPP

#include <cstdio>
#include <string>
#include <stdexcept>
#include <SDL/SDL.h>

#include "varreader.hpp"

extern std::string lieroEXERoot;
extern std::string lieroOPT;

// Return an opened file
FILE* openFile(std::string const& name);

FILE* openLieroEXE();
FILE* openLieroSND();
FILE* openLieroCHR();

void setLieroEXE(std::string const& path);

// Close old files
void processReader();
void closeAllCachedFiles();

#endif // LIERO_READER_HPP


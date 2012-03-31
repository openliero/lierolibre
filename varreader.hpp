#ifndef VAR_READER_HPP
#define VAR_READER_HPP

#include <SDL/SDL.h>
#include <string>

using namespace std;

void checkedFread(void* ptr, size_t size, size_t count, FILE* f);

string readPascalString(FILE* f);
string readPascalString(FILE* f, unsigned char fieldLen);
string readPascalStringAt(FILE* f, int location);

void writePascalString(FILE* f, string const& str, unsigned char fieldLen);

Uint32 readUint8(FILE* f);
Sint32 readSint8(FILE* f);
Uint32 readUint16(FILE* f);
Sint32 readSint16(FILE* f);
Uint32 readUint32(FILE* f);
Sint32 readSint32(FILE* f);

void writeUint8(FILE* f, Uint32 v);
void writeUint16(FILE* f, Uint32 v);

#endif //VAR_READER_HPP

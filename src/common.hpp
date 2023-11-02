#ifndef COMMON_HPP
#define COMMON_HPP
#include "types.h"
#include "rb3/symbol.hpp"
#include "rb3/textfile.hpp"

// placement new
inline void* operator new (unsigned long size, void* p) { return p; }

// misc functions
int Minimum(int, int);
unsigned int Minimum(unsigned int, unsigned int);
unsigned short SwapDataHalfWord(unsigned short);
unsigned int SwapDataWord(int);
long long SwapDataDoubleWord(long long);

void FileQualifiedFilename(char*, int, const char*);
extern "C" char* FileGetDrive(char*);

#endif

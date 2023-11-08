#ifndef COMMON_HPP
#define COMMON_HPP
#include "types.h"
#include "rb3/symbol.hpp"
#include "rb3/textfile.hpp"
#include "rb3/data.hpp"

// placement new
inline void* operator new (unsigned long size, void* p) { return p; }

// evaluate a DataNode at a particular index
DataNode* EvaluateNodeAtIndex(DataArray*, int);

// misc functions
int Minimum(int, int);
unsigned int Minimum(unsigned int, unsigned int);
bool SearchReplace(const char*, const char*, const char*, char*);
int Round(float);

// functions to swap endians of data
void SwapData(const void*, void*, int);
unsigned short SwapDataHalfWord(unsigned short);
unsigned int SwapDataWord(int);
long long SwapDataDoubleWord(long long);

// thunks
float FloorThunk(double);
float CeilThunk(double);

#endif

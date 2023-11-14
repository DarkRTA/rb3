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
float Clamp(float, float, float);
int Clamp(int, int, int);
int Modulo(int, int);
float Modulo(float, float);
float FMod(float, float);
float GetSqrtAsFloat(double);
double Sqrt(double);
float Interp(float, float, float);
float InverseLerp(float, float, float);
float DegreesToRadians(float);
float RadiansToDegrees(float);
bool IsNan(float);
int CountBits(int);

// functions to swap endians of data
void SwapData(const void*, void*, int);
unsigned short SwapDataHalfWord(unsigned short);
unsigned int SwapDataWord(int);
long long SwapDataDoubleWord(long long);

// thunks
float FloorThunk(double);
float CeilThunk(double);
float AbsThunk(double);
float PowThunk(double, double);
float ATanThunk(double);
float PowFloat(double, double);
float SinThunk(double);
float CosThunk(double);
float TanThunk(double);
float TanFloat(double);
float ASinThunk(double);
float ASinFloat(double);
float ACosThunk(double);
float ACosFloat(double);

#endif

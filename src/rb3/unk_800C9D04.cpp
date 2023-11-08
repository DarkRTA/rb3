#include "jsonobject.hpp"
#include "common.hpp"
#include "data.hpp"
#include "std/math.h"

// fn_800CF370
int Minimum(int x, int y)
{
	return (y < x) ? y : x;
}

// fn_800D7964
float DataArray::GetFloatAtIndex(int i) const {
	DataNode* dn = GetNodeAtIndex(i);
    return dn->Float(this);
}

// fn_800D81AC

extern "C" float fn_800D81B0(double d);
extern "C" double fn_800D81D4(double d);
// fn_800D81B0
float fn_800D81B0(double d){
	return fn_800D81D4(d);
}

// fn_800D81D4
double fn_800D81D4(double d){
	return fabs(d);
}
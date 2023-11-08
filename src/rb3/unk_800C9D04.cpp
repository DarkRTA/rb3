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

// fn_800D81D4
double FAbs(double d){
	return __fabs(d);
}

#pragma dont_inline on
// fn_800D81B0
float FAbsFloat(double d){
	return FAbs(d);
}

// fn_800D81AC
float AbsThunk(double d){
	return FAbsFloat(d);
}

#pragma dont_inline reset
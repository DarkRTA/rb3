#include "jsonobject.hpp"
#include "common.hpp"
#include "data.hpp"
#include "std/math.h"
#include "vector3.hpp"

// fn_800CF370
int Minimum(int x, int y)
{
	return (y < x) ? y : x;
}

// fn_800D7964
float DataArray::GetFloatAtIndex(int i) const
{
	DataNode *dn = GetNodeAtIndex(i);
	return dn->Float(this);
}

// fn_800D81D4
double FAbs(double d)
{
	return __fabs(d);
}

#pragma dont_inline on
// fn_800D81B0
float FAbsFloat(double d)
{
	return FAbs(d);
}

// fn_800D81AC
float AbsThunk(double d)
{
	return FAbsFloat(d);
}

#pragma dont_inline reset

// fn_800D4728
int Clamp(int i1, int i2, int i3){
	if(i3 > i2) return i2;
    if(!(i3 < i1)) return i3;
    return i1;
}

// fn_800CB1A4
Vector3::Vector3(float f1, float f2, float f3){
	x = f1;
	y = f2;
	z = f3;
}
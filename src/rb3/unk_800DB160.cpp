#include "data.hpp"
#include "common.hpp"
#include "std/math.h"

// fn_800E25EC
float Ceil(double d)
{
	return ceil(d);
}

#pragma dont_inline on
// fn_800E25E8
float CeilThunk(double d)
{
	return Ceil(d);
}
#pragma dont_inline reset

// fn_800DC764
float Floor(double d)
{
	return floor(d);
}

#pragma dont_inline on
// fn_800DC760
float FloorThunk(double d)
{
	return Floor(d);
}
#pragma dont_inline reset

// fn_800DC1B0
int Round(float f)
{
	if (f > (float)0.0) {
		return (int)((float)0.5 + f);
	} else {
		return (int)(f - (float)0.5);
	}
}
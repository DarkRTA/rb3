#include "common.hpp"
#include "std/math.h"

// fn_8015506C
float PowFloat(double d1, double d2)
{
	return pow(d1, d2);
}

// fn_801301D0
float CosFloat(double d){
	return cos(d);
}

#pragma dont_inline on
// fn_801301CC
float CosThunk(double d){
	return CosFloat(d);
}
#pragma dont_inline reset
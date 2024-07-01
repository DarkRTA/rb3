// Seems they forgot the include, these are stored in .sdata here
// but elsewhere they're are read as if they're in .data
// #include "MSL_Common/float.h"

int __float_nan = 0x7FFFFFFF;
float __float_huge = 0x1.0P128F;
double __double_huge = 0x1.0P1024;

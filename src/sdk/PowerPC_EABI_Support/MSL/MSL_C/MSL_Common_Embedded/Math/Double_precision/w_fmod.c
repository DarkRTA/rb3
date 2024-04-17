#include "sdk/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
double fmod(double x, double y) { return __ieee754_fmod(x,y); }

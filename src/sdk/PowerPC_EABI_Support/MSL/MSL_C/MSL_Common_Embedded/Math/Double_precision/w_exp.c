#include "sdk/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
double exp(double x) { return __ieee754_exp(x); }

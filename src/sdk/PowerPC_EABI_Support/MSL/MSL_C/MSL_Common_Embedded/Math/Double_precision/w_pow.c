#include "sdk/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
double pow(double m, double e) { return __ieee754_pow(m, e); }

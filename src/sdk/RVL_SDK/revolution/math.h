#ifndef _REVOSDK_MATH_H
#define _REVOSDK_MATH_H

#include "types.h"
#include "MSL_C/math.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#define FABS(x) (float)__fabs(x)
#define SQUARE(v) ((v) * (v))

#define TAU     6.2831855f
#define PI      3.1415927f
#define HALF_PI 1.5707964f

#define LONG_TAU 6.2831854820251465

#ifndef M_PI
#define M_PI ((float)3.14159274101257324219)
#endif

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif

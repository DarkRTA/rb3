#ifndef _MATH_H
#define _MATH_H

#include "MSL_Common/math_api.h"
#include "MSL_Common/float.h"
#include "MSL_Common_Embedded/Math/Double_precision/fdlibm.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __MWERKS__
/* Get clangd to shut up about __fabs being undefined. */
#define __fabs(x) (x)
#define __frsqrte(x) (x)
#endif

/*
#define HUGE_VALF
#define HUGE_VALL
*/

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

int __signbitf(float);
int __fpclassifyf(float);
int __signbitd(double);
int __fpclassifyd(double);

/* clang-format off */
#define fpclassify(x) ((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)))
#define signbit(x) ((sizeof(x) == sizeof(float)) ? __signbitf((float)(x)) : __signbitd((double)(x)))
/* clang-format on */

#define isfinite(x) ((fpclassify(x) > FP_INFINITE))
/* #define isinf(x) */
#define isnan(x) (fpclassify(x) == FP_NAN)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)

/*
#define isgreater(x, y)
#define isgreaterequal(x, y)
#define isless(x, y)
#define islessequal(x, y)
#define islessgreater(x, y)
#define isunordered(x, y)
*/

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)

/*
#define FP_FAST_FMA
#define FP_FAST_FMAF
#define FP_FAST_FMAL
#define FP_ILOGB0
#define FP_ILOGBNAN
*/

double nan(const char *str);

inline long double fabsl(long double x) {
    return __fabs((double)x);
}

#ifdef __cplusplus
}
#endif

#endif

#ifndef _MATH_H
#define _MATH_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "MSL_Common/math_api.h"

extern int __float_nan[];
extern int __float_huge[];
extern int __double_huge[];

#define INFINITY (*(float *)__float_huge)
#define NAN (*(float *)__float_nan)
#define HUGE_VAL (*(double *)__double_huge)
// #define HUGE_VALF
// #define HUGE_VALL

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

int __signbitf(float);
int __fpclassifyf(float);
int __signbitd(double);
int __fpclassifyd(double);

// clang-format off
#define fpclassify(x) ((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)))
#define signbit(x) ((sizeof(x) == sizeof(float)) ? __signbitf((float)(x)) : __signbitd((double)(x)))
// clang-format on

#define isfinite(x) ((fpclassify(x) > FP_INFINITE))
// #define isinf(x)
#define isnan(x) (fpclassify(x) == FP_NAN)
#define isnormal(x) (fpclassify(x) == FP_NORMAL)
// #define isgreater(x, y)
// #define isgreaterequal(x, y)
// #define isless(x, y)
// #define islessequal(x, y)
// #define islessgreater(x, y)
// #define isunordered(x, y)

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2
// #define math_errhandling

// #define FP_FAST_FMA
// #define FP_FAST_FMAF
// #define FP_FAST_FMAL
// #define FP_ILOGB0
// #define FP_ILOGBNAN

#define _DECL_MATH(name)                                                                 \
    float name##f(float x);                                                              \
    double name(double x);                                                               \
    long double name##l(long double x)

#define _DECL_MATHC(name, arg)                                                           \
    float name##f(arg);                                                                  \
    double name(arg);                                                                    \
    long double name##l(arg)

#define _DECL_MATHR(name, ret)                                                           \
    ret name##f(float x);                                                                \
    ret name(double x);                                                                  \
    ret name##l(long double x)

#define _DECL_MATH2(name)                                                                \
    float name##f(float x, float y);                                                     \
    double name(double x, double y);                                                     \
    long double name##l(long double x, long double y)

#define _DECL_MATH2C(name, arg2)                                                         \
    float name##f(float x, arg2);                                                        \
    double name(double x, arg2);                                                         \
    long double name##l(long double x, arg2)

#define _DECL_MATH3(name)                                                                \
    float name##f(float x, float y, float z);                                            \
    double name(double x, double y, double z);                                           \
    long double name##l(long double x, long double y, long double z)

#define _DECL_MATH3C(name, arg3)                                                         \
    float name##f(float x, float y, arg3);                                               \
    double name(double x, double y, arg3);                                               \
    long double name##l(long double x, long double y, arg3)

_DECL_MATH(fabs);
_DECL_MATH2(fmod);
_DECL_MATH2(remainder);
_DECL_MATH3C(remquo, int *quo);
_DECL_MATH3(fma);
_DECL_MATH2(fmax);
_DECL_MATH2(fmin);
_DECL_MATH2(fdim);

_DECL_MATHC(nan, const char *str);

_DECL_MATH(exp);
_DECL_MATH(exp2);
_DECL_MATH(expm1);
_DECL_MATH(log);
_DECL_MATH(log10);
_DECL_MATH(log2);
_DECL_MATH(log1p);

_DECL_MATH2(pow);
_DECL_MATH(sqrt);
_DECL_MATH(cbrt);
_DECL_MATH2(hypot);

_DECL_MATH(sin);
_DECL_MATH(cos);
_DECL_MATH(tan);
_DECL_MATH(asin);
_DECL_MATH(acos);
_DECL_MATH(atan);
_DECL_MATH2(atan2);

_DECL_MATH(sinh);
_DECL_MATH(cosh);
_DECL_MATH(tanh);
_DECL_MATH(asinh);
_DECL_MATH(acosh);
_DECL_MATH(atanh);

_DECL_MATH(erf);
_DECL_MATH(erfc);
_DECL_MATH(tgamma);
_DECL_MATH(lgamma);

_DECL_MATH(ceil);
_DECL_MATH(floor);
_DECL_MATH(trunc);
_DECL_MATH(round);
_DECL_MATHR(lround, long);
_DECL_MATHR(llround, long long);

_DECL_MATH(nearbyint);
_DECL_MATH(rint);
_DECL_MATHR(lrint, long);
_DECL_MATHR(llrint, long long);

_DECL_MATH2C(frexp, int *exp);
_DECL_MATH2C(ldexp, int exp);

float modff(float arg, float *iptr);
double modf(double arg, double *iptr);
long double modfl(long double arg, long double *iptr);

_DECL_MATH2C(scalbn, int exp);
_DECL_MATH2C(scalbln, long exp);
_DECL_MATHR(ilogb, int);
_DECL_MATH(logb);

_DECL_MATH2(nextafter);
_DECL_MATH2C(nexttoward, long double to);

_DECL_MATH2(copysign);

#undef _DECL_MATH
#undef _DECL_MATHC
#undef _DECL_MATHR
#undef _DECL_MATH2
#undef _DECL_MATH2C
#undef _DECL_MATH3
#undef _DECL_MATH3C

inline long double fabsl(long double x) {
    return __fabs((double)x);
}

double __ieee754_acos(double);
double __ieee754_fmod(double, double);
double __ieee754_log(double);
double __ieee754_log10(double);
double __ieee754_pow(double, double);
double __ieee754_sqrt(double);
double __ieee754_atan2(double, double);
double __ieee754_asin(double);

int __ieee754_rem_pio2(double, double *);

double __kernel_sin(double, double, int);
double __kernel_cos(double, double);
double __kernel_tan(double, double, int);

#ifdef __cplusplus
}
#endif

#endif

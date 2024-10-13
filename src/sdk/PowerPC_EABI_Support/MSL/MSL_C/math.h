#ifndef _MATH_H
#define _MATH_H

#include "MSL_Common/math_api.h" /* IWYU pragma: export */
#include "MSL_Common/float.h" /* IWYU pragma: export */
#include "MSL_Common_Embedded/Math/Double_precision/fdlibm.h" /* IWYU pragma: export */

#ifdef __cplusplus
extern "C" {
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

#define _DECL_MATH(name)                                                                 \
    double name(double x);                                                               \
    inline float name##f(float x) { return name(x); }                                    \
    inline long double name##l(long double x) { return name(x); }

#define _DECL_MATHC(name, argtype, arg)                                                  \
    double name(argtype arg);                                                            \
    inline float name##f(argtype arg) { return name(arg); }                              \
    inline long double name##l(argtype arg) { return name(arg); }

#define _DECL_MATHR(name, ret)                                                           \
    ret name(double x);                                                                  \
    inline ret name##f(float x) { return name(x); }                                      \
    inline ret name##l(long double x) { return name(x); }

#define _DECL_MATH2(name)                                                                \
    double name(double x, double y);                                                     \
    inline float name##f(float x, float y) { return name(x, y); }                        \
    inline long double name##l(long double x, long double y) { return name(x, y); }

#define _DECL_MATH2C(name, arg2type, arg2)                                               \
    double name(double x, arg2type arg2);                                                \
    inline float name##f(float x, arg2type arg2) { return name(x, arg2); }               \
    inline long double name##l(long double x, arg2type arg2) { return name(x, arg2); }

#define _DECL_MATH2P(name, arg2name)                                                     \
    double name(double x, double *arg2name);                                             \
    float name##f(float x, float *arg2name);                                             \
    long double name##l(long double x, long double *arg2name);

#define _DECL_MATH3(name)                                                                \
    double name(double x, double y, double z);                                           \
    inline float name##f(float x, float y, float z) { return name(x, y, z); }            \
    inline long double name##l(long double x, long double y, long double z) {            \
        return name(x, y, z);                                                            \
    }

#define _DECL_MATH3C(name, arg3type, arg3)                                               \
    double name(double x, double y, arg3type arg3);                                      \
    inline float name##f(float x, float y, arg3type arg3) { return name(x, y, arg3); }   \
    inline long double name##l(long double x, long double y, arg3type arg3) {            \
        return name(x, y, arg3);                                                         \
    }

_DECL_MATH(fabs);
_DECL_MATH2(fmod);
_DECL_MATH2(remainder);
_DECL_MATH3C(remquo, int *, quo);
_DECL_MATH3(fma);
_DECL_MATH2(fmax);
_DECL_MATH2(fmin);
_DECL_MATH2(fdim);

_DECL_MATHC(nan, const char *, str);

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

_DECL_MATH2C(frexp, int *, exp);
_DECL_MATH2C(ldexp, int, exp);

_DECL_MATH2P(modf, iptr);

_DECL_MATH2C(scalbn, int, exp);
_DECL_MATH2C(scalbln, long, exp);
_DECL_MATHR(ilogb, int);
_DECL_MATH(logb);

_DECL_MATH2(nextafter);
_DECL_MATH2C(nexttoward, long double, to);

_DECL_MATH2(copysign);

#undef _DECL_MATH
#undef _DECL_MATHC
#undef _DECL_MATHR
#undef _DECL_MATH2
#undef _DECL_MATH2C
#undef _DECL_MATH2P
#undef _DECL_MATH3
#undef _DECL_MATH3C

#ifdef __cplusplus
}
#endif

#endif

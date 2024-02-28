#ifndef MATH_MATHFUNCS_H
#define MATH_MATHFUNCS_H
#include <math.h>

extern "C" float asin_f(double);
extern "C" float acos_f(double);
extern "C" float atan_f(double);
extern "C" float fabs_f(double);
extern "C" float pow_f(double, double);
extern "C" float sin_f(double);
extern "C" float cos_f(double);
extern "C" float tan_f(double);
extern "C" float log10_f(double);

inline float asin_f(double d){
    return asin(d);
}

inline float acos_f(double d){
    return acos(d);
}

inline float atan_f(double d){
    return atan(d);
}

inline float fabs_f(double d){
    return __fabs(d);
}

inline float pow_f(double x, double y){
    return pow(x, y);
}

inline float sin_f(double d){
    return sin(d);
}

inline float cos_f(double d){
    return cos(d);
}

inline float tan_f(double d){
    return tan(d);
}

inline float log10_f(double d){
    return log10(d);
}

#endif

#ifndef MATH_MATHF_H
#define MATH_MATHF_H
#include <math.h>

extern "C" float atan_f(double);
extern "C" float fabs_f(double);
extern "C" float pow_f(double, double);
extern "C" float sin_f(double);

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

#endif

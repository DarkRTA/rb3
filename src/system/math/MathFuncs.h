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
extern "C" float sqrt_f(double);
extern "C" float floor_f(double);
extern "C" float ceil_f(double);
extern "C" float fmod_f(double,double);

inline int CountBits(int num) {
    int temp_r0;
    int var_r3;
    int var_r4;

    var_r3 = num;
    var_r4 = 0;
    while (var_r3 != 0) {
        temp_r0 = var_r3 & 1;
        var_r3 = (int)((unsigned int)var_r3 >> 1U);
        var_r4 += temp_r0;
    }
    return var_r4;
}

inline int Round(float f) {
    if (f > (float)0.0) {
        return (int)((float)0.5 + f);
    } else {
        return (int)(f - (float)0.5);
    }
}

template<class T> inline T Minimum(T x, T y){
    return (y < x) ? y : x;
}

template<class T> inline T Max(T x, T y){
    return (x < y) ? y : x;
}

template<class T> inline T Minimum(T x, T y, T z){
    return Minimum(x, Minimum(y, z));
}

template<class T> inline T Max(T x, T y, T z){
    return Max(x, Max(y, z));
}

template<class T> inline T Clamp(T x, T y, T z){
    if(z > y) return y;
    if(!(z < x)) return z;
    return x;
}

template<class T> inline bool ClampEq(T& x, const T& y, const T& z) {
    T temp = y;
    if (x < y) {
        x = temp;
        return true;
    } else if (x > z) {
        x = z;
        return true;
    }
    return false;
}

template<class T> inline const T Abs(T x){
    if(x > 0) return x;
    else return -x;
}

inline bool IsNaN(float){

}

inline int Mod(int num, int modbase){
    if(modbase == 0) return 0;
    int div = num % modbase;
    if(div < 0) return div + modbase;
    else return div;
}

inline float sqrt_f(double d){
    return sqrt(d);
}

inline float asin_f(double d){
    return asin(d);
}

inline float acos_f(double d){
    return acos(d);
}

inline float atan_f(double d){
    return atan(d);
}

// inline float my_fabsf(float x){
//     return fabsf(x);
// }

// inline float fabsf(float x) {
//     return (float)fabs((double)x);
// }

// extern inline double fabs(double x) {
//     return __fabs(x);
// }

inline float fabs_f(double d){
    return __fabs(d);
}

inline float pow_f(double x, double y){
    return pow(x, y);
}

inline double pow_d(double x, double y){
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

inline float floor_f(double d){
    return floor(d);
}

inline float ceil_f(double d){
    return ceil(d);
}

inline float Modulo(float f1, float f2) {
    if (f2 == 0.0f)
        return 0.0f;
    float tmp = fmod_f(f1, f2);
    if (tmp < 0.0f)
        tmp += f2;
    return tmp;
}

inline float ModRange(float f1, float f2, float f3){
    return Modulo(f3 - f1, f2 - f1) + f1;
}

inline float fmod_f(double x, double y){
    return fmod(x, y);
}

inline float Interp(float a, float b, float c){
    float delta = b - a;
    return c * delta + a;
}

inline void Interp(float f1, float f2, float f3, float& fres){
    fres = f3 * (f2 - f1) + f1;
}

#endif

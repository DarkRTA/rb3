#ifndef MATH_MATHFUNCS_H
#define MATH_MATHFUNCS_H
#include <math.h>
#include <cmath>

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

template<class T> inline T Min(T x, T y){
    return (y < x) ? y : x;
}

template<class T> inline T Max(T x, T y){
    return (x < y) ? y : x;
}

template<class T> inline T Min(T x, T y, T z){
    return Min(x, Min(y, z));
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

template<class T> inline bool MinEq(T& x, const T& y){
    if(y < x){
        x = y;
        return true;
    }
    return false;
}

template<class T> inline bool MaxEq(T& x, const T& y){
    T temp = y;
    if(x < y){
        x = temp;
        return true;
    }
    return false;
}

template<class T> inline const T Abs(T x){
    if(x > 0) return x;
    else return -x;
}

inline bool IsNaN(float f) {
    return (f == f) ? false : true;
}

inline int Mod(int num, int modbase){
    if(modbase == 0) return 0;
    int div = num % modbase;
    if(div < 0) return div + modbase;
    else return div;
}

inline bool IsFloatZero(float f){
    return std::abs(f) < 0.0001f;
}

inline bool IsFloatOne(float f){
    return std::abs(f - 1.0f) < 0.000099999997f;
}

inline float Modulo(float f1, float f2) {
    if (f2 == 0.0f)
        return 0.0f;
    float tmp = std::fmod(f1, f2);
    if (tmp < 0.0f)
        tmp += f2;
    return tmp;
}

inline float ModRange(float f1, float f2, float f3){
    return Modulo(f3 - f1, f2 - f1) + f1;
}


inline float Interp(float a, float b, float c){
    float delta = b - a;
    return c * delta + a;
}

inline void Interp(float f1, float f2, float f3, float& fres){
    fres = f3 * (f2 - f1) + f1;
}

inline void Interp(bool b1, bool b2, float f, bool& bres){
    bres = f < 1.0f ? b1 : b2;
}

inline bool PowerOf2(int num){
    if(num < 0) return false;
    else if(num == 0) return true;
    else return (num & num - 1) == 0;
}

#endif

#pragma once
#include <math.h>
#include <cmath>

#define kHugeFloat 1.0e30f

inline float ScaleUShortToFloat01(unsigned short u) { return u / 65535.0f; }

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

inline int HighestBit(int num) {
    if (num == 0) {
        return 0;
    } else {
        int bit = 0x80000000;
        while (!(bit & num)) {
            bit >>= 1;
        }
        return bit;
    }
}

inline int LowestBit(int num) {
    if (num == 0) {
        return 0;
    } else {
        int bit = 1;
        while (!(bit & num)) {
            bit <<= 1;
        }
        return bit;
    }
}

inline int Round(float f) {
    if (f > (float)0.0) {
        return (int)((float)0.5 + f);
    } else {
        return (int)(f - (float)0.5);
    }
}

template <class T>
inline T Min(T x, T y) {
    return (y < x) ? y : x;
}

template <class T>
inline T Max(T x, T y) {
    return (x < y) ? y : x;
}

template <class T>
inline T Min(T x, T y, T z) {
    return Min(x, Min(y, z));
}

template <class T>
inline T Max(T x, T y, T z) {
    return Max(x, Max(y, z));
}

template <class T>
inline T Clamp(T min, T max, T value) {
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

template <class T>
inline bool ClampEq(T &value, const T &min, const T &max) {
    T temp = min;
    if (value < min) {
        value = temp;
        return true;
    } else if (value > max) {
        value = max;
        return true;
    }
    return false;
}

template <class T>
inline bool MinEq(T &x, const T &y) {
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

template <class T>
inline bool MaxEq(T &x, const T &y) {
    T temp = y;
    if (x < y) {
        x = temp;
        return true;
    }
    return false;
}

template <class T>
inline const T Abs(T x) {
    if (x > 0)
        return x;
    else
        return -x;
}

inline bool IsNaN(float f) { return (f == f) ? false : true; }

inline int Mod(int num, int modbase) {
    if (modbase == 0)
        return 0;
    int div = num % modbase;
    if (div < 0)
        return div + modbase;
    else
        return div;
}

inline bool IsFloatZero(float f) { return std::abs(f) < 0.0001f; }

inline bool IsFloatOne(float f) { return std::abs(f - 1.0f) < 0.000099999997f; }

inline bool IsFabsZero(float f) { return std::fabs(f) < 0.000099999997f ? true : false; }

inline bool ApproxEq(float f1, float f2) {
    return std::fabs(f1 - f2) < 0.000099999997f ? true : false;
}

inline float Modulo(float f1, float f2) {
    if (f2 == 0.0f)
        return 0.0f;
    float tmp = std::fmod(f1, f2);
    if (tmp < 0.0f)
        tmp += f2;
    return tmp;
}

inline float ModRange(float f1, float f2, float f3) {
    return Modulo(f3 - f1, f2 - f1) + f1;
}

inline float Interp(float a, float b, float t) { return t * (b - a) + a; }

inline void Interp(float a, float b, float t, float &fres) { fres = t * (b - a) + a; }

inline void Interp(bool a, bool b, float t, bool &bres) { bres = t < 1.0f ? a : b; }

inline float InterpAng(float, float, float) {}

inline float InverseLerp(float min, float max, float value) {
    // Prevent divide-by-zero from zero-sized range
    if (max != min) {
        return (value - min) / (max - min);
    } else {
        return 1.0f;
    }
}

inline bool PowerOf2(int num) {
    if (num < 0)
        return false;
    else if (num == 0)
        return true;
    else
        return (num & num - 1) == 0;
}

inline float Limit(float f1, float f2, float f3, int &i) {
    float fsub = f2 - f1;
    int floored = floor((f3 - f1) / fsub);
    i = floored;
    return -(floored * fsub - f3);
}

inline float Sigmoid(float t) {
    // MILO_ASSERT(t >= 0 && t <= 1, 0x1DB); FIXME: uncommenting this line results in a
    // ton of circular dependencies surrounding Color.h and here, Utl.h
    float tsq = t * t;
    return Clamp<float>(0, 1, tsq * 3.0f - tsq * 2.0f * t);
}
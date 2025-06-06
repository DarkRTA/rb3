#ifndef MATH_VEC_H
#define MATH_VEC_H
#include "os/Debug.h"
#include "math/Trig.h"
#include "utl/BinStream.h"
#include "utl/TextStream.h"

class Vector2 {
public:
    Vector2() {}
    Vector2(float xx, float yy) : x(xx), y(yy) {}
    Vector2(const Vector2 &vec) : x(vec.x), y(vec.y) {}

    void Set(float xx, float yy) {
        x = xx;
        y = yy;
    }

    // Vector2& operator*=(float f) {
    //     x *= f; y *= f;
    //     return *this;
    // }
    // there's no way this returns a float what
    // according to RndCam::WorldToScreen it does
    float operator*=(float f) {
        x *= f;
        y *= f;
        return f;
    }

    void Zero() { x = y = 0.0f; }

    Vector2 &operator/=(float f) {
        x /= f;
        y /= f;
        return *this;
    }

    Vector2 &operator+=(const Vector2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    bool operator==(const Vector2 &v) const { return x == v.x && y == v.y; }

    bool operator!() const { return x == 0.0f && y == 0.0f; }

    float x;
    float y;
};

inline BinStream &operator<<(BinStream &bs, const Vector2 &vec) {
    bs << vec.x << vec.y;
    return bs;
}

inline BinStream &operator>>(BinStream &bs, Vector2 &vec) {
    bs >> vec.x >> vec.y;
    return bs;
}

class Vector3 {
public:
    static Vector3 sX;
    static Vector3 sY;
    static Vector3 sZ;
    static Vector3 sZero;

    float x;
    float y;
    float z;

    Vector3() {}
    Vector3(float f1, float f2, float f3) : x(f1), y(f2), z(f3) {}
    // Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    // used during decompression of CharBones vectors
    Vector3(short* s){
        x = s[0] * 0.000030518509f * 1300.0f;
        y = s[1] * 0.000030518509f * 1300.0f;
        z = s[2] * 0.000030518509f * 1300.0f;
    }

    void Set(float f1, float f2, float f3) {
        x = f1;
        y = f2;
        z = f3;
    }
    void Zero() { x = y = z = 0.0f; }

    float X() const { return x; }
    float Y() const { return y; }
    float Z() const { return z; }

    Vector3 &operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3 &operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3 &operator*=(const Vector3 &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3 &operator/=(float f) {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    const float &operator[](int i) const { return *(&x + i); }
    float &operator[](int i) { return *(&x + i); }
    bool operator==(const Vector3 &v) const { return x == v.x && y == v.y && z == v.z; }
    bool IsZero() const { return x == 0 && y == 0 && z == 0; }
    bool operator!=(const Vector3 &v) const { return x != v.x || y != v.y || z != v.z; }
};

inline BinStream &operator<<(BinStream &bs, const Vector3 &vec) {
    bs << vec.x << vec.y << vec.z;
    return bs;
}

inline BinStream &operator>>(BinStream &bs, Vector3 &vec) {
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}

TextStream &operator<<(TextStream &, const Vector3 &);

class Vector4 {
public:
    static Vector4 sX;
    static Vector4 sY;
    static Vector4 sZ;
    static Vector4 sW;
    static Vector4 sZero;
    float x;
    float y;
    float z;
    float w;

    Vector4() {}
    Vector4(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}
    void Set(float f1, float f2, float f3, float f4) {
        x = f1;
        y = f2;
        z = f3;
        w = f4;
    }

    // Vector4(const Vector4 &);
};

inline BinStream &operator>>(BinStream &bs, Vector4 &vec) {
    bs >> vec.x >> vec.y >> vec.z >> vec.w;
    return bs;
}

class Vector4_16_01 {
public:
    Vector4_16_01() {}
    Vector4_16_01(float f0, float f1, float f2, float f3) {
        SetX(f0);
        SetY(f1);
        SetZ(f2);
        SetW(f3);
    }

    float GetX() const { return ScaleUShortToFloat01(x); }
    float GetY() const { return ScaleUShortToFloat01(y); }
    float GetZ() const { return ScaleUShortToFloat01(z); }
    float GetW() const { return ScaleUShortToFloat01(w); }

    void SetX(float f) { x = ScaleFloat01ToUShort(f); }
    void SetY(float f) { y = ScaleFloat01ToUShort(f); }
    void SetZ(float f) { z = ScaleFloat01ToUShort(f); }
    void SetW(float f) { w = ScaleFloat01ToUShort(f); }

    u16 ScaleFloat01ToUShort(float f) {
        MILO_ASSERT(f >= 0.0f, 543);
        MILO_ASSERT(f <= 1.0f, 544);

        f32 size_u16 = 65535.f;
        return f * size_u16;
    }
    void Set(float f0, float f1, float f2, float f3) {
        SetX(f0);
        SetY(f1);
        SetZ(f2);
        SetW(f3);
    }

    float FloatAt(int idx) const { return ScaleUShortToFloat01(((u16 *)&x)[idx]); }
    const u16 operator[](int i) const { return ((u16 *)&x)[i]; }

    u16 x, y, z, w;
};

void Scale(const Vector3 &, const Vector3 &, Vector3 &);

inline void Scale(const Vector3 &v1, float f, Vector3 &dst) {
    dst.Set(v1.x * f, v1.y * f, v1.z * f);
}

inline float Average(const Vector2 &v) { return (v.x + v.y) / 2; }

inline float Distance(const Vector3 &v1, const Vector3 &v2) {
    register const Vector3 *_v1 = &v1;
    register const Vector3 *_v2 = &v2;

    register __vec2x32float__ paired1, paired2;
    register __vec2x32float__ single1, single2;

    register float yz_sub;
    register float x_sub;

    register float total;
    register float inv;
    register float inv_half;
    register float inv_sq;

    register float half = 0.5;
    register float zero;

    // clang-format off
    asm {
        // load x (also loads y, but we can ignore that)
        psq_l single1, Vector3.x(_v1), 0, 0
        psq_l single2, Vector3.x(_v2), 0, 0

        // load y and z into half register
        psq_l paired1, Vector3.y(_v1), 0, 0
        psq_l paired2, Vector3.y(_v2), 0, 0

        // (x1 - x2), (y1 - y2 (ignored))
        ps_sub x_sub, single1, single2

            // (y1 - y2), (z1 - z2)
        ps_sub yz_sub, paired1, paired2

            // update register to hold (y1 - y2)^2, (z1 - z2)^2
        ps_mul yz_sub, yz_sub, yz_sub

            // (x^2 + y^2), (x^2 + y^2 (ignored))
        ps_madd total, x_sub, x_sub, yz_sub

            // (x^2 + y^2 + z^2), (z^2 (ignored))
        ps_sum0 total, total, yz_sub, yz_sub

            // i guess make 0 out of a constant we already have loaded?
        fsubs zero, half, half
            // compare unordered, no negatives; if zero, return 0
        fcmpu zero, total
        beq _done
    }

    register float three = 3;

    asm {
        // get 1/distance
        frsqrte inv, total

            // square the inverse, so 1/distance^2
        fmuls inv_sq, inv, inv

            // turn half into 1/2d
        fmuls inv_half, inv, half

            // multiply the distance^2 by 1/d^2, and then multiply by 3?
            // my best guess is this would return 3?
        fnmsubs inv_sq, inv_sq, total, three

            // beyond this point, I'm not really sure what we're doing,
            // as a best guess, it would be a newton iteration?

        fmuls inv, inv_sq, inv_half

        fmuls total, total, inv

        _done:
    }
    // clang-format on

    return total;
}

inline void Subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
    dst.Set(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline float Length(const Vector3 &v1) {
    typedef __vec2x32float__ psq;
    register const Vector3 *_v1 = &v1;

    register psq paired1;
    register float single1;

    register float total;
    register float inv;
    register float inv_half;
    register float inv_sq;

    register float zero;
    register float three;
    register float half = 0.5;

    asm { // load y and z into half register
        psq_l paired1, Vector3.x(_v1), 0, 0
        lfs single1, Vector3.z(_v1)

          // (y1 - y2), (z1 - z2)
          // ps_sub yz_sub, paired1, paired2

          // update register to hold (y1 - y2)^2, (z1 - z2)^2
        ps_mul paired1, paired1, paired1
              // load x (also loads y, but we can ignore that)
              // psq_l single1, Vector3.x(_v1), 0, 0

              // (x1 - x2), (y1 - y2 (ignored))
              // ps_sub x_sub, single1, single2

              // (x^2 + y^2), (x^2 + y^2 (ignored))
        ps_madd total, single1, single1, paired1

              // (x^2 + y^2 + z^2), (z^2 (ignored))
        ps_sum0 total, total, paired1, paired1

              // i guess make 0 out of a constant we already have loaded?
        fsubs zero, half, half
              // compare unordered, no negatives; if zero, return 0
        fcmpu total, zero
        beq _done
    }

    three = 3;

    asm {
        // get 1/distance
        frsqrte inv, total

            // square the inverse, so 1/distance^2
        fmuls inv_sq, inv, inv

            // turn half into 1/2d
        fmuls inv_half, inv, half

            // multiply the distance^2 by 1/d^2, and then multiply by 3?
            // my best guess is this would return 3?
        fnmsubs inv_sq, inv_sq, total, three

            // beyond this point, I'm not really sure what we're doing,
            // as a best guess, it would be a newton iteration?

        fmuls inv, inv_sq, inv_half

        fmuls total, total, inv

        _done:
    }

    return total;
}

inline float LengthSquared(const Vector2 &v) {
    float x = v.x;
    float y = v.y;
    return x * x + y * y;
}

inline float Dot(const Vector3 &v1, const Vector3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Cross(const Vector2 &v1, const Vector2 &v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

inline float LengthSquared(const Vector3 &v) {
    float x = v.x;
    float y = v.y;
    float z = v.z;
    return x * x + y * y + z * z;
}

// https://decomp.me/scratch/TWZ2T
// why oh why does debug behave this way
inline float DistanceSquared(const Vector3 &v1, const Vector3 &v2) {
#ifdef MILO_DEBUG
    float zdiff = v1.z - v2.z;
    float ydiff = v1.y - v2.y;
    float xdiff = v1.x - v2.x;
    return xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;
#else
    Vector3 res;
    Subtract(v1, v2, res);
    return Dot(res, res);
#endif
}

float RecipSqrtAccurate(float);

inline void Add(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
    dst.Set(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline void Interp(const Vector2 &v1, const Vector2 &v2, float f, Vector2 &res) {
    res.Set(Interp(v1.x, v2.x, f), Interp(v1.y, v2.y, f));
}

inline void Interp(const Vector3 &v1, const Vector3 &v2, float f, Vector3 &dst) {
    if (f == 0.0f) {
        dst = v1;
    } else if (f == 1.0f) {
        dst = v2;
    } else {
        dst.Set(Interp(v1.x, v2.x, f), Interp(v1.y, v2.y, f), Interp(v1.z, v2.z, f));
    }
}

inline void ScaleAdd(const Vector3 &v1, const Vector3 &v2, float f, Vector3 &vres) {
    vres.x = v2.x * f + v1.x;
    vres.y = v2.y * f + v1.y;
    vres.z = v2.z * f + v1.z;
}

inline void ScaleAddEq(Vector3 &v1, const Vector3 &v2, float f) {
    v1.x += v2.x * f;
    v1.y += v2.y * f;
    v1.z += v2.z * f;
}

inline void Cross(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
    float x1, x2, y2, z1, z2, y1;

    x2 = v2.x;
    y1 = v1.y;
    y2 = v2.y;
    z1 = v1.z;
    x1 = v1.x;
    z2 = v2.z;

    dst.Set(y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2);
}

inline void Normalize(register const Vector3 &v, register Vector3 &vout) {
    if (v.x != 0 || v.y != 0 || v.z != 0) {
        register float half = 0.5;
        register float three = 3;
        register __vec2x32float__ x;
        register __vec2x32float__ z;
        register __vec2x32float__ z2;
        register __vec2x32float__ x2;
        register __vec2x32float__ inv_sq;
        register __vec2x32float__ inv;
        register __vec2x32float__ inv_half;
        register __vec2x32float__ total;

        ASM_BLOCK(
            psq_l x, Vector3.x(v), 0, 0
            psq_l z, Vector3.z(v), 1, 0
            ps_mul x2, x, x
            ps_madd z2, z, z, x2
            ps_sum0 total, z2, z, x2
                // get 1/distance
            frsqrte x2, total

                // square the inverse, so 1/distance^2
            fmuls inv_sq, x2, x2

                // turn half into 1/2d
            fmuls half, x2, half

                // multiply the distance^2 by 1/d^2, and then multiply by 3?
                // my best guess is this would return 3?
            fnmsubs inv_sq, inv_sq, total, three

                // beyond this point, I'm not really sure what we're doing,
                // as a best guess, it would be a newton iteration?

            fmuls x2, inv_sq, half

            ps_muls0 x, x, x2
            ps_muls0 z, z, x2

            psq_st x, Vector3.x(vout), 0, 0
            psq_st z, Vector3.z(vout), 1, 0
        )
    } else {
        vout.Set(0, 0, 0);
    }
}

inline float operator*(const Vector3 &v1, const Vector3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline void Negate(const Vector3 &v, Vector3 &vres) { vres.Set(-v.x, -v.y, -v.z); }

inline void ScaleToMagnitude(const Vector3 &vec, float fl, Vector3 &res) {
    if (!IsFloatZero(vec.x) || !IsFloatZero(vec.y) || !IsFloatZero(vec.z)) {
        Scale(vec, fl / Length(vec), res);
    } else
        res.Set(0, 0, 0);
}

inline void RotateAboutZ(const Vector3 &v, float f, Vector3 &res) {
    float c = Cosine(f);
    float s = Sine(f);
    res.Set(v.x * c - v.y * s, v.x * s + v.y * c, v.z);
}

#endif

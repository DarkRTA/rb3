#ifndef MATH_VEC_H
#define MATH_VEC_H
#include "os/Debug.h"
#include "utl/BinStream.h"

class Vector2 {
public:
    Vector2(){}
    Vector2(float xx, float yy) : x(xx), y(yy) {}
    Vector2(const Vector2& vec) : x(vec.x), y(vec.y) {}

    void Set(float xx, float yy){ x = xx; y = yy; }

    Vector2& operator*(float f) { 
        x *= f; y *= f; 
        return *this;
    }

    Vector2& operator=(const Vector2& vec){
        x = vec.x; y = vec.y;
        return *this;
    }

    bool operator!() const {
        return x == 0.0f && y == 0.0f;
    }

    float x;
    float y;
};

inline BinStream& operator>>(BinStream& bs, Vector2& vec){
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

    Vector3(){}
    Vector3(float f1, float f2, float f3) : x(f1), y(f2), z(f3) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float f1, float f2, float f3){ x = f1; y = f2; z = f3; }
    void Zero(){ x = y = z = 0.0f; }

    float X() const { return x; }
    float Y() const { return y; }
    float Z() const { return z; }

    Vector3& operator+=(const Vector3& v){
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3& operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    const float& operator[](int i) const { return *(&x + i); }
    float& operator[](int i){ return *(&x + i); }
    // bool operator==(const Vector3 &) const;
    // bool operator!=(const Vector3 &) const;
};

inline BinStream& operator>>(BinStream& bs, Vector3& vec){
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}

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

    Vector4(){}
    Vector4(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}

    // Vector4(const Vector4 &);
};

inline BinStream& operator>>(BinStream& bs, Vector4& vec){
    bs >> vec.x >> vec.y >> vec.z >> vec.w;
    return bs;
}

class Vector4_16_01 {
    public:
    //Vector4_16_01() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    u16 x, y, z, w;
    float GetX() const { return x / 65535.0f;}
    float GetY() const { return y / 65535.0f;}
    float GetZ() const { return z / 65535.0f;}
    inline u16 ScaleFloat01ToUShort(float f) { 
        MILO_ASSERT(f >= 0.0f, 543);
        MILO_ASSERT(f <= 1.0f, 544);
        return f * 65535.0f;
    }
    void Set(float f0, float f1, float f2, float f3) {
        x = ScaleFloat01ToUShort(f0);
        y = ScaleFloat01ToUShort(f1);
        z = ScaleFloat01ToUShort(f2);
        w = ScaleFloat01ToUShort(f3);
    }
};

inline void Scale(const Vector3 &v1, float f, Vector3 &dst) {
    dst.Set(v1.x * f, v1.y * f, v1.z * f);
}

inline float Average(const Vector2& v){
    return (v.x + v.y) / 2;
}

inline float Distance(const Vector3& v1, const Vector3& v2){
    register const Vector3* _v1 = &v1;
    register const Vector3* _v2 = &v2;
    
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
    
    return total;
}

inline void Subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
#ifdef VERSION_SZBE69_B8
    dst.z = v1.z - v2.z;
    dst.y = v1.y - v2.y;
    dst.x = v1.x - v2.x;
#else
    dst.Set(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
#endif
}

float Length(const Vector3&);

inline float LengthSquared(const Vector2& v){
    float x = v.x;
    float y = v.y;
    return x * x + y * y;
}

inline float Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Cross(const Vector2& v1, const Vector2& v2){
    return v1.x * v2.y - v1.y * v2.x;
}

inline float LengthSquared(const Vector3& v){
    float x = v.x;
    float y = v.y;
    float z = v.z;
    return x * x + y * y + z * z;
}

inline float DistanceSquared(const Vector3& v1, const Vector3& v2){
#ifdef VERSION_SZBE69_B8
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

inline void Add(const Vector3& v1, const Vector3& v2, Vector3& dst){
#ifdef VERSION_SZBE69_B8
    dst.z = v1.z + v2.z;
    dst.y = v1.y + v2.y;
    dst.x = v1.x + v2.x;
#else
    dst.Set(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
#endif
}

inline void Interp(const Vector2& v1, const Vector2& v2, float f, Vector2& res){
    res.Set(Interp(v1.x,v2.x,f),Interp(v1.y,v2.y,f));
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

inline void ScaleAdd(const Vector3& v1, const Vector3& v2, float f, Vector3& vres){
    vres.x = v2.x * f + v1.x;
    vres.y = v2.y * f + v1.y;
    vres.z = v2.z * f + v1.z;
}

inline void ScaleAddEq(Vector3& v1, const Vector3& v2, float f){
    v1.x += v2.x * f;
    v1.y += v2.y * f;
    v1.z += v2.z * f;
}

inline void Cross(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
    dst.Set(
        v2.y * v1.x - v1.y * v2.x, v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z
    );
}

void Normalize(const Vector3&, Vector3&);

inline float operator*(const Vector3& v1, const Vector3& v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

#endif

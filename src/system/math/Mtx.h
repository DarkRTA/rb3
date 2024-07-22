#ifndef MATH_MTX_H
#define MATH_MTX_H
#include "math/Vec.h"
#include "obj/Data.h"
#include "utl/BinStream.h"
#include "decomp.h"

#define PSQ_MOVE(dst, src) *(__vec2x32float__*)&dst = *(__vec2x32float__*)&src

namespace Hmx {
    class Matrix3 {
    public:
        Vector3 x;
        Vector3 y;
        Vector3 z;

        // all of these are weak
        Matrix3(){}

        Matrix3(const Matrix3& mtx){
            x = mtx.x; y = mtx.y; z = mtx.z;
        }

        Matrix3(const Vector3& v1, const Vector3& v2, const Vector3& v3) : x(v1), y(v2), z(v3) {}

        Matrix3(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9) :
            x(f1, f2, f3), y(f4, f5, f6), z(f7, f8, f9) {}

        void Set(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9){
            x.Set(f1,f2,f3); y.Set(f4,f5,f6); z.Set(f7,f8,f9);
        }
        void Set(const Vector3& v1, const Vector3& v2, const Vector3& v3){
            x = v1; y = v2; z = v3;
        }
        void Identity(){
            x.Set(1.0f, 0.0f, 0.0f);
            y.Set(0.0f, 1.0f, 0.0f);
            z.Set(0.0f, 0.0f, 1.0f);
        }
        Matrix3& operator=(const Matrix3 &);
        Vector3& operator[](int);

        bool operator==(const Matrix3& mtx) const {
            return x == mtx.x && y == mtx.y && z == mtx.z;
        }

    };

    class Quat {
    public:
        Quat(){}
        Quat(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}
        Quat(const Matrix3& m){ Set(m); }
        Quat(const Vector3& v){ Set(v); }

        void Reset(){ x = y = z = 0.0f; w = 1.0f; }
        void Zero(){ w = x = y = z = 0.0f; }
        void Set(const Matrix3&);
        void Set(const Vector3&);
        void Set(const Vector3&, float);

        float x;
        float y;
        float z;
        float w;
    };
}

inline BinStream& operator>>(BinStream& bs, Hmx::Matrix3& mtx){
    bs >> mtx.x >> mtx.y >> mtx.z;
    return bs;
}

inline BinStream& operator>>(BinStream& bs, Hmx::Quat& q){
    bs >> q.x >> q.y >> q.z >> q.w;
    return bs;
}

class Transform {
public:
    class Hmx::Matrix3 m;
    class Vector3 v;

    // all of these are weak
    Transform(){}

    Transform(const Hmx::Matrix3& mtx, const Vector3& vec) : m(mtx), v(vec) {}

    // both of these use powerpc asm magic
    Transform(const register Transform& tf){
        // m.x.x = tf.m.x.x;
        // m.x.y = tf.m.x.y;
        PSQ_MOVE(m.x.x, tf.m.x.x);
        m.x.z = tf.m.x.z;

        // m.y.x = tf.m.y.x;
        // m.y.y = tf.m.y.y;
        PSQ_MOVE(m.y.x, tf.m.y.x);
        m.y.z = tf.m.y.z;

        // m.z.x = tf.m.z.x;
        // m.z.y = tf.m.z.y;
        PSQ_MOVE(m.z.x, tf.m.z.x);
        m.z.z = tf.m.z.z;

        // v.x = tf.v.x;
        // v.y = tf.v.y;
        PSQ_MOVE(v.x, tf.v.x);
        v.z = tf.v.z;
    }
    Transform& operator=(const Transform& tf){
        // m.x.x = tf.m.x.x;
        // m.x.y = tf.m.x.y;
        PSQ_MOVE(m.x.x, tf.m.x.x);
        m.x.z = tf.m.x.z;

        // m.y.x = tf.m.y.x;
        // m.y.y = tf.m.y.y;
        PSQ_MOVE(m.y.x, tf.m.y.x);
        m.y.z = tf.m.y.z;

        // m.z.x = tf.m.z.x;
        // m.z.y = tf.m.z.y;
        PSQ_MOVE(m.z.x, tf.m.z.x);
        m.z.z = tf.m.z.z;

        // v.x = tf.v.x;
        // v.y = tf.v.y;
        PSQ_MOVE(v.x, tf.v.x);
        v.z = tf.v.z;
        return *this;
    }

    void Reset(){
        m.Identity();
        v.Zero();
    }

    void SetFromDA(const class DataArray* da) {
        Reset();
        v.x = da->Float(2);
        v.y = da->Float(3);
        v.z = da->Float(4);
    }

    void LookAt(const Vector3&, const Vector3&);
    void Zero(){
        m.x.Zero();
        m.y.Zero();
        m.z.Zero();
        v.Zero();
    }

    bool operator==(const Transform& tf) const {
        return m == tf.m && v == tf.v;
    }
};

inline BinStream& operator>>(BinStream& bs, Transform& tf){
    bs >> tf.m >> tf.v;
    return bs;
}

class ShortQuat {
public:
    short x, y, z, w;
    void Reset() { x = y = z = 0; w = 32767; }
};

class TransformNoScale {
public:
    TransformNoScale(){}
    void Set(const Transform&);
    void Set(const TransformNoScale&);
    void SetRot(const Hmx::Matrix3&);
    void Reset();

    ShortQuat q;
    class Vector3 v;
};

BinStream& operator>>(BinStream&, TransformNoScale&);

class Plane {
public:
    Plane(){}

    float Dot(const Vector3& vec) const {
        return a * vec.x + b * vec.y + c * vec.z + d;
    }

    float a, b, c, d;
};

inline BinStream& operator>>(BinStream& bs, Plane& pl){
    bs >> pl.a >> pl.b >> pl.c >> pl.d;
    return bs;
}

class Frustum {
    // total size: 0x60
public:
    class Plane front; // offset 0x0, size 0x10
    class Plane back; // offset 0x10, size 0x10
    class Plane left; // offset 0x20, size 0x10
    class Plane right; // offset 0x30, size 0x10
    class Plane top; // offset 0x40, size 0x10
    class Plane bottom; // offset 0x50, size 0x10
};

// https://decomp.me/scratch/kGwAB
// lol, regswaps galore
inline void Scale(const Vector3& vec, const Hmx::Matrix3& mtx, Hmx::Matrix3& res){
    Scale(mtx.x, vec.x, res.x);
    Scale(mtx.y, vec.y, res.y);
    Scale(mtx.z, vec.z, res.z);
}

float AngleBetween(const Hmx::Quat&, const Hmx::Quat&);
void ScaleAddEq(Hmx::Quat&, const Hmx::Quat&, float);
void Normalize(const Hmx::Quat&, Hmx::Quat&);
void Multiply(const Hmx::Quat&, const Hmx::Quat&, Hmx::Quat&);
void FastInterp(const Hmx::Quat&, const Hmx::Quat&, float, Hmx::Quat&);
void Invert(const Hmx::Matrix3&, Hmx::Matrix3&);
void Multiply(const Hmx::Matrix3&, const Vector3&, Vector3&);
void Multiply(const Transform&, const Transform&, Transform&);

inline void Normalize(const Hmx::Matrix3 &src, Hmx::Matrix3 &dst) {
    Normalize(src.y, dst.y);
    Cross(dst.y, src.z, dst.x);
    Normalize(dst.x, dst.x);
    Cross(dst.x, dst.y, dst.z);
}

inline void Multiply(const Vector3& vin, const Hmx::Matrix3& mtx, Vector3& vout) {
    register __vec2x32float__ i1, i2, m1, m2, o1, o2;
    
    register const Vector3 *_vin = &vin;
    register       Vector3 *_vout = &vout;
    register const Hmx::Matrix3 *_m = &mtx;

    typedef Hmx::Matrix3 Matrix3;

    ASM_BLOCK(
        psq_l i1, Vector3.x(_vin), 0, 0
        psq_l i2, Vector3.y(_vin), 0, 0

        psq_l m1, Matrix3.z.x(_m), 0, 0
        psq_l m2, Matrix3.z.z(_m), 1, 0

        ps_muls1 o1, m1, i2
        ps_muls1 o2, m2, i2

        psq_l m1, Matrix3.y.x(_m), 0, 0
        psq_l m2, Matrix3.y.z(_m), 1, 0

        ps_madds0 o1, m1, i2, o1
        ps_madds0 o2, m2, i2, o2

        psq_l m1, Matrix3.x.x(_m), 0, 0
        psq_l m2, Matrix3.x.z(_m), 1, 0

        ps_madds0 o1, m1, i1, o1
        ps_madds0 o2, m2, i1, o2

        psq_st o1, Vector3.x(_vout), 0, 0
        psq_st o2, Vector3.z(_vout), 1, 0
    )
}

inline void Invert(const Transform& tfin, Transform& tfout){
    Vector3 vtmp;
    Negate(tfin.v, vtmp);
    Invert(tfin.m, tfout.m);
    Multiply(vtmp, tfout.m, tfout.v);
}

#endif

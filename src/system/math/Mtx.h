#ifndef MATH_MTX_H
#define MATH_MTX_H
#include "math/Vec.h"
#include "obj/Data.h"
#include "utl/BinStream.h"

#include "decomp.h"

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

        Matrix3(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9) :
            x(f1, f2, f3), y(f4, f5, f6), z(f7, f8, f9) {}

        void Set(float, float, float, float, float, float, float, float, float);
        void Set(const Vector3&, const Vector3&, const Vector3&);
        void Identity(){
            x.Set(1.0f, 0.0f, 0.0f);
            y.Set(0.0f, 1.0f, 0.0f);
            z.Set(0.0f, 0.0f, 1.0f);
        }
        Matrix3& operator=(const Matrix3 &);
        Vector3& operator[](int);
    };

    class Quat {
    public:
        Quat(){}
        Quat(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}

        void Reset(){ x = y = z = 0.0f; w = 1.0f; }
        void Zero(){ w = x = y = z = 0.0f; }

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

    // both of these use powerpc asm magic
    Transform(const register Transform& tf){
        register Transform* other = this;
        register float temp1;
        register float temp2;
        register float temp3;
        register float temp4;
        register float temp5;
        register float temp6;
        register float temp7;
        register float temp8;
        ASM_BLOCK(
            psq_lx temp8,0,tf,0,0
            lfs temp7, 8(tf);
            psq_l temp6,0xc(tf),0,0
            lfs temp5, 0x14(tf);
            psq_l temp4,0x18(tf),0,0
            lfs temp3, 0x20(tf);
            psq_l temp2,0x24(tf),0,0
            lfs temp1, 0x2C(tf);
            psq_stx temp8,0,other,0,0
            stfs temp7, 8(other);
            psq_st temp6,0x0c(other),0,0
            stfs temp5, 0x14(other);
            psq_st temp4,0x18(other),0,0
            stfs temp3, 0x20(other);
            psq_st temp2,0x24(other),0,0
            stfs temp1, 0x2C(other);
        )
    }
    Transform& operator=(const register Transform& tf){
        register Transform* other = this;
        register float temp1;
        register float temp2;
        register float temp3;
        register float temp4;
        register float temp5;
        register float temp6;
        register float temp7;
        register float temp8;
        ASM_BLOCK(
            psq_lx temp8,0,tf,0,0
            lfs temp7, 8(tf);
            psq_l temp6,0xc(tf),0,0
            lfs temp5, 0x14(tf);
            psq_l temp4,0x18(tf),0,0
            lfs temp3, 0x20(tf);
            psq_l temp2,0x24(tf),0,0
            lfs temp1, 0x2C(tf);
            psq_stx temp8,0,other,0,0
            stfs temp7, 8(other);
            psq_st temp6,0x0c(other),0,0
            stfs temp5, 0x14(other);
            psq_st temp4,0x18(other),0,0
            stfs temp3, 0x20(other);
            psq_st temp2,0x24(other),0,0
            stfs temp1, 0x2C(other);
        )
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
};

inline BinStream& operator>>(BinStream& bs, Transform& tf){
    bs >> tf.m >> tf.v;
    return bs;
}

class ShortQuat {
public:
    short x, y, z, w;
};

class TransformNoScale {
public:
    ShortQuat q;
    class Vector3 v;
};

class Plane {
public:
    float a, b, c, d;
};

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

#endif

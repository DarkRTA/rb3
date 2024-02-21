#ifndef MATH_MTX_H
#define MATH_MTX_H
#include "math/Vec.h"

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
}

class Transform {
public:
    class Hmx::Matrix3 m;
    class Vector3 v;

    // all of these are weak
    Transform(){}
    Transform(const Transform& tf){
        m = tf.m; v = tf.v;
    }
    Transform& operator=(const Transform&);
    void Reset(){
        m.Identity();
        v.Zero();
    }
    void LookAt(const Vector3&, const Vector3&);
    void Zero();
};

#endif

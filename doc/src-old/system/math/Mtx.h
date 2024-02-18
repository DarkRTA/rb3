#ifndef MATH_MTX_H
#define MATH_MTX_H
#include "world/vector3.hpp"

namespace Hmx {
    class Matrix3 {
    public:
        Vector3 row1;
        Vector3 row2;
        Vector3 row3;
        // all weak
        // Matrix3() {};
        // Matrix3(const Matrix3 &);
        void Set(const Vector3 &, const Vector3 &, const Vector3 &);
        void Set(float, float, float, float, float, float, float, float, float);
        void Identity();
        void operator=(const Matrix3 &);
    };
}

#endif

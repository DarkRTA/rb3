#ifndef RB3_MATRIX3_HPP
#define RB3_MATRIX3_HPP
#include "vector3.hpp"

namespace Hmx {
    class Matrix3 {
        Vector3 row1;
        Vector3 row2;
        Vector3 row3;
        void Identity();  
    };
}

#endif

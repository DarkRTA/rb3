#ifndef RB3_TRANSFORM_HPP
#define RB3_TRANSFORM_HPP
#include "math/Mtx.h"
#include "vector3.hpp"

class Transform {
public:
    Hmx::Matrix3 rot;
    Vector3 trans;
};

#endif

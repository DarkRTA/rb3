#ifndef RB3_SHORTTRANSFORM_HPP
#define RB3_SHORTTRANSFORM_HPP
#include "shortquat.hpp"
#include "vector3.hpp"
#include "transform.hpp"

class ShortTransform {
public:
    ShortQuat rot;
    Vector3 trans;

    ShortTransform(); // fn_802DE1D8
    void operator=(const ShortTransform &); // fn_802DE0D0
    void operator=(const Transform &); // fn_802DDF9C
};

#endif

#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H
#include "math/Vec.h"

class Sphere {
public:
    Sphere(){ Zero(); }
    void Zero(){ radius = 0.0f; center.Zero(); }
    Vector3 center;
    float radius;
};

#endif

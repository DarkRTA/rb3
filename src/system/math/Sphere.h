#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H
#include "math/Vec.h"
#include "math/Mtx.h"

class Sphere {
public:
    Sphere(){ Zero(); }
    void Zero(){ radius = 0.0f; center.Zero(); }
    float Radius() const { return radius; }

    Vector3 center;
    float radius;
};

bool operator>(const Sphere&, const Frustum&);

#endif

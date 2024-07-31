#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H
#include "math/Vec.h"
#include "math/Mtx.h"

class Sphere {
public:
    Sphere(){ Zero(); }
    void Zero(){ radius = 0.0f; center.Zero(); }
    float GetRadius() const { return radius; }

    Sphere& operator=(const Sphere& s){
        center = s.center;
        radius = s.radius;
        return *this;
    }

    void Set(const Vector3& vec, float f){
        center = vec;
        radius = f;
    }

    Vector3 center;
    float radius;
};

inline BinStream& operator>>(BinStream& bs, Sphere& s){
    Vector3 vec;
    float f;
    bs >> vec >> f;
    s.Set(vec, f);
    return bs;
}

bool operator>(const Sphere&, const Frustum&);
void Multiply(const Sphere&, const Transform&, Sphere&);

#endif

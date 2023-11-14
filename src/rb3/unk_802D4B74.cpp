#include "common.hpp"
#include "vector3.hpp"

extern float fn_802D54E8(float);
// fn_802D54A8
double Sqrt(double d){
    return (float)d * fn_802D54E8(d);
}

// fn_802D54E8

// fn_802D75F4
void Add(const Vector3& v1, const Vector3& v2, Vector3& dst){
    dst.Set(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
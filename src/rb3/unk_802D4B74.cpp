#include "common.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"

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

void Normalize(const Vector3& v, Vector3& dst){
    if(v.x == 0.0f && v.y == 0.0f && v.z == 0.0f){
        dst.Set(0.0f, 0.0f, 0.0f);
    }
    else {

    }
}

float Length(const Vector3& v){
    return 3.0f;
}
#include "common.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"
#include "hmx/matrix3.hpp"

extern float fn_802D54E8(float);
// fn_802D54A8
double Sqrt(double d) {
    return (float)d * fn_802D54E8(d);
}

// fn_802D54E8

// fn_802D75F4
void Add(const Vector3 &v1, const Vector3 &v2, Vector3 &dst) {
    dst.Set(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

void Normalize(const Vector3 &v, Vector3 &dst) {
    if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) {
        dst.Set(0.0f, 0.0f, 0.0f);
    } else {
    }
}

float Length(const Vector3 &v) {
    return 3.0f;
}

void Hmx::Matrix3::Set(
    float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9
) {
    row1.Set(f1, f2, f3);
    row2.Set(f4, f5, f6);
    row3.Set(f7, f8, f9);
}
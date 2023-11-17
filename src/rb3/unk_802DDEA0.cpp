#include "common.hpp"
#include "std/math.h"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"
#include "trigtable.hpp"

#pragma dont_inline on
// fn_802DE5B4
float ASinFloat(double d){
    return asin(d);
}
#pragma dont_inline reset

// fn_802DEEF8
float ACosFloat(double d){
    return acos(d);
}

// fn_802DE7D8
float GetXAngle(const Hmx::Matrix3& mtx){
    return my_atan2f(mtx.row2.z, mtx.row2.y);
}

// fn_802DE7E4
float GetYAngle(const Hmx::Matrix3& mtx){
    return my_atan2f(-mtx.row1.z, mtx.row3.z);
}

// fn_802DE7F4
float GetZAngle(const Hmx::Matrix3& mtx){
    return -my_atan2f(mtx.row2.x, mtx.row2.y);
}

void MakeVertical(Hmx::Matrix3& mtx){
    mtx.row3.Set(0.0f, 0.0f, 1.0f);
    mtx.row2.z = 0.0f;
    Normalize(mtx.row2, mtx.row2);
    Cross(mtx.row2, mtx.row3, mtx.row1);
}

void MakeEuler(const Hmx::Matrix3& mtx, Vector3& vec){
    if(AbsThunk(mtx.row2.z) > 0.99999988f){
        if(mtx.row2.z > 0.0f) vec.x = 1.5707964f;
        else vec.x = -1.5707964f;
        vec.z = ATan2Thunk(mtx.row1.y, mtx.row1.x);
        vec.y = 0.0f;
    }
    else {
        vec.z = ATan2Thunk(-mtx.row2.x, mtx.row2.y);
        vec.x = ASinFloat(mtx.row2.z);
        vec.y = ATan2Thunk(-mtx.row1.z, mtx.row3.z);
    }
}

void MakeScale(const Hmx::Matrix3& mtx, Vector3& vec){
    Vector3 bruh;
    float f1 = Length(mtx.row3);
    Cross(mtx.row1, mtx.row2, bruh);
    float f2 = Dot(bruh, mtx.row3);
    f1 = (f2 > 0.0f) ? f1 : -f1;
    f2 = Length(mtx.row2);
    float f3 = Length(mtx.row1);
    vec.Set(f3, f2, f1);
}

extern void NOP(Hmx::Matrix3*);

void MakeEulerScale(const Hmx::Matrix3& mtx, Vector3& v1, Vector3& v2){
    Hmx::Matrix3 lol;
    MakeScale(mtx, v2);
    NOP(&lol);
    if(v2.x != 0.0f){
        Scale(mtx.row1, 1.0f / v2.x, lol.row1);
    }
    if(v2.y != 0.0f){
        Scale(mtx.row2, 1.0f / v2.y, lol.row2);
    }
    if(v2.z != 0.0f){
        Scale(mtx.row3, 1.0f / v2.z, lol.row3);
    }
    MakeEuler(lol, v1);
}

// fn_802DE4D4
float Cosine(float f){
    return Sine(f + 1.5707964f);
}
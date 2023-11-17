#include "common.hpp"
#include "std/math.h"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"

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
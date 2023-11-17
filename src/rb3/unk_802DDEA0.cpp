#include "common.hpp"
#include "std/math.h"
#include "hmx/matrix3.hpp"

// fn_802DE5B4
float ASinFloat(double d){
    return asin(d);
}

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
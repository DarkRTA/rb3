#include "common.hpp"
#include "std/math.h"
#include "hmx/matrix3.hpp"
#include "vector3.hpp"
#include "vector_ops.hpp"
#include "trigtable.hpp"
#include "hmx/quat.hpp"
#include "textstream.hpp"
#include "vector2.hpp"
#include "transform.hpp"
#include "binstream.hpp"
#include "shortquat.hpp"

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

// fn_802DE8BC - https://decomp.me/scratch/uzSF7

#pragma dont_inline on
// fn_802DE4D4
float Cosine(float f){
    return Sine(f + 1.5707964f);
}
#pragma dont_inline reset

void MakeRotMatrix(const Vector3& v1, const Vector3& v2, Hmx::Matrix3& mtx) {
    mtx.row2 = v1;
    Normalize(mtx.row2, mtx.row2);
    Cross(mtx.row2, v2, mtx.row1);
    Normalize(mtx.row1, mtx.row1);
    Cross(mtx.row1, mtx.row2, mtx.row3);
}

TextStream& operator<<(TextStream& ts, const Hmx::Quat& q){
    ts << "(x:" << q.x << " y:" << q.y << " z:" << q.z << " w:" << q.w << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Vector3& vec){
    ts << "(x:" << vec.x << " y:" << vec.y << " z:" << vec.z << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Vector2& vec){
    ts << "(x:" << vec.x << " y:" << vec.y << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Hmx::Matrix3& mtx){
    ts << "\n\t" << mtx.row1 << "\n\t" << mtx.row2 << "\n\t" << mtx.row3;
    return ts;
}

TextStream& operator<<(TextStream& ts, const Transform& tf){
    ts << tf.rot << "\n\t" << tf.trans;
    return ts;
}

void FastInvert(const Hmx::Matrix3& mtx, Hmx::Matrix3& dst){
    float d1 = 1.0f / Dot(mtx.row1, mtx.row1);
    float d2 = 1.0f / Dot(mtx.row2, mtx.row2);
    float d3 = 1.0f / Dot(mtx.row3, mtx.row3);
    dst.Set(mtx.row1.x * d1, mtx.row2.x * d2, mtx.row3.x * d3,
        mtx.row1.y * d1, mtx.row2.y * d2, mtx.row3.y * d3,
        mtx.row1.z * d1, mtx.row2.z * d2, mtx.row3.z * d3);
}

BinStream& operator<<(BinStream& bs, const Vector3& vec){
    bs << vec.x << vec.y << vec.z;
    return bs;
}

void ShortQuat::Set(const Hmx::Quat& q){
    x = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.x + 0.5f));
    y = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.y + 0.5f));
    z = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.z + 0.5f));
    w = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.w + 0.5f));
}

void ShortQuat::operator=(const ShortQuat& q){
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
}

bool Vector3::operator==(const Vector3& vec) const {
    bool b = false;
    if(x == vec.x && y == vec.y && z == vec.z) b = true;
    return b;
}

bool Vector3::operator!=(const Vector3& vec) const {
    bool b = false;
    if(x != vec.x || y != vec.y || z != vec.z) b = true;
    return b;
}

void ShortQuat::ToQuat(Hmx::Quat& q) const {
    q.Set((float)(x * 0.000030518509f), (float)(y * 0.000030518509f), (float)(z * 0.000030518509f), (float)(w * 0.000030518509f));
}

void Normalize(const Hmx::Quat& q, Hmx::Quat& dst){
    dst.x = 0.0000099999997f;
}

void IdentityInterp(const Hmx::Quat& q, float f, Hmx::Quat& dst) {
    if(f == 0.0f){
        dst = q;
    }
    else if(f == 1.0f){
        dst.Set(0.0f, 0.0f, 0.0f, 1.0f);
    }
    else {
        float f2 = 1.0f - f;
        dst.x = q.x * f2;
        dst.y = q.y * f2;
        dst.z = q.z * f2;
        float f1 = q.w;
        if(f1 < 0.0f){
            dst.w = f1 * f2 - f;
        }
        else dst.w = f1 * f2 + f;
        Normalize(dst, dst);
    }
}

#pragma dont_inline on
BinStream& operator>>(BinStream& bs, Vector3& vec){
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}
#pragma dont_inline reset

BinStream& operator>>(BinStream& bs, Hmx::Matrix3& mtx){
    bs >> mtx.row1 >> mtx.row2 >> mtx.row3;
    return bs;
}

void Hmx::Quat::Set(const Vector3& vec, float f) {
    float mult = 0.5f * f;
    float f1 = Sine(mult);
    float f2 = Cosine(mult);
    w = f2;
    x = vec.x * f1;
    y = vec.y * f1;
    z = vec.z * f1;
}

void Hmx::Quat::Set(const Vector3& vec) {
    Vector3 stack;
    Scale(vec, 0.5f, stack);
    float f1 = Sine(stack.x);
    float f2 = Cosine(stack.x);
    float f3 = Sine(stack.y);
    float f4 = Cosine(stack.y);
    Set(f1 * f4, f2 * f3, f1 * f3, f2 * f4);
    f1 = Sine(stack.z);
    f2 = Cosine(stack.z);
    Set(f2 * x - f1 * y, f2 * y + f1 * x, f2 * z + f1 * w, f2 * w - f1 * z);
}
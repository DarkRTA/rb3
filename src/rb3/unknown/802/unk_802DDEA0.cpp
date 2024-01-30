#include "rot.hpp"

#include "common.hpp"
#include "math.h"
#include "vector_ops.hpp"
#include "trig.hpp"
#include "binstream.hpp"
#include "shortquat.hpp"
#include "shorttransform.hpp"

BinStream &operator<<(BinStream &bs, const Vector3 &vec) {
    bs << vec.x << vec.y << vec.z;
    return bs;
}

void ShortQuat::Set(const Hmx::Quat &q) {
    x = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.x + 0.5f));
    y = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.y + 0.5f));
    z = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.z + 0.5f));
    w = FloorThunk(Clamp(-32767.0f, 32767.0f, 32767.0f * q.w + 0.5f));
}

void ShortQuat::operator=(const ShortQuat &q) {
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
}

bool Vector3::operator==(const Vector3 &vec) const {
    bool b = false;
    if (x == vec.x && y == vec.y && z == vec.z)
        b = true;
    return b;
}

bool Vector3::operator!=(const Vector3 &vec) const {
    bool b = false;
    if (x != vec.x || y != vec.y || z != vec.z)
        b = true;
    return b;
}

void ShortQuat::ToQuat(Hmx::Quat &q) const {
    q.Set(
        (float)(x * 0.000030518509f),
        (float)(y * 0.000030518509f),
        (float)(z * 0.000030518509f),
        (float)(w * 0.000030518509f)
    );
}


BinStream &operator>>(BinStream &bs, Vector3 &vec) {
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}


BinStream &operator>>(BinStream &bs, Hmx::Matrix3 &mtx) {
    bs >> mtx.row1 >> mtx.row2 >> mtx.row3;
    return bs;
}

Hmx::Quat::Quat(const Hmx::Matrix3 &mtx) {
    Set(mtx);
}

void ShortQuat::Set(const Hmx::Matrix3 &mtx) {
    Set(Hmx::Quat(mtx));
}

// fn_802DE1D8
ShortTransform::ShortTransform() {
    rot.z = 0;
    rot.y = 0;
    rot.x = 0;
    rot.w = 0x7FFF;
    trans.z = 0.0f;
    trans.y = 0.0f;
    trans.x = 0.0f;
}

// fn_802DE0D0
void ShortTransform::operator=(const ShortTransform &st) {
    rot = st.rot;
    trans = st.trans;
}

// fn_802DDF9C
void ShortTransform::operator=(const Transform &tf) {
    rot.Set(tf.rot);
    trans = tf.trans;
}

void ShortQuat::SetThunk(const Hmx::Quat &q) {
    Set(q);
}

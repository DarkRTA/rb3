#include "Rot.h"
#include "math/Mtx.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include <cmath>

void deadstripped_assert() {MILO_ASSERT(false, 0);}

void TransformNoScale::SetRot(const Hmx::Matrix3& m) {
    Hmx::Quat quat;
    quat.Set(m);

    float nu_x = 32767.0f * quat.x + 0.5f;
    q.x = std::floor(nu_x > quat.x ? nu_x : (nu_x < -32767.0f ? nu_x : quat.x));

    float nu_y = 32767.0f * quat.y + 0.5f;
    q.y = std::floor(nu_y > quat.y ? nu_y : (nu_y < -32767.0f ? nu_y : quat.y));

    float nu_z = 32767.0f * quat.z + 0.5f;
    q.z = std::floor(nu_z > quat.z ? nu_z : (nu_z < -32767.0f ? nu_z : quat.z));

    float nu_w = 32767.0f * quat.w + 0.5f;
    q.w = std::floor(nu_w > quat.w ? nu_w : (nu_w < -32767.0f ? nu_w : quat.w));

}

void TransformNoScale::Reset() {
    q.Reset();
    v.Zero();
}

BinStream& operator>>(BinStream& bs, TransformNoScale& t) {
    Hmx::Matrix3 m;
    bs >> m;
    bs >> t.v;
    t.SetRot(m);
    return bs;
}

float GetXAngle(const Hmx::Matrix3& m) {
    float z = m.y.z;
    return std::atan2(z, m.y.y);
}

float GetYAngle(const Hmx::Matrix3& m) {
    float z = -m.x.z;
    return std::atan2(z, m.z.z);
}

float GetZAngle(const Hmx::Matrix3& m) {
    float x = m.y.x;
    return -std::atan2(x, m.y.y);
}

TextStream& operator<<(TextStream& ts, const Hmx::Quat& v) {
    ts << "(x:" << v.x << " y:" << v.y << " z:" << v.z << " w:" << v.w << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Vector3& v) {
    ts << "(x:" << v.x << " y:" << v.y << " z:" << v.z << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Vector2& v) {
    ts << "(x:" << v.x << " y:" << v.y << ")";
    return ts;
}

TextStream& operator<<(TextStream& ts, const Hmx::Matrix3& m) {
    ts << "\n\t" << m.x << "\n\t" << m.y << "\n\t" << m.z;
    return ts;
}

TextStream& operator<<(TextStream& ts, const Transform& t) {
    ts << t.m << "\n\t" << t.v;
    return ts;
}

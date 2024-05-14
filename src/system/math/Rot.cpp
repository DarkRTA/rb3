#include "Rot.h"
#include "os/Debug.h"
#include <cmath>

void deadstripped_assert() {MILO_ASSERT(false, 0);}

float GetXAngle(const Hmx::Matrix3& m) {
    float z = m.y.z;
    return atan2(z, m.y.y);
}

float GetYAngle(const Hmx::Matrix3& m) {
    float z = -m.x.z;
    return atan2(z, m.z.z);
}

float GetZAngle(const Hmx::Matrix3& m) {
    float x = m.y.x;
    return -atan2(x, m.y.y);
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

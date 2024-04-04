#include "Rot.h"

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

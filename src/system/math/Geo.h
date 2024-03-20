#ifndef MATH_GEO_H
#define MATH_GEO_H
#include "math/Vec.h"
#include "utl/BinStream.h"

class Segment {
public:
    Vector3 start;
    Vector3 end;
};

namespace Hmx {
    class Rect {
    public:
        Rect() {}
        Rect(float xx, float yy, float ww, float hh) : x(xx), y(yy), w(ww), h(hh) {}
        float x, y, w, h;
    };
}

inline BinStream& operator>>(BinStream& bs, Hmx::Rect& rect){
    bs >> rect.x >> rect.y >> rect.w >> rect.h;
    return bs;
}

class Box {
public:
    Box() : mMin(1.0f, 1.0f, 1.0f), mMax(-1.0f, -1.0f, -1.0f) {}
    Vector3 mMin;
    Vector3 mMax;
};

#endif

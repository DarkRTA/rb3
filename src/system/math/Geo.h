#ifndef MATH_GEO_H
#define MATH_GEO_H
#include "math/Vec.h"

class Segment {
public:
    Vector3 start;
    Vector3 end;
};

namespace Hmx {
    class Rect {
    public:
        Rect() : x(0.0f), y(0.0f), w(1.0f), h(1.0f) {}
        float x, y, w, h;
    };
}

#endif

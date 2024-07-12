#ifndef MATH_GEO_H
#define MATH_GEO_H
#include "math/Vec.h"
#include "math/Sphere.h"
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
        void Set(float xx, float yy, float ww, float hh){ x = xx; y = yy; w = ww; h = hh; }
        float x, y, w, h;
    };

    class Polygon {
    public:
        Polygon() {}
        ~Polygon() {}
        std::vector<Vector2> mPoints;
    };

    struct Ray {
        Vector2 base, dir;
    };
}

inline BinStream& operator>>(BinStream& bs, Hmx::Rect& rect){
    bs >> rect.x >> rect.y >> rect.w >> rect.h;
    return bs;
}

class Box {
public:
    Box(){}
    void GrowToContain(const Vector3&, bool);

    Vector3 mMin;
    Vector3 mMax;
};

inline BinStream& operator>>(BinStream& bs, Box& box){
    bs >> box.mMin >> box.mMax;
    return bs;
}

void SetBSPParams(float f1, float f2, int r3, int r4, float f3);
bool Intersect(const Segment&, const Sphere&);
bool Intersect(const Transform&, const Hmx::Polygon&, const class BSPNode*);
void Multiply(const Box&, float, Box&);

#endif

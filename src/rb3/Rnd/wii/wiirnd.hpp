#ifndef RND_WII_WIIRND_HPP
#define RND_WII_WIIRND_HPP
#include "math/Color.h"
#include "math/Rect.h"

//#include "Rnd/rnd.hpp"
#include "world/vector3.hpp"

class WiiRnd /*: Rnd*/ {
    WiiRnd();
    virtual ~WiiRnd();
    virtual void DrawLine(const Vector3&, const Vector3&, const Hmx::Color&, bool);
    virtual void DrawQuad(const Hmx::Rect&);
};

#endif

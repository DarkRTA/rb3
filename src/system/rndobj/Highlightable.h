#ifndef RNDOBJ_HIGHLIGHTABLE_H
#define RNDOBJ_HIGHLIGHTABLE_H
#include "obj/Object.h"

class RndHighlightable : public virtual Hmx::Object {
public:
    RndHighlightable(){}
    virtual ~RndHighlightable(){}
    virtual void Highlight() = 0;
};

#endif

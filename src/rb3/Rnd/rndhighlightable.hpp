#ifndef RND_RNDHIGHLIGHTABLE_HPP
#define RND_RNDHIGHLIGHTABLE_HPP
#include "Object.h"

class RndHighlightable : public virtual Hmx::Object {
public:
    RndHighlightable();
    virtual ~RndHighlightable();
    virtual void Highlight() = 0;
};

#endif

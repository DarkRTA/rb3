#ifndef RND_RNDHIGHLIGHTABLE_HPP
#define RND_RNDHIGHLIGHTABLE_HPP
#include "rb3/hmx/object.hpp"

class RndHighlightable : public virtual Hmx::Object {
public:
    RndHighlightable();
    virtual ~RndHighlightable();
    virtual void Highlight() = 0;
};

#endif

#ifndef RB3_RND_DRAWABLE_HPP
#define RB3_RND_DRAWABLE_HPP
#include "rndhighlightable.hpp"
#include "rb3/symbol.hpp"
#include "rb3/hmx/quat.hpp"

class RndDrawable : public RndHighlightable {
    RndDrawable();
    virtual ~RndDrawable();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol *);

    static Symbol StaticClassName();

    bool mShowing;
    Hmx::Quat mBoundSphere;
    float mDrawOrder;
};

#endif // RB3_RND_DRAWABLE_HPP

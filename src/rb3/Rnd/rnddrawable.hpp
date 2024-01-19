#ifndef RND_RNDDRAWABLE_HPP
#define RND_RNDDRAWABLE_HPP
#include "rndhighlightable.hpp"
#include "rb3/symbol.hpp"
#include "rb3/hmx/quat.hpp"

class RndDrawable : public RndHighlightable {
    RndDrawable();
    virtual ~RndDrawable();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol *);

    virtual void Save(BinStream&);

    static Symbol StaticClassName();

    bool mShowing;
    Hmx::Quat mBoundSphere;
    float mDrawOrder;
};

#endif

#ifndef RND_RNDDRAWABLE_HPP
#define RND_RNDDRAWABLE_HPP
#include "Rnd/rndhighlightable.hpp"
#include "sphere.hpp"

class RndDrawable : public virtual RndHighlightable {
    RndDrawable();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndDrawable();

    static Symbol StaticClassName();

    bool mShowing;
    Sphere mBoundSphere;
    float mDrawOrder;
};

#endif

#ifndef RNDOBJ_FLARE_H
#define RNDOBJ_FLARE_H
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "math/Vec.h"
#include "rndobj/Mat.h"
#include "math/Mtx.h"

class RndFlare : public RndTransformable, public RndDrawable {
public:
    RndFlare();
    OBJ_CLASSNAME(Flare)
    OBJ_SET_TYPE(Flare)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndFlare();
    virtual void Highlight();
    virtual void Print();

    bool mPointTest; // 0xb0
    bool mAreaTest;
    bool mVisible;
    Vector2 mSizes;
    ObjPtr<RndMat, ObjectDir> mMat;
    Vector2 mRange;
    float mOffset;
    int mSteps;
    int mStep;
    Hmx::Rect mArea;
    float unkec;
    Hmx::Matrix3 mMatrix;
    Vector2 unk114;
};

#endif

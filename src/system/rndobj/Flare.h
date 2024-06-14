#pragma once
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
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual void Print();
    virtual void DrawShowing();
    virtual void Mats(std::list<class RndMat*>&, bool);

    void CalcScale();
    void SetMat(RndMat*);
    void SetPointTest(bool);
    void SetSteps(int);

    DECLARE_REVS
    NEW_OBJ(RndFlare)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFlare)
    }

    bool mPointTest; // 0xB0
    bool mAreaTest; // 0xB1
    bool mVisible; // 0xB2
    Vector2 mSizes; // 0xB4
    ObjPtr<RndMat, ObjectDir> mMat; // 0xBC
    Vector2 mRange; // 0xC8
    float mOffset; // 0xD0
    int mSteps; // 0xD4
    int mStep; // 0xD8
    Hmx::Rect mArea; // 0xDC
    float unkec; // 0xEC
    Hmx::Matrix3 mMatrix; // 0xF0
    Vector2 unk114; // 0x114
};

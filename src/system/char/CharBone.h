#ifndef CHAR_CHARBONE_H
#define CHAR_CHARBONE_H
#include "obj/Object.h"
#include <vector>
#include "rndobj/Trans.h"

class CharBone : public Hmx::Object {
public:

    enum Type {
        TYPE_POS = 0,
        TYPE_SCALE = 1,
        TYPE_QUAT = 2,
        TYPE_ROTX = 3,
        TYPE_ROTY = 4,
        TYPE_ROTZ = 5,
        TYPE_END = 6,
        NUM_TYPES = 7,
    };

    class WeightContext {
    public:
        // WeightContext(int ctx, float wt) : mContext(ctx), mWeight(wt) {}
        int mContext;
        float mWeight;
    };

    CharBone();
    virtual ~CharBone(){}
    OBJ_CLASSNAME(CharBone);
    OBJ_SET_TYPE(CharBone);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    
    int mPositionContext; // 0x1c
    int mScaleContext; // 0x20
    Type mRotation; // 0x24
    int mRotationContext; // 0x28
    ObjPtr<CharBone, ObjectDir> mTarget; // 0x2c
    std::vector<WeightContext> mWeights; // 0x38
    ObjPtr<RndTransformable, ObjectDir> mTrans; // 0x40
    bool mBakeOutAsTopLevel; // 0x4c
};

BinStream& operator>>(BinStream&, CharBone::WeightContext&);

#endif

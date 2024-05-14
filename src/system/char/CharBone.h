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
        int mContext;
        float mWeight;
    };

    CharBone();
    virtual ~CharBone();
    OBJ_CLASSNAME(CharBone);
    OBJ_SET_TYPE(CharBone);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    int mPositionContext;
    int mScaleContext;
    Type mRotation;
    int mRotationContext;
    ObjPtr<CharBone, ObjectDir> mTarget;
    std::vector<WeightContext> mWeights;
    ObjPtr<RndTransformable, ObjectDir> mTrans;
    bool mBakeOutAsTopLevel;
};

#endif

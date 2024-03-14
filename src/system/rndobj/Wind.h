#ifndef RNDOBJ_WIND_H
#define RNDOBJ_WIND_H
#include "obj/Object.h"
#include "math/Vec.h"
#include "obj/ObjPtr_p.h"

class RndWind : public Hmx::Object {
public:
    RndWind();
    virtual ~RndWind();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(Wind);
    OBJ_SET_TYPE(Wind);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void SetWindOwner(RndWind*);
    void Zero();
    void SetDefaults();
    void SyncLoops();

    DELETE_OVERLOAD;

    Vector3 mPrevailing;
    Vector3 mRandom;
    float mTimeLoop;
    float mSpaceLoop;
    Vector3 mTimeRate;
    Vector3 mSpaceRate;
    ObjOwnerPtr<RndWind, ObjectDir> mWindOwner;
};

#endif // RNDOBJ_WIND_H

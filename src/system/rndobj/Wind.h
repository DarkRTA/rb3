#ifndef RNDOBJ_WIND_H
#define RNDOBJ_WIND_H
#include "obj/Object.h"
#include "math/Vec.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"

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
    float GetWind(float);
    void GetWind(const Vector3&, float, Vector3&);

    static void Init();
    NEW_OBJ(RndWind)

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD

    Vector3 mPrevailing; // 0x1c
    Vector3 mRandom; // 0x28
    float mTimeLoop; // 0x34
    float mSpaceLoop; // 0x38
    Vector3 mTimeRate; // 0x3c
    Vector3 mSpaceRate; // 0x48
    ObjOwnerPtr<RndWind, ObjectDir> mWindOwner; // 0x54
};

#endif // RNDOBJ_WIND_H

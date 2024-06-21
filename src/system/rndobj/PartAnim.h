#ifndef RNDOBJ_PARTANIM_H
#define RNDOBJ_PARTANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Part.h"
#include "math/Key.h"

class RndParticleSysAnim : public RndAnimatable {
public:
    RndParticleSysAnim();
    OBJ_CLASSNAME(ParticleSysAnim);
    OBJ_SET_TYPE(ParticleSysAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndParticleSysAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndParticleSysAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndParticleSysAnim)
    }

    ObjPtr<RndParticleSys, ObjectDir> mParticleSys; // 0x10
    Keys<Hmx::Color, Hmx::Color> mStartColorKeys; // 0x1c
    Keys<Hmx::Color, Hmx::Color> mEndColorKeys; // 0x24
    Keys<Vector2, Vector2> mEmitRateKeys; // 0x2c
    Keys<Vector2, Vector2> mSpeedKeys; // 0x34
    Keys<Vector2, Vector2> mLifeKeys; // 0x3c
    Keys<Vector2, Vector2> mStartSizeKeys; // 0x44
    ObjOwnerPtr<RndParticleSysAnim, ObjectDir> mKeysOwner; // 0x4c
};

#endif

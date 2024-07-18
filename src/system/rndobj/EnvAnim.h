#ifndef RNDOBJ_ENVANIM_H
#define RNDOBJ_ENVANIM_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "math/Key.h"
#include "rndobj/Env.h"

class RndEnvAnim : public RndAnimatable {
public:
    RndEnvAnim();
    OBJ_CLASSNAME(EnvAnim);
    OBJ_SET_TYPE(EnvAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndEnvAnim(){}
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget(){ return mEnviron; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    Keys<Hmx::Color, Hmx::Color>& AmbientColorKeys(){ return mKeysOwner->mAmbientColorKeys; }
    Keys<Hmx::Color, Hmx::Color>& FogColorKeys(){ return mKeysOwner->mFogColorKeys; }
    Keys<Vector2, Vector2>& FogRangeKeys(){ return mKeysOwner->mFogRangeKeys; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndEnvAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndEnvAnim)
    }
    
    ObjPtr<RndEnviron, ObjectDir> mEnviron; // 0x10
    Keys<Hmx::Color, Hmx::Color> mFogColorKeys; // 0x1c
    Keys<Vector2, Vector2> mFogRangeKeys; // 0x24
    Keys<Hmx::Color, Hmx::Color> mAmbientColorKeys; // 0x2c
    ObjOwnerPtr<RndEnvAnim, ObjectDir> mKeysOwner; // 0x34
};

#endif
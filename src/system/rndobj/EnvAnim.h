#ifndef RNDOBJ_ENVANIM_H
#define RNDOBJ_ENVANIM_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "utl/Key.h"
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
    virtual ~RndEnvAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual RndAnimatable* AnimTarget(); // weak
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();
    
    ObjPtr<RndEnviron, ObjectDir> mEnviron;
    Keys<Hmx::Color, Hmx::Color> mFogColorKeys;
    Keys<Vector2, Vector2> mFogRangeKeys;
    Keys<Hmx::Color, Hmx::Color> mAmbientColorKeys;
    ObjOwnerPtr<RndEnvAnim, ObjectDir> mKeysOwner;
};

#endif

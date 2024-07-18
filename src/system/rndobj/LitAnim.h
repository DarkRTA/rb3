#ifndef RNDOBJ_LITANIM_H
#define RNDOBJ_LITANIM_H
#include "obj/ObjPtr_p.h"
#include "rndobj/Anim.h"
#include "rndobj/Lit.h"
#include "rndobj/PropKeys.h"

class RndLightAnim : public RndAnimatable {
public:
    RndLightAnim();
    OBJ_CLASSNAME(LightAnim);
    OBJ_SET_TYPE(LightAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndLightAnim(){}
    virtual void SetFrame(float, float); 
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget(){ return mLight; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void SetKeysOwner(RndLightAnim*);
    DataNode OnCopyKeys(DataArray*);
    Keys<Hmx::Color, Hmx::Color>& ColorKeys(){ return mKeysOwner->mColorKeys; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndLightAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndLightAnim)
    }

    ObjPtr<RndLight, class ObjectDir> mLight; // 0x10
    Keys<Hmx::Color, Hmx::Color> mColorKeys; // 0x1c
    ObjOwnerPtr<RndLightAnim, class ObjectDir> mKeysOwner; // 0x24
};

#endif

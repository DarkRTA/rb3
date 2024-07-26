#ifndef RNDOBJ_PROPANIM_H
#define RNDOBJ_PROPANIM_H
#include "rndobj/Anim.h"
#include "obj/Object.h"
#include <vector>
#include "rndobj/PropKeys.h"

class RndPropAnim : public RndAnimatable {
public:
    RndPropAnim();
    OBJ_CLASSNAME(PropAnim);
    OBJ_SET_TYPE(PropAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndPropAnim();
    virtual bool Loop(){ return mLoop; }
    virtual void StartAnim(){}
    virtual void EndAnim(){}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void RemoveKeys();
    PropKeys* GetKeys(const Hmx::Object*, DataArray*);
    PropKeys* AddKeys(Hmx::Object*, DataArray*, PropKeys::AnimKeysType);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPropAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndPropAnim)
    }
    
    std::vector<PropKeys*> mPropKeys; // 0x10
    float mLastFrame; // 0x18
    bool mInSetFrame; // 0x1c
    bool mLoop; // 0x1d
};

#endif

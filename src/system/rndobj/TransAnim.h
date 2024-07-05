#ifndef RNDOBJ_TRANSANIM_H
#define RNDOBJ_TRANSANIM_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Key.h"

class RndTransAnim : public RndAnimatable {
public:
    RndTransAnim();
    OBJ_CLASSNAME(TransAnim);
    OBJ_SET_TYPE(TransAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransAnim(){}
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget() { return mTrans; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void MakeTransform(float, Transform&, bool, float);
    void SetTrans(RndTransformable*);
    void SetKeysOwner(RndTransAnim*);

    RndTransformable* Trans() const { return mTrans; }
    Keys<Vector3, Vector3>& TransKeys(){ return mKeysOwner->mTransKeys; }
    Keys<Hmx::Quat, Hmx::Quat>& RotKeys(){ return mKeysOwner->mRotKeys; }
    Keys<Vector3, Vector3>& ScaleKeys(){ return mKeysOwner->mScaleKeys; }
    bool TransSpline() const { return mKeysOwner->mTransSpline; }
    bool ScaleSpline() const { return mKeysOwner->mScaleSpline; }

    DataNode OnSetTransSpline(const DataArray*);
    DataNode OnSetScaleSpline(const DataArray*);
    DataNode OnSetRotSlerp(const DataArray*);
    DataNode OnTrans(const DataArray*);
    DataNode OnNumTransKeys(const DataArray*);
    DataNode OnNumRotKeys(const DataArray*);
    DataNode OnNumScaleKeys(const DataArray*);
    DataNode OnAddTransKey(const DataArray*);
    DataNode OnAddRotKey(const DataArray*);
    DataNode OnAddScaleKey(const DataArray*);
    DataNode OnSplice(const DataArray*);
    DataNode OnRemoveRotKeys(const DataArray*);
    DataNode OnRemoveTransKeys(const DataArray*);
    DataNode OnLinearize(const DataArray*);
    DataNode OnSetTrans(const DataArray*);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTransAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTransAnim)
    }

    ObjPtr<RndTransformable, ObjectDir> mTrans; // 0x10
    bool mTransSpline; // 0x1C
    bool mScaleSpline; // 0x1D
    bool mRotSlerp; // 0x1E
    bool mRotSpline; // 0x1F
    Keys<Hmx::Quat, Hmx::Quat> mRotKeys; // 0x20
    Keys<Vector3, Vector3> mTransKeys; // 0x28
    Keys<Vector3, Vector3> mScaleKeys; // 0x30
    ObjOwnerPtr<RndTransAnim, ObjectDir> mKeysOwner; // 0x38
    bool mRepeatTrans; // 0x44
    bool mFollowPath; // 0x45
};

#endif

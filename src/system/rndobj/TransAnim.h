#ifndef RNDOBJ_TRANSANIM_H
#define RNDOBJ_TRANSANIM_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "utl/Key.h"

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
    virtual Hmx::Object* AnimTarget();
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    void SetTrans(RndTransformable*);
    void SetKeysOwner(RndTransAnim*);

    ObjPtr<RndTransformable, ObjectDir> mTrans;
    bool mTransSpline;
    bool mScaleSpline;
    bool mRotSlerp;
    bool mRotSpline;
    Keys<Hmx::Quat, Hmx::Quat> mRotKeys;
    Keys<Vector3, Vector3> mTransKeys;
    Keys<Vector3, Vector3> mScaleKeys;
    ObjOwnerPtr<RndTransAnim, ObjectDir> mKeysOwner;
    bool mRepeatTrans;
    bool mFollowPath;
};

#endif

#pragma once
#include "char/CharIKHand.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"
#include "char/CharCollide.h"

/** "Remedial foot skate ik, not yet ready for prime time." */
class CharIKFoot : public CharIKHand {
public:
    CharIKFoot();
    virtual ~CharIKFoot();
    virtual void Highlight(){}
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharIKHand);
    OBJ_SET_TYPE(CharIKHand);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Enter();
    virtual void SetName(const char*, class ObjectDir*);

    void DoFSM(Transform&);

    DECLARE_REVS;
    DELETE_OVERLOAD;
    NEW_OBJ(CharIKFoot)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharIKFoot)
    }
    
    ObjPtr<RndTransformable> unk88;
    int unk94;
    /** "which bone to use to get the IK data from" */
    ObjPtr<RndTransformable> mData; // 0x98
    /** "Which element index to use (x=0, y=1, z=2)" */
    int mDataIndex; // 0xa4
    Vector3 unka8; // 0xa8
    float unkb4; // 0xb4
    ObjPtr<Character> mMe; // 0xb8
};

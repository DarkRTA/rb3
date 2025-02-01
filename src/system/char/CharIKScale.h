#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "Rescales a local position of a bone" */
class CharIKScale : public CharWeightable, public CharPollable {
public:
    CharIKScale();
    OBJ_CLASSNAME(CharIKScale);
    OBJ_SET_TYPE(CharIKScale);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~CharIKScale();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);

    /** "Call after posing normally, captures data with which to auto compute scale" */
    void CaptureBefore();
    /** "Call after posing deformed, computes scale based on ratio of capture_before
     * capture to now." */
    void CaptureAfter();

    DECLARE_REVS;
    DELETE_OVERLOAD;
    NEW_OBJ(CharIKScale)
    static void Init() { REGISTER_OBJ_FACTORY(CharIKScale) }

    /** "The bone to be scaled" */
    ObjPtr<RndTransformable> mDest; // 0x20
    /** "Scale to apply" */
    float mScale; // 0x2c
    /** "Apply remainder weight to these targets" */
    ObjPtrList<RndTransformable> mSecondaryTargets; // 0x30
    /** "If dest starts out at or below this height, weight will be 0" */
    float mBottomHeight; // 0x40
    /** "If dest starts out at or above this height, weight will be 1" */
    float mTopHeight; // 0x44
    /** "Automatically determine weight from top & bottom heights" */
    bool mAutoWeight; // 0x48
};

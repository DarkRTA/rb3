#pragma once
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "<p>Rigs a bone between two other bones and sets the
 *  orientation from that.</p>
 *
 *  <p>When you set up all the bone pointers, the rig xfm will be
 *  computed, an inverse from that to the dst bone will be computed,
 *  and everything will come from that. So the dst bone will maintain
 *  the exact same position in that pose. That makes it easy to author
 *  the bones.</p>" */
class CharIKRod : public CharPollable {
public:
    CharIKRod();
    OBJ_CLASSNAME(CharIKRod);
    OBJ_SET_TYPE(CharIKRod);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual ~CharIKRod();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    bool ComputeRod(Transform &);
    void SyncBones();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharIKRod)
    static void Init() { REGISTER_OBJ_FACTORY(CharIKRod) }

    /** "Left end of the rod" */
    ObjPtr<RndTransformable> mLeftEnd; // 0x8
    /** "Right end of the rod" */
    ObjPtr<RndTransformable> mRightEnd; // 0x14
    /** "Fraction of the way dest is from left (0) to right(1)" */
    float mDestPos; // 0x20
    /** "Take the z axis from this bone rather than from rod end delta" */
    ObjPtr<RndTransformable> mSideAxis; // 0x24
    /** "Force the dest to be vertically upright" */
    bool mVertical; // 0x30
    /** "The bone to set" */
    ObjPtr<RndTransformable> mDest; // 0x34
    Transform mXfm; // 0x40
};

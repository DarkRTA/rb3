#pragma once
#include "char/CharPollable.h"
#include "rndobj/Highlightable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "Does all interpolation for the forearm. Assumes:
 *      <li>foretwist1 and forearm are under upperarm.</li>
 *      <li>foretwist2 is under foretwist1 and that hand is under forearm.</li>
 *      <li>on the left hand offset rotation is usually 90 on the left, and -90 on the
 * right.</li> Feeds the bones when executed." */
class CharForeTwist : public CharPollable, public RndHighlightable {
public:
    CharForeTwist();
    OBJ_CLASSNAME(CharForeTwist);
    OBJ_SET_TYPE(CharForeTwist);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual ~CharForeTwist() {}
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Highlight() {}

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharForeTwist)
    static void Init() { REGISTER_OBJ_FACTORY(CharForeTwist) }

    /** "The hand bone" */
    ObjPtr<RndTransformable> mHand; // 0x10
    /** "The twist2 bone" */
    ObjPtr<RndTransformable> mTwist2; // 0x1c
    /** "Usually 180 for right hand, 0 for left hand" */
    float mOffset; // 0x28
    /** "Biases the angle before dividing by 3, typically 45 on the left hand, -45 on the
     * right." */
    float mBias; // 0x2c
};

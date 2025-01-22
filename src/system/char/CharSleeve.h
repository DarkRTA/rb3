#pragma once
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "char/Character.h"

/** "Animates top and bottom sleeve bones. Both must have the same local xfm when transformed, and the parent bone must point along the X axis.  The local positions of both bones must only have z be non null." */
class CharSleeve : public RndHighlightable, public CharPollable {
public:
    CharSleeve();
    virtual ~CharSleeve();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharSleeve);
    OBJ_SET_TYPE(CharSleeve);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetName(const char*, class ObjectDir*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharSleeve)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharSleeve)
    }

    /** "The sleeve bone" */
    ObjPtr<RndTransformable> mSleeve; // 0x10
    /** "The top sleeve bone, has zero range" */
    ObjPtr<RndTransformable> mTopSleeve; // 0x1c
    Vector3 mPos; // 0x28
    Vector3 mLastPos; // 0x34
    float mLastDT; // 0x40
    /** "Intertia 0-1, .5 is default". Ranges from 0 to 10000. */
    float mInertia; // 0x44
    /** "Force of gravity, 1 is normal" */
    float mGravity; // 0x48
    /** "forward and backward range of the sleeve". Ranges from 0 to 10000. */
    float mRange; // 0x4c
    /** "how much negative length it can go". Ranges from 0 to 10000. */
    float mNegLength; // 0x50
    /** "how much longer it can stretch than its length". Ranges from 0 to 10000. */
    float mPosLength; // 0x54
    /** "how stiff it is for length and range, 1 is max". Ranges from 0 to 1. */
    float mStiffness; // 0x58
    ObjPtr<Character> mMe; // 0x5c
};

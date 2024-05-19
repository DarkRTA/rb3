#ifndef CHAR_CHARIKHAND_H
#define CHAR_CHARIKHAND_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"
#include "char/CharCollide.h"

class CharIKHand : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    CharIKHand();
    virtual ~CharIKHand();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    OBJ_CLASSNAME(CharIKHand);
    OBJ_SET_TYPE(CharIKHand);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    ObjPtr<RndTransformable, ObjectDir> mHand;
    ObjPtr<RndTransformable, ObjectDir> mFinger;
    ObjVector<int> mTargets;
    bool mOrientation;
    bool mStretch;
    bool mScalable;
    bool mMoveElbow;
    float mElbowSwing;
    bool mAlwaysIKElbow; // 0x54
    bool mHandChanged;

    // this range of data is unknown, not referenced in SyncProperty or anything like that
    int unk_filler;
    Vector3 mWorldDst;
    float mInv2ab;
    float mAAPlusBB;
    // end unknown data range

    bool mConstrainWrist; // 0x70
    float mWristRadians; // 0x74
    ObjPtr<CharCollide, ObjectDir> mElbowCollide; // 0x78
    bool mClockwise; // 0x84
};

#endif

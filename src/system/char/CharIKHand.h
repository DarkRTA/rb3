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

    class IKTarget {
    public:
        IKTarget(Hmx::Object* o) : mTarget(o, 0), mExtent(0) {}
        IKTarget(ObjPtr<RndTransformable, ObjectDir> o, float f) ;
        ObjPtr<RndTransformable, ObjectDir> mTarget; // 0x0
        float mExtent; // 0xc
    };

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

    void UpdateHand();
    void IKElbow(RndTransformable*, RndTransformable*);
    void PullShoulder(Vector3&, const Transform&, const Vector3&, float);
    void SetHand(RndTransformable*);
    void MeasureLengths();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    
    ObjPtr<RndTransformable, ObjectDir> mHand; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mFinger; // 0x34
    ObjVector<IKTarget> mTargets; // 0x40
    bool mOrientation; // 0x4c
    bool mStretch; // 0x4d
    bool mScalable; // 0x4e
    bool mMoveElbow; // 0x4f
    float mElbowSwing; // 0x50
    bool mAlwaysIKElbow; // 0x54
    bool mHandChanged; // 0x55

    // this range of data is unknown, not referenced in SyncProperty or anything like that
    Vector3 mWorldDst; // 0x58
    float unk64; // 0x64
    float mInv2ab; // 0x68
    float mAAPlusBB; // 0x6c
    // end unknown data range

    bool mConstrainWrist; // 0x70
    float mWristRadians; // 0x74
    ObjPtr<CharCollide, ObjectDir> mElbowCollide; // 0x78
    bool mClockwise; // 0x84
};

BinStream& operator>>(BinStream&, CharIKHand::IKTarget&);

#endif

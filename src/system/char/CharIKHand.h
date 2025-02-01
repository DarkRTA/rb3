#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"
#include "obj/ObjVector.h"
#include "char/CharCollide.h"

/** "Pins a hand bone to another RndTransformable, bending the elbow to make it reach.
 * Optionally aligns orientations and stretches" */
class CharIKHand : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    class IKTarget {
    public:
        IKTarget(Hmx::Object *o) : mTarget(o), mExtent(0) {}
        IKTarget(ObjPtr<RndTransformable> o, float f);

        /** "Where to move the hand to" */
        ObjPtr<RndTransformable> mTarget; // 0x0
        /** "Distance along the negative z axis of the transform to snap to" */
        float mExtent; // 0xc
    };

    CharIKHand();
    virtual ~CharIKHand();
    virtual void Highlight();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    OBJ_CLASSNAME(CharIKHand);
    OBJ_SET_TYPE(CharIKHand);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    void UpdateHand();
    void IKElbow(RndTransformable *, RndTransformable *);
    void PullShoulder(Vector3 &, const Transform &, const Vector3 &, float);
    void SetHand(RndTransformable *);
    void MeasureLengths();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharIKHand)
    static void Init() { REGISTER_OBJ_FACTORY(CharIKHand) }

    /** "The hand to be moved, must be child of elbow" */
    ObjPtr<RndTransformable> mHand; // 0x28
    /** "If non null, will be the thing that actually hits the target,
     *  the hand will be moved into such a location as to make it hit.
     *  You probably always want to turn on orientation in this case,
     *  as otherwise, the hand will be in a somewhat random orientation,
     *  which will probably mean that the finger will miss the mark." */
    ObjPtr<RndTransformable> mFinger; // 0x34
    /** "Targets for the hand" */
    ObjVector<IKTarget> mTargets; // 0x40
    /** "Orient the hand to the dest" */
    bool mOrientation; // 0x4c
    /** "Stretch the hand to the dest" */
    bool mStretch; // 0x4d
    /** "Recalculate bone length every frame, needed for bones which scale" */
    bool mScalable; // 0x4e
    /** "Moves the elbow and shoulder to position the hand, if false, just teleports the
     * hand" */
    bool mMoveElbow; // 0x4f
    /** "Range to swing the elbow in radians to hit target, better looking suggest .7" */
    float mElbowSwing; // 0x50
    /** "Turn this on to do IK calcs even if weight is 0" */
    bool mAlwaysIKElbow; // 0x54
    bool mHandChanged; // 0x55

    // this range of data is unknown, not referenced in SyncProperty or anything like that
    Vector3 mWorldDst; // 0x58
    float unk64; // 0x64
    float mInv2ab; // 0x68
    float mAAPlusBB; // 0x6c
    // end unknown data range

    /** "Constrain the wrist rotation to be believable" */
    bool mConstrainWrist; // 0x70
    /** "Constrain wrist rotation to this angle (in radians)" */
    float mWristRadians; // 0x74
    /** "Collision sphere that elbow won't enter." */
    ObjPtr<CharCollide> mElbowCollide; // 0x78
    /** "Choose the clockwise solution for the collision detection" */
    bool mClockwise; // 0x84
};

BinStream &operator>>(BinStream &, CharIKHand::IKTarget &);

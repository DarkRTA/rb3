#pragma once
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "rndobj/Trans.h"
#include "char/CharCollide.h"
#include "obj/ObjVector.h"
#include "utl/MemMgr.h"

// forward decs
class Character;
class RndWind;

/** "Hair physics, deals with strands of hair" */
class CharHair : public RndHighlightable, public CharPollable {
public:
    struct Point {
        Point(Hmx::Object *o)
            : bone(o), length(0.0f), collides(o), radius(0.0f), outerRadius(-1.0f) {
            pos.Zero();
            force.Zero();
            lastFriction.Zero();
            lastZ.Zero();
            unk5c.Zero();
        }

        Vector3 pos; // 0x0
        Vector3 force; // 0xc
        Vector3 lastFriction; // 0x18
        Vector3 lastZ; // 0x24
        /** "hair bone we set the transform of" */
        ObjPtr<RndTransformable> bone; // 0x30
        /** "the length of this strand bone" */
        float length; // 0x3c
        /** "things to collide against" */
        ObjPtrList<CharCollide> collides; // 0x40
        /** "collision radius" */
        float radius; // 0x50
        /** "if > radius, is the distance the hair bone should start aligning itself with
         * the collision primitive, so that once touching it, it will be totally flattened
         * against it." */
        float outerRadius; // 0x54
        /** "if >= 0 the base length to the side modified by min_slack and max_slack" */
        float sideLength; // 0x58
        Vector3 unk5c; // 0x5c
    };

    class Strand {
    public:
        Strand(Hmx::Object *);
        ~Strand() {}
        void Load(BinStream &);
        void SetRoot(RndTransformable *);
        void SetAngle(float);
        RndTransformable *Root() { return mRoot; }
        Hmx::Matrix3 &RootMat() { return mRootMat; }
        ObjVector<Point> &Points() { return mPoints; }

        /** "show the points as spheres" */
        bool mShowSpheres; // 0x0
        /** "show the collision shapes" */
        bool mShowCollide; // 0x1
        /** "Show the original pose when hilit, good for adjusting angle to match the
         * pose" */
        bool mShowPose; // 0x2
        /** "The root Trans for the hair strand" */
        ObjPtr<RndTransformable> mRoot; // 0x4
        /** "Angle in degrees of starting flip" */
        float mAngle; // 0x10
        ObjVector<Point> mPoints; // 0x14
        Hmx::Matrix3 mBaseMat; // 0x20
        Hmx::Matrix3 mRootMat; // 0x44
        int mHookupFlags;
    };

    CharHair();
    virtual ~CharHair();
    virtual void Highlight() {}
    OBJ_CLASSNAME(CharHair);
    OBJ_SET_TYPE(CharHair);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual void Enter();
    virtual void SetName(const char *, class ObjectDir *);

    void SimulateInternal(float);
    /** "Re-hookup the hair to the collision volumes" */
    void Hookup();
    void Hookup(ObjPtrList<CharCollide> &);
    /** "Sets this as cloth, all sides true." */
    void SetCloth(bool);
    /** "freeze the current pose for resetting" */
    void FreezePose();
    void FreezePoseRaw();
    void SimulateLoops(int, float);
    void DoReset(int);
    float GetFPS();
    void SimulateZeroTime();
    void SetManagedHookup(bool b) { mManagedHookup = b; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharHair)
    static void Init() { REGISTER_OBJ_FACTORY(CharHair) }

    /** "stiffness of each strand". Ranges from 0 to 1. */
    float mStiffness; // 0x10
    /** "rotational stiffness of each strand". Ranges from 0 to 1. */
    float mTorsion; // 0x14
    /** "Inertia of the hair, zero means none". Ranges from 0 to 1. */
    float mInertia; // 0x18
    /** "Gravity of the hair, one is normal". Ranges from 0 to 10. */
    float mGravity; // 0x1c
    /** "Gravity of the hair, one is normal". Ranges from 0 to 1. */
    float mWeight; // 0x20
    /** "Hair friction against each other". Ranges from 0 to 1. */
    float mFriction; // 0x24
    /** "If using sides, determines how far in it could go" */
    float mMinSlack; // 0x28
    /** "If using sides, determines how far out it could go" */
    float mMaxSlack; // 0x2c
    ObjVector<Strand> mStrands; // 0x30
    int mReset; // 0x3c
    /** "Simulate physics or not" */
    bool mSimulate; // 0x40
    bool mUsePostProc; // 0x41
    ObjPtr<Character> mMe; // 0x44
    /** "wind object to use" */
    ObjPtr<RndWind> mWind; // 0x50
    ObjPtrList<CharCollide> mCollide; // 0x5c
    bool mManagedHookup; // 0x6c
};

BinStream &operator>>(BinStream &bs, CharHair::Point &pt);
BinStream &operator>>(BinStream &bs, CharHair::Strand &strand);

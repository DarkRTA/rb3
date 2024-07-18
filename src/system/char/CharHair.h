#ifndef CHAR_CHARHAIR_H
#define CHAR_CHARHAIR_H
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "rndobj/Trans.h"
#include "char/CharCollide.h"
#include "obj/ObjVector.h"

// forward decs
class Character;
class RndWind;

class CharHair : public RndHighlightable, public CharPollable {
public:

    struct Point {
        Point(Hmx::Object* o) : bone(o, 0), length(0.0f), collides(o, kObjListNoNull), radius(0.0f), outerRadius(-1.0f){
            pos.Zero();
            force.Zero();
            lastFriction.Zero();
            lastZ.Zero();
        }

        Vector3 pos; // 0x0
        Vector3 force; // 0xc
        Vector3 lastFriction; // 0x18
        Vector3 lastZ; // 0x24
        ObjPtr<RndTransformable, ObjectDir> bone; // 0x30
        float length; // 0x3c
        ObjPtrList<CharCollide, ObjectDir> collides; // 0x40
        float radius; // 0x50
        float outerRadius; // 0x54
        float sideLength; // 0x58
        float collide; // 0x5c
        float unk60; // 0x60
        float unk64; // 0x64
    };

    class Strand {
    public:
        Strand(Hmx::Object*);
        ~Strand();
        void Load(BinStream&);
        void SetRoot(RndTransformable*);
        void SetAngle(float);
        RndTransformable* Root(){ return mRoot; }
        Hmx::Matrix3& RootMat(){ return mRootMat; }
        ObjVector<Point>& Points(){ return mPoints; }

        bool mShowSpheres; // 0x0
        bool mShowCollide; // 0x1
        bool mShowPose; // 0x2
        ObjPtr<RndTransformable, ObjectDir> mRoot; // 0x4
        float mAngle; // 0x10
        ObjVector<Point> mPoints; // 0x14
        Hmx::Matrix3 mBaseMat; // 0x20
        Hmx::Matrix3 mRootMat; // 0x44
        int mHookupFlags;
    };

    CharHair();
    virtual ~CharHair();
    virtual void Highlight();
    OBJ_CLASSNAME(CharHair);
    OBJ_SET_TYPE(CharHair);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void SetName(const char*, class ObjectDir*);

    void SimulateInternal(float);
    void Hookup();

    DECLARE_REVS;

    float mStiffness; // 0x10
    float mTorsion; // 0x14
    float mInertia; // 0x18
    float mGravity; // 0x1c
    float mWeight; // 0x20
    float mFriction; // 0x24
    float mMinSlack; // 0x28
    float mMaxSlack; // 0x2c
    ObjVector<Strand> mStrands; // 0x30
    int mReset; // 0x3c
    bool mSimulate; // 0x40
    bool mUsePostProc; // 0x41
    ObjPtr<Character, ObjectDir> mMe; // 0x44
    ObjPtr<RndWind, ObjectDir> mWind; // 0x50
    ObjPtrList<CharCollide, ObjectDir> mCollide; // 0x5c
    bool unk6c; // 0x6c
};

BinStream& operator>>(BinStream& bs, CharHair::Point& pt);
BinStream& operator>>(BinStream& bs, CharHair::Strand& strand);

#endif

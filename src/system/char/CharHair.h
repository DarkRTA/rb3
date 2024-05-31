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

        Vector3 pos;
        Vector3 force;
        Vector3 lastFriction;
        Vector3 lastZ;
        ObjPtr<RndTransformable, ObjectDir> bone;
        float length;
        ObjPtrList<CharCollide, ObjectDir> collides;
        float radius;
        float outerRadius;
        float sideLength;
        float collide;
        float unk64;
    };

    class Strand {
    public:
        Strand(Hmx::Object*);
        ~Strand();
        void Load(BinStream&);
        void SetRoot(RndTransformable*);

        bool mShowSpheres;
        bool mShowCollide;
        bool mShowPose;
        ObjPtr<RndTransformable, ObjectDir> mRoot;
        float mAngle;
        ObjVector<Point> mPoints;
        Hmx::Matrix3 mBaseMat;
        Hmx::Matrix3 mRootMat;
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

    DECLARE_REVS;

    float mStiffness;
    float mTorsion;
    float mInertia;
    float mGravity;
    float mWeight;
    float mFriction;
    float mMinSlack;
    float mMaxSlack;
    ObjVector<Strand> mStrands;
    int mReset;
    bool mSimulate;
    bool mUsePostProc;
    ObjPtr<Character, ObjectDir> mMe;
    ObjPtr<RndWind, ObjectDir> mWind;
    ObjPtrList<CharCollide, ObjectDir> mCollide;
    bool unk6c;
};

BinStream& operator>>(BinStream& bs, CharHair::Point& pt){
    return bs;
}

BinStream& operator>>(BinStream& bs, CharHair::Strand& strand){
    strand.Load(bs);
}

#endif

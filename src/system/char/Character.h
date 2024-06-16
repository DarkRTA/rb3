#ifndef CHAR_CHARACTER_H
#define CHAR_CHARACTER_H
#include "rndobj/Dir.h"
#include "obj/ObjVector.h"
#include "rndobj/Group.h"
#include "math/Sphere.h"

class CharacterTest; // forward dec
class Waypoint;
class RndCam;
class CharInterest;
class CharEyes;

class Character : public RndDir {
public:

    enum DrawMode {
        kCharDrawNone,
        kCharDrawOpaque,
        kCharDrawTranslucent,
        kCharDrawAll
    };

    class Lod {
    public:
        Lod(Hmx::Object*);
        Lod(const Lod&);
        Lod& operator=(const Lod&);
        ~Lod(){}

        float mScreenSize;
        ObjPtr<RndGroup, ObjectDir> mGroup;
        ObjPtr<RndGroup, ObjectDir> mGroup2;
    };

    Character();
    OBJ_CLASSNAME(Character);
    OBJ_SET_TYPE(Character);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~Character();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void AddedObject(Hmx::Object*);
    virtual void RemovingObject(Hmx::Object*);

    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void DrawShowing();
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void Teleport(Waypoint*);
    virtual void PreSave(BinStream&);
    virtual void CalcBoundingSphere();
    virtual float ComputeScreenSize(RndCam*);
    virtual void DrawLodOrShadow(int, DrawMode);
    virtual CharEyes* GetEyes();
    virtual bool ValidateInterest(CharInterest*, ObjectDir*){ return true; }
    virtual bool SetFocusInterest(CharInterest*, int);
    virtual void SetInterestFilterFlags(int);
    virtual void ClearInterestFilterFlags();

    void UnhookShadow();

    ObjVector<Lod> mLods; // 0x18c
    int mLastLod;
    int mMinLod;
    ObjPtr<RndGroup, ObjectDir> mShadow;
    ObjPtr<RndGroup, ObjectDir> mTransGroup;
    int mDriver; // CharDriver*
    bool mSelfShadow;
    bool mSpotCutout;
    bool mFloorShadow;
    ObjOwnerPtr<RndTransformable, ObjectDir> mSphereBase;
    Sphere mBounding;
    std::vector<int> mShadowBones;
    int mPollState;
    CharacterTest* mTest;
    bool mFrozen;
    DrawMode mDrawMode; // 0x1f0
    bool unk1f4;
    Symbol mInterestToForce;
    ObjPtr<RndEnviron, ObjectDir> unk1fc;
    int unk208;
    bool mDebugDrawInterestObjects;
};

#endif

// enum PollState {
//     kCharCreated = 0,
//     kCharSyncObject = 1,
//     kCharEntered = 2,
//     kCharPolled = 3,
//     kCharExited = 4,
// };
// class Character : public RndDir {
//     // total size: 0x2A0
// protected:
//     class ObjVector mLods; // offset 0x1F4, size 0x10
//     int mLastLod; // offset 0x204, size 0x4
//     int mMinLod; // offset 0x208, size 0x4
//     class ObjPtr mShadow; // offset 0x20C, size 0xC
//     class CharDriver * mDriver; // offset 0x218, size 0x4
//     class CharWalk * mWalk; // offset 0x21C, size 0x4
//     unsigned char mSelfShadow; // offset 0x220, size 0x1
//     unsigned char mSpotCutout; // offset 0x221, size 0x1
//     unsigned char mFloorShadow; // offset 0x222, size 0x1
//     class ObjOwnerPtr mSphereBase; // offset 0x224, size 0xC
//     class Sphere mBounding; // offset 0x230, size 0x20
//     class vector mShadowBones; // offset 0x250, size 0xC
//     enum PollState mPollState; // offset 0x25C, size 0x4
//     class CharacterTest * mTest; // offset 0x260, size 0x4
// };
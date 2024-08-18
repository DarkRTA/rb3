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
class CharDriver;
class CharServoBone;

class ShadowBone : public RndTransformable {
public:
    ShadowBone() : mParent(this, 0) {}
    virtual ~ShadowBone(){}

    ObjPtr<RndTransformable, ObjectDir> mParent;
};

class Character : public RndDir {
public:

    enum DrawMode {
        kCharDrawNone,
        kCharDrawOpaque,
        kCharDrawTranslucent,
        kCharDrawAll
    };

    enum PollState {
        kCharCreated = 0,
        kCharSyncObject = 1,
        kCharEntered = 2,
        kCharPolled = 3,
        kCharExited = 4,
    };

    class Lod {
    public:
        Lod(Hmx::Object*);
        Lod(const Lod&);
        Lod& operator=(const Lod&);
        ~Lod(){}

        RndGroup* Group(){ return mGroup; }
        float ScreenSize() const { return mScreenSize; }
        void SetScreenSize(float size){ mScreenSize = size; }

        float mScreenSize; // 0x0
        ObjPtr<RndGroup, ObjectDir> mGroup; // 0x4
        ObjPtr<RndGroup, ObjectDir> mTransGroup; // 0x10
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
    ShadowBone* AddShadowBone(RndTransformable*);
    void SyncShadow();
    void RemoveFromPoll(RndPollable*);
    void CopyBoundingSphere(Character*);
    void RepointSphereBase(ObjectDir*);
    void FindInterestObjects(ObjectDir*);
    void SetFocusInterest(Symbol, int);
    void EnableBlinks(bool, bool);
    void SetDebugDrawInterestObjects(bool);
    void SetSphereBase(RndTransformable*);
    void SetShadow(RndGroup*);
    CharServoBone* BoneServo();
    void SetInterestObjects(const ObjPtrList<CharInterest, ObjectDir>&, ObjectDir*);
    void ForceBlink();
    void SetDrawMode(DrawMode m){ mDrawMode = m; }

    DataNode OnPlayClip(DataArray*);
    DataNode OnCopyBoundingSphere(DataArray*);
    DataNode OnGetCurrentInterests(DataArray*);

    static void Init();
    static void Terminate();
    static void Register(){ REGISTER_OBJ_FACTORY(Character); }

    NEW_OBJ(Character);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjVector<Lod> mLods; // 0x18c
    int mLastLod; // 0x198
    int mMinLod; // 0x19c
    ObjPtr<RndGroup, ObjectDir> mShadow; // 0x1a0
    ObjPtr<RndGroup, ObjectDir> mTransGroup; // 0x1ac
    CharDriver* mDriver; // 0x1b8
    bool mSelfShadow; // 0x1bc
    bool mSpotCutout; // 0x1bd
    bool mFloorShadow; // 0x1be
    ObjOwnerPtr<RndTransformable, ObjectDir> mSphereBase; // 0x1c0
    Sphere mBounding; // 0x1cc
    std::vector<ShadowBone*> mShadowBones; // 0x1dc
    PollState mPollState; // 0x1e4
    CharacterTest* mTest; // 0x1e8
    bool mFrozen; // 0x1ec
    DrawMode mDrawMode; // 0x1f0
    bool unk1f4; // 0x1f4
    Symbol mInterestToForce; // 0x1f8
    ObjPtr<RndEnviron, ObjectDir> unk1fc; // 0x1fc
    int unk208; // 0x208
    bool mDebugDrawInterestObjects; // 0x20c
};

#endif
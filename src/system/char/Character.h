#pragma once
#include "rndobj/Dir.h"
#include "obj/ObjVector.h"
#include "rndobj/Group.h"
#include "math/Sphere.h"
#include "rndobj/Trans.h"

class CharacterTest; // forward dec
class Waypoint;
class RndCam;
class CharInterest;
class CharEyes;
class CharDriver;
class CharServoBone;

class ShadowBone : public RndTransformable {
public:
    ShadowBone() : mParent(this) {}
    virtual ~ShadowBone() {}

    RndTransformable *Parent() const { return mParent; }
    void SetParent(RndTransformable *parent) { mParent = parent; }

    ObjPtr<RndTransformable> mParent; // 0x90
};

/** "Base class for Character objects. Contains Geometry,
 *  Outfit Loaders, and LOD + Sphere concepts." */
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
        Lod(Hmx::Object *);
        Lod(const Lod &);
        Lod &operator=(const Lod &);
        ~Lod() {}

        RndGroup *Group() { return mGroup; }
        RndGroup *TransGroup() { return mTransGroup; }
        float ScreenSize() const { return mScreenSize; }
        void SetScreenSize(float size) { mScreenSize = size; }

        /** "when the unit sphere centered on the bounding sphere is smaller than this
         * screen height fraction, it will draw the next lod". Ranges from 0 to 10000. */
        float mScreenSize; // 0x0
        /** "group to show at this LOD.  Drawables not in any lod group will be drawn at
         * every LOD" */
        ObjPtr<RndGroup> mGroup; // 0x4
        /** "translucency group to show at this LOD.  Drawables in it are guaranteed to be
         * drawn last." */
        ObjPtr<RndGroup> mTransGroup; // 0x10
    };

    Character();
    OBJ_CLASSNAME(Character);
    OBJ_SET_TYPE(Character);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual ~Character();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void AddedObject(Hmx::Object *);
    virtual void RemovingObject(Hmx::Object *);

    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere &, bool);
    virtual void DrawShowing();
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void Teleport(Waypoint *);
    virtual void PreSave(BinStream &);
    /** "Calculates a new bounding sphere" */
    virtual void CalcBoundingSphere();
    virtual float ComputeScreenSize(RndCam *);
    virtual void DrawLodOrShadow(int, DrawMode);
    virtual CharEyes *GetEyes();
    virtual bool ValidateInterest(CharInterest *, ObjectDir *) { return true; }
    virtual bool SetFocusInterest(CharInterest *, int);
    virtual void SetInterestFilterFlags(int);
    virtual void ClearInterestFilterFlags();

    void UnhookShadow();
    ShadowBone *AddShadowBone(RndTransformable *);
    void SyncShadow();
    void RemoveFromPoll(RndPollable *);
    void CopyBoundingSphere(Character *);
    void RepointSphereBase(ObjectDir *);
    void FindInterestObjects(ObjectDir *);
    bool SetFocusInterest(Symbol, int);
    void EnableBlinks(bool, bool);
    void SetDebugDrawInterestObjects(bool);
    void SetSphereBase(RndTransformable *);
    void SetShadow(RndGroup *);
    CharServoBone *BoneServo();
    void SetInterestObjects(const ObjPtrList<CharInterest> &, ObjectDir *);
    void ForceBlink();
    void DrawLod(int);
    void DrawShadow(const Transform &, const Plane &);

    void SetDrawMode(DrawMode m) { mDrawMode = m; }
    bool Teleported() const { return mTeleported; }
    PollState GetPollState() const { return mPollState; }
    int MinLod() const { return mMinLod; }
    int LastLod() const { return mLastLod; }
    void SetMinLod(int lod) { mMinLod = lod; }
    CharDriver *GetDriver() const { return mDriver; }
    void SetTeleported(bool b) { mTeleported = b; }
    void SetSelfShadow(bool b) { mSelfShadow = b; }

    DataNode OnPlayClip(DataArray *);
    DataNode OnCopyBoundingSphere(DataArray *);
    DataNode OnGetCurrentInterests(DataArray *);

    static void Init();
    static void Terminate();
    static void Register() { REGISTER_OBJ_FACTORY(Character); }

    NEW_OBJ(Character);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjVector<Lod> mLods; // 0x18c
    int mLastLod; // 0x198
    int mMinLod; // 0x19c
    /** "Group containing shadow geometry" */
    ObjPtr<RndGroup> mShadow; // 0x1a0
    /** "translucency group to show independent of lod.  Drawables in it are guaranteed to
     * be drawn last." */
    ObjPtr<RndGroup> mTransGroup; // 0x1ac
    CharDriver *mDriver; // 0x1b8
    /** "Whether this character should be self-shadowed." */
    bool mSelfShadow; // 0x1bc
    bool mSpotCutout; // 0x1bd
    bool mFloorShadow; // 0x1be
    /** "Base for bounding sphere, such as bone_pelvis.mesh" */
    ObjOwnerPtr<RndTransformable> mSphereBase; // 0x1c0
    /** "bounding sphere for the character, fixed" */
    Sphere mBounding; // 0x1cc
    std::vector<ShadowBone *> mShadowBones; // 0x1dc
    PollState mPollState; // 0x1e4
    /** "Test Character by animating it" */
    CharacterTest *mTest; // 0x1e8
    /** "if true, is frozen in place, no polling happens" */
    bool mFrozen; // 0x1ec
    DrawMode mDrawMode; // 0x1f0
    bool mTeleported; // 0x1f4
    /** "select an interest object here and select 'force_interest' below to force the
     * character to look at it." */
    Symbol mInterestToForce; // 0x1f8
    ObjPtr<RndEnviron> unk1fc; // 0x1fc
    Vector3 *unk208; // 0x208
#ifdef MILO_DEBUG
    bool mDebugDrawInterestObjects; // 0x20c
#endif
};

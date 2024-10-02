#pragma once
#include "world/CameraShot.h"
#include "rndobj/Env.h"
#include "math/Mtx.h"

class Character;

class OldTrigger {
public:
    float frame; // 0x0
    Symbol trigger; // 0x4
};

class BandCamShot : public CamShot {
public:
    class Target {
    public:
        Target(Hmx::Object* o) : mFastForward(0), mEnvOverride(o, 0), mForceLod(-1), mTeleport(1),
            mReturn(1), mSelfShadow(1), unk1(0), unk2(1), mHide(0) {
            mXfm.Reset();
        }
        void Store(BandCamShot*);
        void UpdateTarget(Symbol, BandCamShot*);

        Symbol mTarget; // 0x0
        TransformNoScale mXfm; // 0x4
        Symbol mAnimGroup; // 0x18
        float mFastForward; // 0x1c
        Symbol mForwardEvent; // 0x20
        ObjPtr<RndEnviron, ObjectDir> mEnvOverride; // 0x24
        // 0x30 bitfields
        int mForceLod : 4;
        int mTeleport : 2;
        int mReturn : 2;
        int mSelfShadow : 2;
        int unk1 : 2;
        int unk2 : 2;
        int mHide : 2;
    };

    // size 0x20
    class TargetCache {
    public:
        Symbol unk0;
        RndTransformable* unk4;
        int unk8;
        TransformNoScale unkc;
    };

    BandCamShot();
    OBJ_CLASSNAME(BandCamShot);
    OBJ_SET_TYPE(BandCamShot);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~BandCamShot(){}
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void SetPreFrame(float, float);
    virtual CamShot* CurrentShot(){ return mCurShot; }
    virtual bool CheckShotStarted();
    virtual bool CheckShotOver(float);

    RndTransformable* FindTarget(Symbol, bool);
    void CheckNextShots();
    void ResetNextShot();
    float GetTotalDuration();
    float GetTotalDurationSeconds();
    void Store();
    void View();
    void Freeze();
    void FreezeChar(Character*, bool);
    void ViewFreeze();
    BandCamShot* InitialShot();
    int GetNumShots();
    bool IterateNextShot();
    void SetFrameEx(float, float);
    void AnimateShot(float, float);
    void ListNextShots(std::list<BandCamShot*>&);
    static void DeleteTargetCache(std::list<TargetCache>::iterator);
    std::list<TargetCache>::iterator CreateTargetCache(Symbol);

    DataNode OnTestDelta(DataArray*);
    DataNode AddTarget(DataArray*);
    DataNode OnAllowableNextShots(const DataArray*);
    DataNode OnListAllNextShots(const DataArray*);
    DataNode OnListTargets(const DataArray*);
    DataNode OnListAnimGroups(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static std::list<TargetCache> sCache;
    static int sHideAllCharactersHack;

    ObjVector<Target> mTargets; // 0x124
    int mMinTime; // 0x130
    int mMaxTime; // 0x134
    float mZeroTime; // 0x138
    ObjPtrList<BandCamShot, ObjectDir> mNextShots; // 0x13c
    ObjPtrList<BandCamShot, ObjectDir>::iterator mShotIter; // 0x14c
    ObjPtr<BandCamShot, ObjectDir> mCurShot; // 0x150
    float unk15c;
    float unk160;
    float unk164;
    bool unk168;
    bool unk169;
    bool unk16a;
    bool mAnimsDuringNextShots; // 0x16b
};
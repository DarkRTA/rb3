#pragma once
#include "world/CameraShot.h"
#include "rndobj/Env.h"
#include "math/Mtx.h"

class BandCamShot : public CamShot {
public:
    class Target {
    public:
        Target(Hmx::Object*);
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

    class TargetCache {
    public:
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
    void ViewFreeze();
    BandCamShot* InitialShot();
    int GetNumShots();

    DataNode OnTestDelta(DataArray*);
    DataNode AddTarget(DataArray*);
    DataNode OnAllowableNextShots(DataArray*);
    DataNode OnListAllNextShots(const DataArray*);
    DataNode OnListTargets(const DataArray*);
    DataNode OnListAnimGroups(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static std::list<TargetCache> sCache;

    ObjVector<Target> mTargets; // 0x124
    int mMinTime; // 0x130
    int mMaxTime; // 0x134
    float mZeroTime; // 0x138
    ObjPtrList<BandCamShot, ObjectDir> mNextShots; // 0x13c
    int unk14c; // 0x14c - some struct
    ObjPtr<BandCamShot, ObjectDir> mCurShot; // 0x150
    float unk15c;
    float unk160;
    float unk164;
    bool unk168;
    bool unk169;
    bool unk16a;
    bool mAnimsDuringNextShots; // 0x16b
};
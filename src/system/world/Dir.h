#pragma once
#include "ui/PanelDir.h"
#include "obj/ObjList.h"
#include "world/CameraManager.h"
#include "world/LightPresetManager.h"
#include "world/LightPreset.h"
#include "world/LightHue.h"

class CamShot;
class WorldCrowd;

/**
 * @brief An ObjectDir dedicated to holding world objects.
 * Original _objects description:
 * "A WorldDir contains world objects."
 */
class WorldDir : public PanelDir {
public:

    class PresetOverride {
    public:
        PresetOverride(Hmx::Object* o) : preset(o), hue(o) {}
        void Sync(bool);

        /** "Subdir preset to modify" */
        ObjPtr<LightPreset> preset; // 0x0
        /** "Hue texture to use" */
        ObjPtr<LightHue> hue; // 0xc
    };

    class BitmapOverride {
    public:
        BitmapOverride(Hmx::Object* o) : original(o), replacement(o) {}
        void Sync(bool);

        /** "Subdir texture to replace" */
        ObjPtr<RndTex> original; // 0x0
        /** "Curdir texture to replace with" */
        ObjPtr<RndTex> replacement; // 0xc
    };

    class MatOverride {
    public:
        MatOverride(Hmx::Object* o) : mesh(o), mat(o), mat2(o) {}
        void Sync(bool);

        /** "Subdir mesh to modify" */
        ObjPtr<RndMesh> mesh; // 0x0
        /** "Curdir material to set" */
        ObjPtr<RndMat> mat; // 0xc
        ObjPtr<RndMat> mat2; // 0x18
    };

    WorldDir();
    OBJ_CLASSNAME(WorldDir);
    OBJ_SET_TYPE(WorldDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~WorldDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void DrawShowing();
    virtual void Poll();
    virtual void Enter();
    virtual bool DrawShowingBudget(float);

    void ClearDeltas();
    void AccumulateDeltas(float*);
    void ExtendDeltas();
    void RestoreDeltas(float*);
    void SyncHides(bool);
    void SyncBitmaps(bool);
    void SyncMats(bool);
    void SyncPresets(bool);
    void SyncCamShots(bool);
    void SyncHUD();
    void DrawSplitWorld();
    void SetCrowds(ObjVector<CamShotCrowd>&);
    CameraManager& CamManager(){ return mCameraManager; }

    DECLARE_REVS;

    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(WorldDir)
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(WorldDir)
    }

    ObjList<PresetOverride> mPresetOverrides; // 0x1d8
    ObjList<BitmapOverride> mBitmapOverrides; // 0x1e4
    ObjList<MatOverride> mMatOverrides; // 0x1f0
    /** "Subdir objects to hide" */
    ObjPtrList<RndDrawable> mHideOverrides; // 0x1fc
    /** "Subdir camshots to inhibit" */
    ObjPtrList<CamShot> mCamShotOverrides; // 0x20c
    /** "Things to show when ps3_per_pixel on CamShot" */
    ObjPtrList<RndDrawable> mPS3PerPixelShows; // 0x21c
    /** "Things to hide when ps3_per_pixel on CamShot" */
    ObjPtrList<RndDrawable> mPS3PerPixelHides; // 0x22c
    ObjPtrList<WorldCrowd> mCrowds; // 0x23c
    RndMat* mGlowMat; // 0x24c
    /** "HUD Preview Dir" */
    FilePath mFakeHudFilename; // 0x250
    /** "hud to be drawn last" */
    RndDir* mFakeHudDir; // 0x25c
    /** "Whether to draw the HUD preview" */
    bool mShowFakeHud; // 0x260
    ObjPtr<RndDir> mHud; // 0x264
    CameraManager mCameraManager; // 0x270
    LightPresetManager mPresetManager; // 0x2a4
    bool mEchoMsgs; // 0x2f4
    float mDeltaSincePoll[4]; // 0x2f8
    bool mFirstPoll; // 0x308
    bool mPollCamera; // 0x309
    ObjPtr<LightPreset> mTestPreset1; // 0x30c
    ObjPtr<LightPreset> mTestPreset2; // 0x318
    float mTestAnimationTime; // 0x324
    float mLastRndTimeWorld; // 0x328
    float mLastRndTimeChar; // 0x32c
    RndDrawable** mDrawItr; // 0x330
};

BinStream& operator>>(BinStream&, WorldDir::BitmapOverride&);

inline BinStream& operator>>(BinStream& bs, WorldDir::MatOverride& o){
    bs >> o.mesh >> o.mat;
    return bs;
}

inline BinStream& operator>>(BinStream& bs, WorldDir::PresetOverride& o){
    bs >> o.preset >> o.hue;
    return bs;
}

extern WorldDir* TheWorld;
void SetTheWorld(WorldDir*);

#ifndef WORLD_DIR_H
#define WORLD_DIR_H
#include "ui/PanelDir.h"
#include "obj/ObjList.h"
#include "world/CameraManager.h"
#include "world/LightPresetManager.h"
#include "world/LightPreset.h"
#include "world/LightHue.h"

class CamShot;
class WorldCrowd;

class WorldDir : public PanelDir {
public:

    class PresetOverride {
    public:
        PresetOverride(Hmx::Object* o) : preset(o), hue(o) {}
        void Sync(bool);

        ObjPtr<LightPreset, ObjectDir> preset; // 0x0
        ObjPtr<LightHue, ObjectDir> hue; // 0xc
    };

    class BitmapOverride {
    public:
        BitmapOverride(Hmx::Object* o) : original(o), replacement(o) {}
        void Sync(bool);

        ObjPtr<RndTex, ObjectDir> original; // 0x0
        ObjPtr<RndTex, ObjectDir> replacement; // 0xc
    };

    class MatOverride {
    public:
        MatOverride(Hmx::Object* o) : mesh(o), mat(o), mat2(o) {}
        void Sync(bool);

        ObjPtr<RndMesh, ObjectDir> mesh; // 0x0
        ObjPtr<RndMat, ObjectDir> mat; // 0xc
        ObjPtr<RndMat, ObjectDir> mat2; // 0x18
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

    ObjList<PresetOverride> mPresetOverrides; // 0x1d8 - WorldDir::PresetOverride
    ObjList<BitmapOverride> mBitmapOverrides; // 0x1e4 - WorldDir::BitmapOverride
    ObjList<MatOverride> mMatOverrides; // 0x1f0 - WorldDir::MatOverride
    ObjPtrList<RndDrawable, ObjectDir> mHideOverrides; // 0x1fc
    ObjPtrList<CamShot, ObjectDir> mCamShotOverrides; // 0x20c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelShows; // 0x21c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelHides; // 0x22c
    ObjPtrList<WorldCrowd, ObjectDir> mCrowds; // 0x23c
    RndMat* mGlowMat; // 0x24c
    FilePath mFakeHudFilename; // 0x250
    RndDir* mFakeHudDir; // 0x25c
    bool mShowFakeHud; // 0x260
    ObjPtr<RndDir, ObjectDir> mHud; // 0x264
    CameraManager mCameraManager; // 0x270
    LightPresetManager mPresetManager; // 0x2a4
    bool mEchoMsgs; // 0x2f4
    float mDeltaSincePoll[4]; // 0x2f8
    bool unk308;
    bool unk309;
    ObjPtr<LightPreset, ObjectDir> mTestPreset1; // 0x30c
    ObjPtr<LightPreset, ObjectDir> mTestPreset2; // 0x318
    float mTestAnimationTime; // 0x324
    int unk328;
    int unk32c;
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

#endif

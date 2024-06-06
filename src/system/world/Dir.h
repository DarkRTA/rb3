#ifndef WORLD_DIR_H
#define WORLD_DIR_H
#include "ui/PanelDir.h"
#include "obj/ObjList.h"
#include "world/CameraManager.h"
#include "world/LightPresetManager.h"

class CamShot;
class WorldCrowd;
class LightPreset;

class WorldDir : public PanelDir {
public:
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

    NEW_OBJ(WorldDir)
    static void Init();

    ObjList<int> mPresetOverrides; // 0x1d8 - WorldDir::PresetOverride
    ObjList<int> mBitmapOverrides; // 0x1e4 - WorldDir::BitmapOverride
    ObjList<int> mMatOverrides; // 0x1f0 - WorldDir::MatOverride
    ObjPtrList<RndDrawable, ObjectDir> mHideOverrides; // 0x1fc
    ObjPtrList<CamShot, ObjectDir> mCamShotOverrides; // 0x20c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelShows; // 0x21c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelHides; // 0x22c
    ObjPtrList<WorldCrowd, ObjectDir> mCrowds; // 0x23c
    RndMat* mGlowMat; // 0x24c
    FilePath mFakeHudFilename; // 0x250
    int unk25c; // 0x25c
    bool mShowFakeHud; // 0x260
    ObjPtr<RndDir, ObjectDir> mHud; // 0x264
    CameraManager mCameraManager; // 0x270
    LightPresetManager mPresetManager; // 0x2a4
    bool mEchoMsgs; // 0x2f4
    float unk2f8[4]; // 0x2f8
    bool unk308;
    bool unk309;
    ObjPtr<LightPreset, ObjectDir> mTestPreset1; // 0x30c
    ObjPtr<LightPreset, ObjectDir> mTestPreset2; // 0x318
    float mTestAnimationTime; // 0x324
    int unk328;
    int unk32c;
    int unk330;
};

#endif

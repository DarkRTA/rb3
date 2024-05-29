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

    ObjList<int> mPresetOverrides; // 0x1d8 - WorldDir::PresetOverride
    ObjList<int> mBitmapOverrides; // 0x1e4 - WorldDir::BitmapOverride
    ObjList<int> mMatOverrides; // 0x1f0 - WorldDir::MatOverride
    ObjPtrList<RndDrawable, ObjectDir> mHideOverrides; // 0x1fc
    ObjPtrList<CamShot, ObjectDir> mCamShotOverrides; // 0x20c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelShows; // 0x21c
    ObjPtrList<RndDrawable, ObjectDir> mPS3PerPixelHides; // 0x22c
    ObjPtrList<WorldCrowd, ObjectDir> mCrowds; // 0x23c
    FilePath mFakeHudFilename; // 0x250
    int unk25c; // 0x25c
    bool mShowFakeHud; // 0x260
    ObjPtr<RndDir, ObjectDir> unk264;
    CameraManager mCameraManager; // 0x270
    LightPresetManager mPresetManager; // 0x2a4
    bool unk2f4; // 0x2f4
    float unk2f8[4]; // 0x2f8
    bool unk308;
    bool unk309;
    ObjPtr<LightPreset, ObjectDir> unk30c; // 0x30c
    ObjPtr<LightPreset, ObjectDir> unk318; // 0x318
    float unk324;
};

#endif

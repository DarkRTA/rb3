#include "world/Dir.h"
#include "world/Crowd.h"
#include "world/LightPreset.h"
#include "rndobj/Mat.h"

WorldDir::WorldDir() : mPresetOverrides(this), mBitmapOverrides(this), mMatOverrides(this), mHideOverrides(this, kObjListNoNull), mCamShotOverrides(this, kObjListNoNull),
    mPS3PerPixelShows(this, kObjListNoNull), mPS3PerPixelHides(this, kObjListNoNull), mCrowds(this, kObjListNoNull), unk25c(0), mShowFakeHud(0), mHud(this, 0),
    mCameraManager(this), mPresetManager(this), mEchoMsgs(0), unk308(0), unk309(1), mTestPreset1(this, 0), mTestPreset2(this, 0), mTestAnimationTime(10.0f) {
    mGlowMat = Hmx::Object::New<RndMat>();
}
#include "world/LightPreset.h"
#include "world/Spotlight.h"

LightPreset::LightPreset() : mKeyframes(this), mPlatformOnly(0), mSelectTriggers(this, kObjListNoNull), mLegacyFadeIn(0.0f), mLooping(0), mManual(0), mLocked(0),
    unk5c(this), unk80(0), unk84(-1.0f), unk88(0.0f), unk8c(0.0f), unk90(0), unk94(-1), unk98(0.0f), unk9c(0.0f), mHue(0) {

}
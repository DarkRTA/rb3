#include "world/LightPreset.h"
#include "world/Spotlight.h"
#include "world/SpotlightDrawer.h"
#include "rndobj/Env.h"

INIT_REVS(LightPreset)

LightPreset::LightPreset() : mKeyframes(this), mPlatformOnly(0), mSelectTriggers(this, kObjListNoNull), mLegacyFadeIn(0.0f), mLooping(0), mManual(0), mLocked(0),
    unk5c(this), unk80(0), unk84(-1.0f), unk88(0.0f), unk8c(0.0f), unk90(0), unk94(-1), unk98(0.0f), unk9c(0.0f), mHue(0) {

}

#pragma push
#pragma dont_inline on
LightPreset::~LightPreset(){ Clear(); }
#pragma pop

void LightPreset::Save(BinStream& bs){
    MILO_FAIL("Attempting to save in Wii");
}

#pragma push
#pragma dont_inline on
BEGIN_LOADS(LightPreset)
    AutoLoading al;
    Clear();
    LOAD_REVS(bs)
    ASSERT_REVS(0x15, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev != 0xE){
        LOAD_SUPERCLASS(RndAnimatable);
        bs >> mKeyframes;
    }
    else {
        mKeyframes.resize(1);
        mKeyframes[0].LoadP9(bs);
    }
    char buf[0x80];
    int spotlightcount;
    bs >> spotlightcount;
    mSpotlights.resize(spotlightcount);
    for(int i = 0; i != mSpotlights.size(); i++){
        bs.ReadString(buf, 0x80);
        mSpotlights[i] = Dir()->Find<Spotlight>(buf, false);
        if(mSpotlights[i]) mSpotlights[i]->AddRef(this);
    }
    int envcount;
    bs >> envcount;
    mEnvironments.resize(envcount);
    for(int i = 0; i != mEnvironments.size(); i++){
        bs.ReadString(buf, 0x80);
        mEnvironments[i] = Dir()->Find<RndEnviron>(buf, false);
        if(mEnvironments[i]) mEnvironments[i]->AddRef(this);
    }
    int lightcount;
    bs >> lightcount;
    mLights.resize(lightcount);
    for(int i = 0; i != mLights.size(); i++){
        bs.ReadString(buf, 0x80);
        mLights[i] = Dir()->Find<RndLight>(buf, false);
        if(mLights[i]) mLights[i]->AddRef(this);
    }
    if(gRev < 5){
        bool b;
        bs >> b;
        if(b){
            Keyframe k(this);
            bs >> k;
        }
    }
    if(gRev != 0xE) bs >> mLooping;
    bs >> mCategory;
    if(gRev != 0xE && gRev < 0x11){
        std::vector<Symbol> symvec;
        bs >> symvec;
        if(symvec.size() != 0){
            if(symvec[0] != ""){
                mCategory = symvec[0];
            }
        }
    }
    String str(mCategory.Str());
    str.ToLower();
    mCategory = Symbol(str.c_str());
    if(gRev < 7){
        String str154;
        bs >> str154;
        if(!str154.empty()){
            MILO_WARN("%s: %s", Name(), str154);
        }
    }
    else if(gRev < 0x15){
        ObjPtr<EventTrigger, ObjectDir> trigPtr(this, 0);
        bs >> trigPtr;
        if(trigPtr) mSelectTriggers.push_back(trigPtr);
    }
    else bs >> mSelectTriggers;
    if(gRev < 5){
        String strdummy; bs >> strdummy;
    }
    if(gRev != 0xE){
        bs >> mLegacyFadeIn;
        int dummy;
        if(gRev != 0 && gRev < 0x11) bs >> dummy;
        if(gRev - 3 < 0xE) bs >> dummy;
    }
    if(gRev > 3){
        if(gRev != 0xE) bs >> mManual;
        bs >> mLocked;
    }
    if(gRev > 0xC) bs >> mPlatformOnly;
    if(gRev > 9){
        int sdrawercount;
        bs >> sdrawercount;
        mSpotlightDrawers.resize(sdrawercount);
        for(int i = 0; i < mSpotlightDrawers.size(); i++){
            bs.ReadString(buf, 0x80);
            mSpotlightDrawers[i] = Dir()->Find<SpotlightDrawer>(buf, false);
            if(mSpotlightDrawers[i]) mSpotlightDrawers[i]->AddRef(this);
        }
    }
    if(gRev == 0xB){
        int dummy;
        for(int i = 0; i < 8; i++) bs >> dummy;
    }
    unk5c.resize(mSpotlights.size());
    unk68.resize(mEnvironments.size(), EnvironmentEntry());
    unk70.resize(mLights.size(), EnvLightEntry());
    unk78.resize(mSpotlightDrawers.size(), SpotlightDrawerEntry());
    for(int i = 0; i < mSpotlights.size(); i++){
        if(!mSpotlights[i] || !mSpotlights[i]->GetAnimateFromPreset()){
            RemoveSpotlight(i);
            i--;
        }
    }
    for(int i = 0; i < mEnvironments.size(); i++){
        if(!mEnvironments[i] || !mEnvironments[i]->GetAnimateFromPreset()){
            RemoveEnvironment(i);
            i--;
        }
    }
    for(int i = 0; i < mLights.size(); i++){
        if(!mLights[i] || !mLights[i]->GetAnimateFromPreset()){
            RemoveLight(i);
            i--;
        }
    }
    for(int i = 0; i < mSpotlightDrawers.size(); i++){
        if(!mSpotlightDrawers[i]){
            RemoveSpotlightDrawer(i);
            i--;
        }
    }
    SyncNewSpotlights();
    CacheFrames();
    sLoading = 0;
END_LOADS
#pragma pop

void LightPreset::Keyframe::Load(BinStream& bs){
    MILO_ASSERT(gRev != 14, 0x64A);
}

// void __thiscall LightPreset::Keyframe::Load(Keyframe *this,BinStream *param_1)

// {
//   char *pcVar1;
//   String SStack_18;
  
//   if (LightPreset::gRev == 0xe) {
//     pcVar1 = ::MakeString(kAssertStr,s_LightPreset.cpp_80c1b7ae,0x64a,s_gRev_!=_14_80c1ba46);
//     Debug::Fail((Debug *)TheDebug,pcVar1);
//   }
//   BinStream::ReadEndian(param_1,this + 0x60,4);
//   BinStream::ReadEndian(param_1,this + 100,4);
//   ::__rs(param_1,(ObjVector<> *)this);
//   ::__rs(param_1,(vector<> *)(this + 0xc));
//   ::__rs(param_1,(vector<> *)(this + 0x14));
//   if (LightPreset::gRev > 5) {
//     String::String(&SStack_18);
//     BinStream::operator_>>(param_1,(String *)&SStack_18);
//     String::~String(&SStack_18);
//   }
//   if (LightPreset::gRev > 9) {
//     ::__rs(param_1,(vector<> *)(this + 0x1c));
//   }
//   if (LightPreset::gRev > 0x11) {
//     ::__rs(param_1,(ObjPtr *)(this + 0x24));
//   }
//   if (LightPreset::gRev > 0x13) {
//     ::__rs(param_1,(ObjPtrList *)(this + 0x30));
//   }
//   if (LightPreset::gRev > 0xb) {
//     LoadStageKit(this,param_1);
//   }
//   return;
// }

LightPreset::SpotlightEntry::SpotlightEntry(Hmx::Object* o) : mIntensity(0), mColor(0), mFlareEnabled(1), mTarget(0) {
    unk10.Reset();
}
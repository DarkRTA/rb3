#include "world/LightPreset.h"
#include "world/Spotlight.h"
#include "world/SpotlightDrawer.h"
#include "world/LightHue.h"
#include "rndobj/Env.h"
#include <algorithm>
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(LightPreset)
LightPreset* gEditPreset;
std::deque<std::pair<LightPreset::KeyframeCmd, float> > LightPreset::sManualEvents;

float ComputeSpotBlend(int i, float f){
    int min = Min<int>(f * 5.0f, 4);
    if(i % 5 < min) return 1.0f;
    else if(min < i % 5) return 0.0f;
    else {
        return Min(Max((f - i / 5.0f) * 5.0f, 0.0f), 1.0f);
    }
}

LightPreset::KeyframeCmd SymToPstKeyframe(Symbol s){
    if(s == next) return LightPreset::kPresetKeyframeNext;
    else if(s == prev) return LightPreset::kPresetKeyframePrev;
    else if(s == first) return LightPreset::kPresetKeyframeFirst;
    else return LightPreset::kPresetKeyframeNum;
}

LightPreset::LightPreset() : mKeyframes(this), mPlatformOnly(0), mSelectTriggers(this, kObjListNoNull), mLegacyFadeIn(0.0f), mLooping(0), mManual(0), mLocked(0),
    mSpotlightState(this), mLastKeyframe(0), mLastBlend(-1.0f), mStartBeat(0.0f), mManualFrameStart(0.0f), mManualFrame(0), mLastManualFrame(-1), mManualFadeTime(0.0f), mCachedDuration(0.0f), mHue(0) {

}

bool LightPreset::PlatformOk() const {
    if(TheLoadMgr.EditMode() || !mPlatformOnly || TheLoadMgr.GetPlatform() == kPlatformNone){
        return true;
    }
    else {
        Platform plat = TheLoadMgr.GetPlatform();
        if(TheLoadMgr.GetPlatform() == kPlatformPC){
            plat = kPlatformXBox;
        }
        return plat == mPlatformOnly;
    }
}

#pragma push
#pragma dont_inline on
LightPreset::~LightPreset(){ Clear(); }
#pragma pop

void LightPreset::ResetEvents(){
    sManualEvents.clear();
}

#pragma push
#pragma dont_inline on
void LightPreset::Clear(){
    mKeyframes.clear();
    for(int i = 0; i != mSpotlights.size(); i++) mSpotlights[i]->Release(this);
    mSpotlights.clear();
    for(int i = 0; i != mEnvironments.size(); i++) mEnvironments[i]->Release(this);
    mEnvironments.clear();
    for(int i = 0; i != mLights.size(); i++) mLights[i]->Release(this);
    for(int i = 0; i != mSpotlightDrawers.size(); i++) mSpotlightDrawers[i]->Release(this);
    mLights.clear();
}
#pragma pop

BEGIN_COPYS(LightPreset)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(LightPreset)
    BEGIN_COPYING_MEMBERS
        Clear();
        COPY_MEMBER(mKeyframes)
        COPY_MEMBER(mSpotlights)
        for(int i = 0; i != mSpotlights.size(); i++){
            mSpotlights[i]->AddRef(this);
        }
        COPY_MEMBER(mEnvironments)
        for(int i = 0; i != mEnvironments.size(); i++){
            mEnvironments[i]->AddRef(this);
        }
        COPY_MEMBER(mLights)
        for(int i = 0; i != mLights.size(); i++){
            mLights[i]->AddRef(this);
        }
        COPY_MEMBER(mSpotlightDrawers)
        for(int i = 0; i != mSpotlightDrawers.size(); i++){
            mSpotlightDrawers[i]->AddRef(this);
        }
        mSpotlightState.resize(mSpotlights.size());
        mEnvironmentState.resize(mEnvironments.size());
        mLightState.resize(mLights.size());
        mSpotlightDrawers.resize(mSpotlightDrawers.size());
        COPY_MEMBER(mLooping)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(mSelectTriggers)
        COPY_MEMBER(mLegacyFadeIn)
        COPY_MEMBER(mManual)
        COPY_MEMBER(mLocked)
        COPY_MEMBER(mPlatformOnly)
        CacheFrames();
    END_COPYING_MEMBERS
END_COPYS

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
    unsigned int spotlightcount;
    bs >> spotlightcount;
    mSpotlights.resize(spotlightcount);
    for(int i = 0; i != mSpotlights.size(); i++){
        bs.ReadString(buf, 0x80);
        mSpotlights[i] = Dir()->Find<Spotlight>(buf, false);
        if(mSpotlights[i]) mSpotlights[i]->AddRef(this);
    }
    unsigned int envcount;
    bs >> envcount;
    mEnvironments.resize(envcount);
    for(int i = 0; i != mEnvironments.size(); i++){
        bs.ReadString(buf, 0x80);
        mEnvironments[i] = Dir()->Find<RndEnviron>(buf, false);
        if(mEnvironments[i]) mEnvironments[i]->AddRef(this);
    }
    unsigned int lightcount;
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
        unsigned int sdrawercount;
        bs >> sdrawercount;
        mSpotlightDrawers.resize(sdrawercount);
        for(int i = 0; i != mSpotlightDrawers.size(); i++){
            bs.ReadString(buf, 0x80);
            mSpotlightDrawers[i] = Dir()->Find<SpotlightDrawer>(buf, false);
            if(mSpotlightDrawers[i]) mSpotlightDrawers[i]->AddRef(this);
        }
    }
    if(gRev == 0xB){
        int dummy;
        for(int i = 0; i < 8; i++) bs >> dummy;
    }
    mSpotlightState.resize(mSpotlights.size());
    mEnvironmentState.resize(mEnvironments.size(), EnvironmentEntry());
    mLightState.resize(mLights.size(), EnvLightEntry());
    mSpotlightDrawerState.resize(mSpotlightDrawers.size(), SpotlightDrawerEntry());
    for(int i = 0; i != mSpotlights.size(); i++){
        if(!mSpotlights[i] || !mSpotlights[i]->GetAnimateFromPreset()){
            RemoveSpotlight(i);
            i--;
        }
    }
    for(int i = 0; i != mEnvironments.size(); i++){
        if(!mEnvironments[i] || !mEnvironments[i]->GetAnimateFromPreset()){
            RemoveEnvironment(i);
            i--;
        }
    }
    for(int i = 0; i != mLights.size(); i++){
        if(!mLights[i] || !mLights[i]->GetAnimateFromPreset()){
            RemoveLight(i);
            i--;
        }
    }
    for(int i = 0; i != mSpotlightDrawers.size(); i++){
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

int LightPreset::GetCurrentKeyframe() const {
    if(mManual) return mManualFrame;
    else if(mKeyframes.empty()) return -1;
    else {
        int i;
        int ret;
        float f;
        GetKey(GetFrame(), i, ret, f);
        return ret;
    }
}

RndPostProc* LightPreset::GetCurrentPostProc() const {
    RndPostProc* ret = 0;
    int frame = GetCurrentKeyframe();
    if(frame >= 0) ret = mKeyframes[frame].mVideoVenuePostProc;
    return ret;
}

void LightPreset::RemoveSpotlight(int idx){
    for(int i = 0; i != mKeyframes.size(); i++){
        Keyframe& cur = mKeyframes[i];
        cur.mSpotlightEntries.erase(cur.mSpotlightEntries.begin() + idx);
    }
    mSpotlightState.erase(mSpotlightState.begin() + idx);
    if(mSpotlights[idx]){
        mSpotlights[idx]->Release(this);
    }
    mSpotlights.erase(mSpotlights.begin() + idx);
}

void LightPreset::RemoveEnvironment(int idx){
    for(int i = 0; i != mKeyframes.size(); i++){
        Keyframe& cur = mKeyframes[i];
        cur.mEnvironmentEntries.erase(cur.mEnvironmentEntries.begin() + idx);
    }
    mEnvironmentState.erase(mEnvironmentState.begin() + idx);
    if(mEnvironments[idx]){
        mEnvironments[idx]->Release(this);
    }
    mEnvironments.erase(mEnvironments.begin() + idx);
}

void LightPreset::RemoveLight(int idx){
    for(int i = 0; i != mKeyframes.size(); i++){
        Keyframe& cur = mKeyframes[i];
        cur.mLightEntries.erase(cur.mLightEntries.begin() + idx);
    }
    mLightState.erase(mLightState.begin() + idx);
    if(mLights[idx]){
        mLights[idx]->Release(this);
    }
    mLights.erase(mLights.begin() + idx);
}

void LightPreset::RemoveSpotlightDrawer(int idx){
    for(int i = 0; i != mKeyframes.size(); i++){
        Keyframe& cur = mKeyframes[i];
        cur.mSpotlightDrawerEntries.erase(cur.mSpotlightDrawerEntries.begin() + idx);
    }
    mSpotlightDrawerState.erase(mSpotlightDrawerState.begin() + idx);
    if(mSpotlightDrawers[idx]){
        mSpotlightDrawers[idx]->Release(this);
    }
    mSpotlightDrawers.erase(mSpotlightDrawers.begin() + idx);
}

void LightPreset::StartAnim(){
    mManualFrame = 0;
    mLastManualFrame = -1;
    mManualFrameStart = 0;
    mManualFadeTime = 0;
    mStartBeat = TheTaskMgr.Beat();
    mLastKeyframe = 0;
    mLastBlend = -1.0f;
    Handle(start_anim_msg, false);
    for(ObjPtrList<EventTrigger, ObjectDir>::iterator it = mSelectTriggers.begin(); it != mSelectTriggers.end(); ++it){
        (*it)->Trigger();
    }
}

void LightPreset::SetFrame(float frame, float blend){
    SetFrameEx(frame, blend, false);
}

void LightPreset::SetFrameEx(float frame, float blend, bool b){
    START_AUTO_TIMER("light");
}

void LightPreset::OnKeyframeCmd(LightPreset::KeyframeCmd cmd){
    sManualEvents.push_back(std::pair<KeyframeCmd, float>(cmd, TheTaskMgr.Beat() + 4.0f));
}

int LightPreset::NextManualFrame(LightPreset::KeyframeCmd cmd) const {
    int frame;
    if(cmd == kPresetKeyframeFirst){
        frame = 0;
    }
    else {
        frame = mManualFrame + (cmd == kPresetKeyframeNext ? 1 : -1);
    }
    if(mLooping){
        return frame % mKeyframes.size();
    }
    else {
        return Max<int>(0, Min<int>(frame, mKeyframes.size() - 1));
    }
}

void LightPreset::AdvanceManual(LightPreset::KeyframeCmd cmd){
    MILO_ASSERT(mManual, 0x330);
    if(cmd != kPresetKeyframeFirst || mManualFrame){
        mManualFrameStart = GetFrame();
        mLastManualFrame = mManualFrame;
        mManualFrame = NextManualFrame(cmd);
    }
}

void LightPreset::GetKey(float frame, int& iref1, int& iref2, float& fref) const {
    float theframe = frame;
    if(theframe <= 0.0f || mCachedDuration <= 0.0f){
        iref1 = -1;
        iref2 = 0;
        fref = 1.0f;
        return;
    }
    else {
        if(mLooping){
            float theframe = std::fmod(frame, mCachedDuration);
            if(mKeyframes.back().mFrame <= frame){
                if(mKeyframes.back().mFadeOutTime <= 0.0f){
                    iref1 = -1;
                    iref2 = mKeyframes.size() - 1;
                    fref = 1.0f;
                    return;
                }
                float framedur = mKeyframes.back().mFrame + mKeyframes.back().mDuration;
                if(framedur < theframe){
                    MILO_ASSERT(mKeyframes.back().mFadeOutTime > 0, 0x358);
                    iref1 = mKeyframes.size() - 1;
                    iref2 = 0;
                    fref = (theframe - framedur) / mKeyframes.back().mFadeOutTime;
                    return;
                }
                iref1 = -1;
                iref2 = mKeyframes.size() - 1;
                fref = 1.0f;
                return;
            }
        }
        else if(mKeyframes.back().mFrame <= frame){
            iref1 = -1;
            iref2 = mKeyframes.size() - 1;
            fref = 1.0f;
            return;
        }
        int cap = mKeyframes.size() - 1;
        int i;
        for(i = 0; i + 1 < cap - 1; i){
            i = (i + cap) >> 1;
            const Keyframe& kf = mKeyframes[i];
            if(theframe == kf.mFrame){
                iref1 = -1;
                iref2 = i;
                fref = 1.0f;
                return;
            }
            if(theframe <= kf.mFrame){
                cap = i;
            }
        }
        if(mKeyframes[i].mFrame <= theframe){
            mKeyframes[cap];
        }
        float dur = mKeyframes[i].mFrame + mKeyframes[i].mDuration;
        if(theframe > dur){
            mKeyframes[i];
            iref1 = i;
            iref2 = cap;
            fref = (theframe - dur) / mKeyframes[i].mFadeOutTime;
        }
        else {
            iref1 = -1;
            iref2 = i;
            fref = 1.0f;
        }
    }
}

void LightPreset::ApplyState(const LightPreset::Keyframe& k){
    mSpotlightState = k.mSpotlightEntries;
    mEnvironmentState = k.mEnvironmentEntries;
    mLightState = k.mLightEntries;
    mSpotlightDrawerState = k.mSpotlightDrawerEntries;
}

void LightPreset::Animate(float f){
    if(f < 1.1920929E-7f) return;
    MILO_ASSERT(mSpotlights.size() == mSpotlightState.size(), 0x3CD);
    for(int i = 0; i != mSpotlights.size(); i++){
        if(mSpotlights[i]->GetAnimateFromPreset()){
            float blend = ComputeSpotBlend(i, f);
            if(blend >= 1.1920929E-7f){
                AnimateSpotFromPreset(mSpotlights[i], mSpotlightState[i], blend);
            }
        }
    }
    MILO_ASSERT(mEnvironments.size() == mEnvironmentState.size(), 0x3DF);
    for(int i = 0; i != mEnvironments.size(); i++){
        if(mEnvironments[i]->GetAnimateFromPreset()){
            AnimateEnvFromPreset(mEnvironments[i], mEnvironmentState[i], f);
        }
    }
    MILO_ASSERT(mLights.size() == mLightState.size(), 1000);
    for(int i = 0; i != mLights.size(); i++){
        if(mLights[i]->GetAnimateFromPreset()){
            AnimateLightFromPreset(mLights[i], mLightState[i], f);
        }
    }
    MILO_ASSERT(mSpotlightDrawers.size() == mSpotlightDrawerState.size(), 0x3F1);
    for(int i = 0; i != mSpotlightDrawers.size(); i++){
        AnimateSpotlightDrawerFromPreset(mSpotlightDrawers[i], mSpotlightDrawerState[i], f);
    }
}

void LightPreset::SetKeyframe(LightPreset::Keyframe& k){
    for(int i = 0; i != k.mSpotlightEntries.size(); i++){
        FillSpotPresetData(mSpotlights[i], k.mSpotlightEntries[i], -1);
    }
    for(int i = 0; i != k.mEnvironmentEntries.size(); i++){
        FillEnvPresetData(mEnvironments[i], k.mEnvironmentEntries[i]);
    }
    for(int i = 0; i != k.mLightEntries.size(); i++){
        FillLightPresetData(mLights[i], k.mLightEntries[i]);
    }
    for(int i = 0; i != k.mSpotlightDrawerEntries.size(); i++){
        FillSpotlightDrawerPresetData(mSpotlightDrawers[i], k.mSpotlightDrawerEntries[i]);
    }
}

void LightPreset::SyncNewSpotlights(){
    for(ObjDirItr<Spotlight> it(Dir(), true); it != 0; ++it){
        Spotlight* key = it;
        std::vector<Spotlight*>::iterator found = std::find(mSpotlights.begin(), mSpotlights.end(), key);
        if(found == mSpotlights.end()){
            AddSpotlight(key, true);
        }
    }
}

void LightPreset::SyncKeyframeTargets(){
    for(ObjDirItr<Spotlight> it(Dir(), true); it != 0; ++it){
        Spotlight* key = it;
        std::vector<Spotlight*>::iterator found = std::find(mSpotlights.begin(), mSpotlights.end(), key);
        if(found == mSpotlights.end()) AddSpotlight(key, true);
    }
    for(ObjDirItr<RndEnviron> it(Dir(), true); it != 0; ++it){
        RndEnviron* key = it;
        std::vector<RndEnviron*>::iterator found = std::find(mEnvironments.begin(), mEnvironments.end(), key);
        if(found == mEnvironments.end()) AddEnvironment(key);
        for(ObjPtrList<RndLight, ObjectDir>::iterator lit = key->mLightsReal.begin(); lit != key->mLightsReal.end(); ++it){
            RndLight* lkey = *lit;
            std::vector<RndLight*>::iterator lfound = std::find(mLights.begin(), mLights.end(), lkey);
            if(lfound == mLights.end()) AddLight(lkey);
        }
        for(ObjPtrList<RndLight, ObjectDir>::iterator lit = key->mLightsApprox.begin(); lit != key->mLightsApprox.end(); ++it){
            RndLight* lkey = *lit;
            std::vector<RndLight*>::iterator lfound = std::find(mLights.begin(), mLights.end(), lkey);
            if(lfound == mLights.end()) AddLight(lkey);
        }
    }
    for(ObjDirItr<SpotlightDrawer> it(Dir(), true); it != 0; ++it){
        SpotlightDrawer* key = it;
        std::vector<SpotlightDrawer*>::iterator found = std::find(mSpotlightDrawers.begin(), mSpotlightDrawers.end(), key);
        if(found == mSpotlightDrawers.end()) AddSpotlightDrawer(key);
    }
    CacheFrames();
}

void LightPreset::AddSpotlight(Spotlight* s, bool b){
    s->AddRef(this);
    mSpotlights.push_back(s);
    SpotlightEntry e(this);
    FillSpotPresetData(s, e, -1);
    if(b){
        e.mIntensity = 0;
        e.mColor = 0;
    }
    for(int i = 0; i != mKeyframes.size(); i++){
        mKeyframes[i].mSpotlightEntries.push_back(e);
        MILO_ASSERT(mKeyframes[i].mSpotlightEntries.size() == mSpotlights.size(), 0x46E);
    }
    mSpotlightState.push_back(e);
}

void LightPreset::AddEnvironment(RndEnviron* env){
    env->AddRef(this);
    mEnvironments.push_back(env);
    EnvironmentEntry e;
    FillEnvPresetData(env, e);
    for(int i = 0; i != mKeyframes.size(); i++){
        mKeyframes[i].mEnvironmentEntries.push_back(e);
        MILO_ASSERT(mKeyframes[i].mEnvironmentEntries.size() == mEnvironments.size(), 0x47F);
    }
    mEnvironmentState.push_back(e);
}

void LightPreset::AddLight(RndLight* lit){
    lit->AddRef(this);
    mLights.push_back(lit);
    EnvLightEntry e;
    FillLightPresetData(lit, e);
    for(int i = 0; i != mKeyframes.size(); i++){
        mKeyframes[i].mLightEntries.push_back(e);
        MILO_ASSERT(mKeyframes[i].mLightEntries.size() == mLights.size(), 0x490);
    }
    mLightState.push_back(e);
}

void LightPreset::AddSpotlightDrawer(SpotlightDrawer* sd){
    sd->AddRef(this);
    mSpotlightDrawers.push_back(sd);
    SpotlightDrawerEntry e;
    FillSpotlightDrawerPresetData(sd, e);
    for(int i = 0; i != mKeyframes.size(); i++){
        mKeyframes[i].mSpotlightDrawerEntries.push_back(e);
        MILO_ASSERT(mKeyframes[i].mSpotlightDrawerEntries.size() == mSpotlightDrawers.size(), 0x4A1);
    }
    mSpotlightDrawerState.push_back(e);
}

void LightPreset::TranslateColor(const Hmx::Color& col, Hmx::Color& res){
    if(mHue) mHue->TranslateColor(col, res);
    else res = col;
}

void LightPreset::FillEnvPresetData(RndEnviron* env, LightPreset::EnvironmentEntry& e){
    e.mColor = env->AmbientColor().Pack();
    e.mFogColor = env->FogColor().Pack();
    e.mFogEnable = env->FogEnable();
    e.mFogStart = env->GetFogStart();
    e.mFogEnd = env->GetFogEnd();
}

void LightPreset::FillSpotlightDrawerPresetData(SpotlightDrawer* sd, LightPreset::SpotlightDrawerEntry& e){
    e.mBaseIntensity = sd->mParams.mBaseIntensity;
    e.mSmokeIntensity = sd->mParams.mSmokeIntensity;
    e.mLightInfluence = sd->mParams.mLightingInfluence;
    e.mTotalIntensity = sd->mParams.mIntensity;
}

void LightPreset::AnimateSpotlightDrawerFromPreset(SpotlightDrawer* sd, const LightPreset::SpotlightDrawerEntry& e, float f){
    float val;
    Interp(sd->mParams.mBaseIntensity, e.mBaseIntensity, f, val);
    sd->mParams.mBaseIntensity = val;
    Interp(sd->mParams.mSmokeIntensity, e.mSmokeIntensity, f, val);
    sd->mParams.mSmokeIntensity = val;
    Interp(sd->mParams.mLightingInfluence, e.mLightInfluence, f, val);
    sd->mParams.mLightingInfluence = val;
    Interp(sd->mParams.mIntensity, e.mTotalIntensity, f, val);
    sd->mParams.mIntensity = val;
}

void LightPreset::SetSpotlight(Spotlight* s, int data){
    int idx;
    for(idx = 0; idx != mSpotlights.size(); idx++){
        if(mSpotlights[idx] == s) break;
    }
    if(idx == mSpotlights.size()) AddSpotlight(s, false);
    for(int i = 0; i != mKeyframes.size(); i++){
        FillSpotPresetData(s, mKeyframes[i].mSpotlightEntries[idx], data);
    }
}

DataNode LightPreset::OnSetKeyframe(DataArray* da){
    if(mHue){
        MILO_WARN("Can't set keyframe with hue translation");
        return DataNode(0);
    }
    else {
        int idx = da->Int(2);
        SyncKeyframeTargets();
        SetKeyframe(mKeyframes[idx]);
        return OnViewKeyframe(da);
    }
}

DataNode LightPreset::OnViewKeyframe(DataArray* da){
    ApplyState(mKeyframes[da->Int(2)]);
    Animate(1.0f);
    return DataNode(0);
}

LightPreset::Keyframe::Keyframe(Hmx::Object* o) : mSpotlightEntries(o), mVideoVenuePostProc(o, 0), mTriggers(o, kObjListNoNull), mDuration(0), mFadeOutTime(0), mFrame(-1.0f) {
    LightPreset* preset = dynamic_cast<LightPreset*>(o);
    MILO_ASSERT(preset, 0x5FB);
    mSpotlightEntries.resize(preset->mSpotlights.size());
    mEnvironmentEntries.resize(preset->mEnvironments.size());
    mLightEntries.resize(preset->mLights.size());
    mSpotlightDrawerEntries.resize(preset->mSpotlightDrawers.size());
    if(!sLoading) preset->SetKeyframe(*this);
}

void LightPreset::Keyframe::LoadStageKit(BinStream& bs){
    int x;
    for(int i = 0; i < 9; i++) bs >> x;
}

void LightPreset::Keyframe::LoadP9(BinStream& bs){
    MILO_ASSERT(gRev == 14, 0x638);
    String str;
    bs >> str;
    bs >> mSpotlightEntries;
    bs >> mEnvironmentEntries;
    bs >> mLightEntries;
    bs >> mSpotlightDrawerEntries;
    LoadStageKit(bs);
}

void LightPreset::Keyframe::Load(BinStream& bs){
    MILO_ASSERT(gRev != 14, 0x64A);
    bs >> mDuration;
    bs >> mFadeOutTime;
    bs >> mSpotlightEntries;
    bs >> mEnvironmentEntries;
    bs >> mLightEntries;
    if(gRev > 5){
        String str; bs >> str;
    }
    if(gRev > 9) bs >> mSpotlightDrawerEntries;
    if(gRev > 0x11) bs >> mVideoVenuePostProc;
    if(gRev > 0x13) bs >> mTriggers;
    if(gRev > 0xB) LoadStageKit(bs);
}

LightPreset::SpotlightEntry::SpotlightEntry(Hmx::Object* o) : mIntensity(0), mColor(0), mFlareEnabled(1), mTarget(0) {
    unk10.Reset();
}

void LightPreset::SpotlightEntry::Load(BinStream& bs){
    float intensity;
    bs >> intensity;
    mIntensity = intensity;
    bs >> unk10;
    Hmx::Color col;
    bs >> col;
    col.alpha = 1.0f;
    mColor = col.Pack();
    ObjPtr<RndTransformable, ObjectDir> tPtr(0, 0);
    if(!tPtr.Load(bs, false, 0)) unk8p1 = 0;
    if(gRev < 0x13){
        Symbol s; bs >> s;
    }
    mTarget = tPtr;
    if(gRev > 1){
        bool b; bs >> b;
        if(b) mFlareEnabled = true;
        else mFlareEnabled = false;
        if(gRev < 9){ int i; bs >> i; }
    }
    if(mTarget || !unk8p1){
        unk10.Set(0,0,0,0);
    }
}

void LightPreset::SpotlightEntry::CalculateDirection(Spotlight* s, Hmx::Quat& q) const {
    q = unk10;
    RndTransformable* target = mTarget;
    Hmx::Matrix3 m38;
    if(unk8p1 && target) s->CalculateDirection(target, m38);
    Hmx::Quat qloc;
    qloc.Set(m38);
    q = qloc;
}

LightPreset::EnvironmentEntry::EnvironmentEntry() : mFogEnable(0), mFogStart(0), mFogEnd(0) {
    mColor = 0;
    mFogColor = 0;
}

void LightPreset::EnvironmentEntry::Load(BinStream& bs){
    Hmx::Color col;
    bs >> col;
    mColor = col.Pack();
    bs >> mFogEnable;
    bs >> mFogStart;
    bs >> mFogEnd;
    bs >> col;
    mFogColor = col.Pack();
}

bool LightPreset::EnvironmentEntry::operator!=(const LightPreset::EnvironmentEntry& e) const {
    if(mFogEnable != e.mFogEnable) return true;
    else if(mFogStart != e.mFogStart) return true;
    else if(mFogEnd != e.mFogEnd) return true;
    else if((unsigned int)mColor != (unsigned int)e.mColor) return true;
    else return mFogColor != e.mFogColor;
}

LightPreset::EnvLightEntry::EnvLightEntry() : mRange(0), mLightType(RndLight::kPoint) {
    unk0.Reset();
    mPosition.Zero();
    mColor = 0;
}

void LightPreset::EnvLightEntry::Load(BinStream& bs){
    bs >> unk0;
    bs >> mPosition;
    Hmx::Color col;
    bs >> col;
    mColor = col.Pack();
    bs >> mRange;
    bs >> (int&)mLightType;
}

bool LightPreset::EnvLightEntry::operator!=(const LightPreset::EnvLightEntry& e) const {
    if(mRange != e.mRange) return true;
    else if((unsigned int)mLightType != e.mLightType) return true;
    else if(unk0 != e.unk0) return true;
    else if(mPosition != e.mPosition) return true;
    else return mColor != e.mColor;
}

LightPreset::SpotlightDrawerEntry::SpotlightDrawerEntry() : mTotalIntensity(0), mBaseIntensity(0), mSmokeIntensity(0), mLightInfluence(0) {}

void LightPreset::SpotlightDrawerEntry::Load(BinStream& bs){
    bs >> mBaseIntensity;
    bs >> mSmokeIntensity;
    bs >> mTotalIntensity;
    if(gRev > 0xF) bs >> mLightInfluence;
    else mLightInfluence = 1.0f;
}

void LightPreset::SpotlightDrawerEntry::Animate(const LightPreset::SpotlightDrawerEntry& e, float f){
    Interp(mBaseIntensity, e.mBaseIntensity, f, mBaseIntensity);
    Interp(mSmokeIntensity, e.mSmokeIntensity, f, mSmokeIntensity);
    Interp(mLightInfluence, e.mLightInfluence, f, mLightInfluence);
    Interp(mTotalIntensity, e.mTotalIntensity, f, mTotalIntensity);
}

bool LightPreset::SpotlightDrawerEntry::operator!=(const LightPreset::SpotlightDrawerEntry& e) const {
    if(mBaseIntensity != e.mBaseIntensity) return true;
    else if(mSmokeIntensity != e.mSmokeIntensity) return true;
    else if(mLightInfluence != e.mLightInfluence) return true;
    else return mTotalIntensity != e.mTotalIntensity;
}

template <class T>
const char* GetObjName(const std::vector<T*>& vec, int idx){
    if(idx >= vec.size()) return "<obj index out of bounds>";
    else if(vec[idx]) return vec[idx]->Name();
    else return "<obj not found>";
}

const char* GetName(LightPreset* preset, int idx, LightPreset::PresetObject obj){
    switch(obj){
        case LightPreset::kPresetSpotlight:
            return GetObjName(preset->mSpotlights, idx);
        case LightPreset::kPresetSpotlightDrawer:
            return GetObjName(preset->mSpotlightDrawers, idx);
        case LightPreset::kPresetEnv:
            return GetObjName(preset->mEnvironments, idx);
        case LightPreset::kPresetLight:
            return GetObjName(preset->mLights, idx);
        default:
            return "<invalid preset object>";
    }
}

BEGIN_CUSTOM_PROPSYNC(LightPreset::SpotlightEntry)
    SYNC_PROP_SET(spotlight, GetName(gEditPreset, _prop->Int(_i - 1), LightPreset::kPresetSpotlight), )
    SYNC_PROP_SET(intensity, o.mIntensity, )
    SYNC_PROP_SET(color, o.mColor, )
    SYNC_PROP(target, o.mTarget)
    SYNC_PROP_SET(flare_enabled, o.mFlareEnabled, )
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(LightPreset::SpotlightDrawerEntry)
    SYNC_PROP_SET(spotlight_drawer, GetName(gEditPreset, _prop->Int(_i - 1), LightPreset::kPresetSpotlightDrawer), )
    SYNC_PROP_SET(total, o.mTotalIntensity, )
    SYNC_PROP_SET(base_intensity, o.mBaseIntensity, )
    SYNC_PROP_SET(smoke_intensity, o.mSmokeIntensity, )
    SYNC_PROP_SET(light_influence, o.mLightInfluence, )
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(LightPreset::EnvironmentEntry)
    SYNC_PROP_SET(environment, GetName(gEditPreset, _prop->Int(_i - 1), LightPreset::kPresetEnv), )
    SYNC_PROP_SET(fog_enable, o.mFogEnable, )
    SYNC_PROP_SET(fog_start, o.mFogStart, )
    SYNC_PROP_SET(fog_end, o.mFogEnd, )
    SYNC_PROP_SET(ambient_color, o.mColor, )
    SYNC_PROP_SET(fog_color, o.mColor, )
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(LightPreset::EnvLightEntry)
    SYNC_PROP_SET(light, GetName(gEditPreset, _prop->Int(_i - 1), LightPreset::kPresetLight), )
    SYNC_PROP(position, o.mPosition)
    SYNC_PROP_SET(range, o.mRange, )
    SYNC_PROP_SET(type, RndLight::TypeToStr(o.mLightType), )
    SYNC_PROP_SET(color, o.mColor, )
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(LightPreset::Keyframe)
    SYNC_PROP(duration, o.mDuration)
    SYNC_PROP(fade_out, o.mFadeOutTime)
    SYNC_PROP(spotlight_entries, o.mSpotlightEntries)
    SYNC_PROP(spotlight_drawer_entries, o.mSpotlightDrawerEntries)
    SYNC_PROP(environment_entries, o.mEnvironmentEntries)
    SYNC_PROP(light_entries, o.mLightEntries)
    SYNC_PROP(video_venue_postproc, o.mVideoVenuePostProc)
    SYNC_PROP(triggers, o.mTriggers)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(LightPreset)
    gEditPreset = this;
    SYNC_PROP_MODIFY_ALT(keyframes, mKeyframes, CacheFrames())
    SYNC_PROP(looping, mLooping)
    SYNC_PROP(category, mCategory)
    SYNC_PROP(select_triggers, mSelectTriggers)
    SYNC_PROP(legacy_fade_in, mLegacyFadeIn)
    SYNC_PROP(manual, mManual)
    SYNC_PROP(locked, mLocked)
    SYNC_PROP(platform_only, mPlatformOnly)
    SYNC_PROP(hue, mHue)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS

BEGIN_HANDLERS(LightPreset)
    HANDLE(set_keyframe, OnSetKeyframe)
    HANDLE(view_keyframe, OnViewKeyframe)
    HANDLE_ACTION(next, OnKeyframeCmd(kPresetKeyframeNext))
    HANDLE_ACTION(prev, OnKeyframeCmd(kPresetKeyframePrev))
    HANDLE_ACTION(first, OnKeyframeCmd(kPresetKeyframeFirst))
    HANDLE_ACTION(reset_events, ResetEvents())
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x85A)
END_HANDLERS
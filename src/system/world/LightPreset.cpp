#include "world/LightPreset.h"
#include "world/Spotlight.h"
#include "world/SpotlightDrawer.h"
#include "world/LightHue.h"
#include "rndobj/Env.h"
#include "utl/Symbols.h"

INIT_REVS(LightPreset)
LightPreset* gEditPreset;

LightPreset::KeyframeCmd SymToPstKeyframe(Symbol s){
    if(s == next) return LightPreset::kPresetKeyframeNext;
    else if(s == prev) return LightPreset::kPresetKeyframePrev;
    else if(s == first) return LightPreset::kPresetKeyframeFirst;
    else return LightPreset::kPresetKeyframeNum;
}

LightPreset::LightPreset() : mKeyframes(this), mPlatformOnly(0), mSelectTriggers(this, kObjListNoNull), mLegacyFadeIn(0.0f), mLooping(0), mManual(0), mLocked(0),
    mSpotlightState(this), unk80(0), unk84(-1.0f), unk88(0.0f), unk8c(0.0f), unk90(0), unk94(-1), unk98(0.0f), mEndFrame(0.0f), mHue(0) {

}

#pragma push
#pragma dont_inline on
LightPreset::~LightPreset(){ Clear(); }
#pragma pop

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
    mSpotlightState.resize(mSpotlights.size());
    mEnvironmentState.resize(mEnvironments.size(), EnvironmentEntry());
    mLightState.resize(mLights.size(), EnvLightEntry());
    mSpotlightDrawerState.resize(mSpotlightDrawers.size(), SpotlightDrawerEntry());
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

int LightPreset::GetCurrentKeyframe() const {
    if(mManual) return unk90;
    else if(mKeyframes.empty()) return -1;
    else {
        int i;
        int ret;
        float f;
        GetKey(mFrame, i, ret, f);
        return ret;
    }
}

RndPostProc* LightPreset::GetCurrentPostProc() const {
    RndPostProc* ret = 0;
    int frame = GetCurrentKeyframe();
    if(frame >= 0) ret = mKeyframes[frame].mVideoVenuePostProc;
    return ret;
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
    mColor = col.Pack();
    ObjPtr<RndTransformable, ObjectDir> tPtr(0, 0);
    if(tPtr.Load(bs, false, 0)) unk8p1 = 0;
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
        unk10.Zero();
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
    unk4 = 0;
}

void LightPreset::EnvironmentEntry::Load(BinStream& bs){
    Hmx::Color col;
    bs >> col;
    mColor = col.Pack();
    bs >> mFogEnable;
    bs >> mFogStart;
    bs >> mFogEnd;
    bs >> col;
    unk4 = col.Pack();
}

bool LightPreset::EnvironmentEntry::operator!=(const LightPreset::EnvironmentEntry& e) const {
    if(mFogEnable != e.mFogEnable) return true;
    else if(mFogStart != e.mFogStart) return true;
    else if(mFogEnd != e.mFogEnd) return true;
    else if((unsigned int)mColor != (unsigned int)e.mColor) return true;
    else return unk4 != e.unk4;
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

LightPreset::SpotlightDrawerEntry::SpotlightDrawerEntry() : mTotal(0), mBaseIntensity(0), mSmokeIntensity(0), mLightInfluence(0) {}

void LightPreset::SpotlightDrawerEntry::Load(BinStream& bs){
    bs >> mBaseIntensity;
    bs >> mSmokeIntensity;
    bs >> mTotal;
    if(gRev > 0xF) bs >> mLightInfluence;
    else mLightInfluence = 1.0f;
}

bool LightPreset::SpotlightDrawerEntry::operator!=(const LightPreset::SpotlightDrawerEntry& e) const {
    if(mBaseIntensity != e.mBaseIntensity) return true;
    else if(mSmokeIntensity != e.mSmokeIntensity) return true;
    else if(mLightInfluence != e.mLightInfluence) return true;
    else return mTotal != e.mTotal;
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
    SYNC_PROP_SET(total, o.mTotal, )
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
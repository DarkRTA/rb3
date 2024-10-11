#include "meta_band/ProfileMgr.h"
#include "meta_band/ModifierMgr.h"
#include "rndobj/Rnd.h"

INIT_REVS(ProfileMgr);
ProfileMgr TheProfileMgr;

namespace {
    float kNotForcingGain = -1.0f;
}

ProfileMgr::ProfileMgr() : mPlatformAudioLatency(0), mPlatformVideoLatency(50.0f), mInGameExtraVideoLatency(70.0f), mInGameSyncOffsetAdjustment(0), mGlobalOptionsSaveState(kMetaProfileUnloaded),
    mGlobalOptionsDirty(0), mBackgroundVolume(11), mForegroundVolume(11), mFxVolume(11), mCrowdVolume(11), mVocalCueVolume(11), mVoiceChatVolume(11),
    mHasSeenFirstTimeCalibration(0), mHasConnectedProGuitar(0), mSyncOffset(0), mSongToTaskMgrMs(0), mBassBoost(0), mDolby(0), unk582(0), mSyncPresetIx(0), mOverscan(0), mSynapseEnabled(1),
    unk58a(1), mSecondPedalHiHat(0), mWiiSpeakToggle(1), mWiiSpeakFriendsVolume(6), mWiiSpeakMicrophoneSensitivity(3),
    mWiiSpeakHeadphoneMode(0), mWiiSpeakEchoSuppression(0), unk5b2(0), mWiiFriendsPromptShown(0), mUsingWiiFriends(0), unk5b8(0), mCymbalConfiguration(0), unk5d8(0), mAllUnlocked(0) {
    mSyncOffset = -mPlatformVideoLatency;
    mSongToTaskMgrMs = mPlatformVideoLatency - mPlatformAudioLatency;
    for(int i = 0; i < 3; i++){
        unk5bc.push_back(8);
        unk5e0.push_back(kNotForcingGain);
    }
    for(int i = 0; i < kJoypadNumTypes; i++){
        for(int j = 0; j < kNumLagContexts; j++){
            mJoypadExtraLagOffsets[i][j] = GetJoypadExtraLagInits((JoypadType)i, (LagContext)j);
        }
    }
    UpdatePrimaryProfile();
}

DECOMP_FORCEACTIVE(ProfileMgr, "profile_mgr", "signin_changed")

bool ProfileMgr::GetAllUnlocked(){ return mAllUnlocked; }
int ProfileMgr::GetMaxCharacters() const { return 10; }

bool ProfileMgr::UnlockAllSongs(){
    bool old = mAllUnlocked;
    mAllUnlocked = true;
    return old == 0;
}

void ProfileMgr::RelockSongs(){ mAllUnlocked = false; }

void ProfileMgr::SetGlobalOptionsSaveState(ProfileSaveState state){
    MILO_ASSERT(mGlobalOptionsSaveState != kMetaProfileUnchanged, 0x396);
    if(state != kMetaProfileUnchanged) mGlobalOptionsSaveState = state;
}

bool ProfileMgr::GlobalOptionsNeedsSave(){
    if(mGlobalOptionsSaveState != kMetaProfileLoaded) return false;
    else return mGlobalOptionsDirty;
}

int ProfileMgr::GetGlobalOptionsSize(){
    return TheModifierMgr->SaveSize(gRev) + 0x52;
}

void ProfileMgr::SaveGlobalOptions(FixedSizeSaveableStream& bs){
    bs << packRevs(2, 7);
    bs << mSyncOffset;
    bs << mSongToTaskMgrMs;
    bs << mBackgroundVolume;
    bs << mForegroundVolume;
    bs << mFxVolume;
    bs << mVocalCueVolume;
    bs << mBassBoost;
    bs << mCrowdVolume;
    bs << mDolby;
    bs << mSyncPresetIx;
    bs << mOverscan;
    bs << mSynapseEnabled;
    bs << mWiiSpeakToggle;
    bs << mWiiSpeakFriendsVolume;
    bs << mWiiSpeakMicrophoneSensitivity;
    bs << mWiiSpeakHeadphoneMode;
    bs << mWiiSpeakEchoSuppression;
    bs << mVoiceChatVolume;
    bs << mHasSeenFirstTimeCalibration;
    bs << mHasConnectedProGuitar;
    bs << mCymbalConfiguration;
    bs << unk58a;
    bs << mSecondPedalHiHat;
    TheModifierMgr->Save(bs);
    bs << String("");
    bs << false;
    bs << 0ll;
    bs << mWiiFriendsPromptShown;
    bs << mUsingWiiFriends;
    bs << unk5b8;
    mGlobalOptionsDirty = false;
}

void ProfileMgr::LoadGlobalOptions(FixedSizeSaveableStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(7, 2);
    bs >> mSyncOffset;
    bs >> mSongToTaskMgrMs;
    if(gRev != 0){
        bs >> mBackgroundVolume;
        bs >> mForegroundVolume;
    }
    else {
        bs >> mBackgroundVolume;
        mForegroundVolume = mBackgroundVolume;
    }
    bs >> mFxVolume;
    if(gRev != 0) bs >> mVocalCueVolume;
    bs >> mBassBoost;
    bs >> mCrowdVolume;
    bs >> mDolby;
    bs >> mSyncPresetIx;
    bs >> mOverscan;
    if(gRev > 1){
        if(gRev > 2) bs >> mSynapseEnabled;
        else {
            bool b; bs >> b;
        }
    }
    bs >> mWiiSpeakToggle;
    bs >> mWiiSpeakFriendsVolume;
    bs >> mWiiSpeakMicrophoneSensitivity;
    bs >> mWiiSpeakHeadphoneMode;
    bs >> mWiiSpeakEchoSuppression;
    bs >> mVoiceChatVolume;
    bs >> mHasSeenFirstTimeCalibration;
    bs >> mHasConnectedProGuitar;
    bs >> mCymbalConfiguration;
    bs >> unk58a;
    if(gRev > 4) bs >> mSecondPedalHiHat;
    if(gRev >= 7) TheModifierMgr->Load(bs, gRev);
    String str;
    bs >> str;
    bool b46; bs >> b46;
    long long lol; bs >> lol;
    if(gAltRev >= 1){
        bs >> mWiiFriendsPromptShown;
        bs >> mUsingWiiFriends;
    }
    if(gAltRev >= 2) bs >> unk5b8;
    unk5b2 = true;
    mGlobalOptionsDirty = false;
    PushAllOptions();
}

void ProfileMgr::InitSliders(){
    if(!mSliderConfig){
        mSliderConfig = SystemConfig("sound", "slider");
    }
    if(!mVoiceChatSliderConfig){
        mVoiceChatSliderConfig = SystemConfig("sound", "slider_voicechat");
    }
}

float ProfileMgr::SliderIxToDb(int ixVol) const {
    MILO_ASSERT(mSliderConfig, 0x4C0);
    MILO_ASSERT(0 <= ixVol && ixVol < mSliderConfig->Size() - 1, 0x4C1);
    return mSliderConfig->Float(ixVol + 1);
}

void ProfileMgr::GetMicGainInfo(const Symbol& s, float& f1, float& f2, float& f3, float& f4) const {
    MILO_LOG("Mic:%s\n", s);
    DataArray* cfg = SystemConfig("sound", "ratio_sliders", s);
    DataArray* arr = cfg->Array(1);
    f1 = arr->Float(0);
    f2 = arr->Float(1);
    f3 = arr->Float(2);
    f4 = arr->Float(3);
}

int ProfileMgr::GetSliderStepCount() const {
    MILO_ASSERT(mSliderConfig, 0x4D3);
    return mSliderConfig->Size() - 1;
}

void ProfileMgr::PushAllOptions(){
    
}

bool ProfileMgr::GetBassBoost() const { return mBassBoost; }

void ProfileMgr::SetBackgroundVolume(int vol){
    mBackgroundVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetForegroundVolume(int vol){
    mForegroundVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetFxVolume(int vol){
    mFxVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

int ProfileMgr::GetFxVolume() const {
    if(!unk582) return mFxVolume;
    else return 0;
}

void ProfileMgr::SetCrowdVolume(int vol){
    mCrowdVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetVocalCueVolume(int vol){
    if(vol >= 0 && vol < GetSliderStepCount()){
        mVocalCueVolume = vol;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

void ProfileMgr::SetVoiceChatVolume(int vol){
    mVoiceChatVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetBassBoost(bool b){
    mBassBoost = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetDolby(bool b){
    mDolby = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetOverscan(bool b){
    if(b != mOverscan){
        mOverscan = b;
        TheRnd->SetOverscan(mOverscan);
        TheRnd->ConfigureRenderMode();
        TheRnd->ChangeYScale(true);
        mGlobalOptionsDirty = true;
    }
}

void ProfileMgr::SetSynapseEnabled(bool b){
    mSynapseEnabled = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetWiiSpeakToggle(bool b){
    mWiiSpeakToggle = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiSpeakFriendsVolume(int vol){
    mWiiSpeakFriendsVolume = vol;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiSpeakMicrophoneSensitivity(int sense){
    mWiiSpeakMicrophoneSensitivity = sense;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiSpeakEchoSuppression(bool b){
    mWiiSpeakEchoSuppression = b;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::GetHasSeenFirstTimeCalibration() const { return mHasSeenFirstTimeCalibration; }

void ProfileMgr::SetHasSeenFirstTimeCalibration(bool b){
    mHasSeenFirstTimeCalibration = b;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::GetHasConnectedProGuitar() const { return mHasConnectedProGuitar; }

void ProfileMgr::SetHasConnectedProGuitar(bool b){
    mHasConnectedProGuitar = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiFriendsPromptShown(){
    mWiiFriendsPromptShown = true;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::GetUsingWiiFriends(){ return mUsingWiiFriends; }

bool ProfileMgr::GetSecondPedalHiHat() const { return mSecondPedalHiHat; }

void ProfileMgr::SetSecondPedalHiHat(bool b){
    mSecondPedalHiHat = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetSyncPresetIx(int ix){
    mSyncPresetIx = ix;
    mGlobalOptionsDirty = true;
}

float ProfileMgr::GetSongToTaskMgrMsRaw() const { return mSongToTaskMgrMs; }

void ProfileMgr::SetSongToTaskMgrMsRaw(float ms){
    if(mSongToTaskMgrMs != ms){
        mSongToTaskMgrMs = ms;
        mGlobalOptionsDirty = true;
    }
}
float ProfileMgr::GetJoypadExtraLag(JoypadType type, LagContext ctx) const {
    MILO_ASSERT(( 0) <= (type) && (type) < ( kJoypadNumTypes), 0x6DE);
    MILO_ASSERT(( 0) <= (ctx) && (ctx) < ( kNumLagContexts), 0x6DF);
    return mJoypadExtraLagOffsets[type][ctx];
}

void ProfileMgr::SetJoypadExtraLag(JoypadType type, LagContext ctx, float lag){
    MILO_ASSERT(( 0) <= (type) && (type) < ( kJoypadNumTypes), 0x6E5);
    MILO_ASSERT(( 0) <= (ctx) && (ctx) < ( kNumLagContexts), 0x6E6);
    mJoypadExtraLagOffsets[type][ctx] = lag;
}

float ProfileMgr::GetPadExtraLag(int pad, LagContext ctx) const {
    return mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][ctx];
}

void ProfileMgr::SetPlatformAudioLatency(float lat){ mPlatformAudioLatency = lat; }
void ProfileMgr::SetPlatformVideoLatency(float lat){ mPlatformVideoLatency = lat; }
float ProfileMgr::GetInGameExtraVideoLatency() const { return mInGameExtraVideoLatency; }
void ProfileMgr::SetInGameExtraVideoLatency(float lat){ mInGameExtraVideoLatency = lat; }
float ProfileMgr::GetInGameSyncOffsetAdjustment() const { return mInGameSyncOffsetAdjustment; }
void ProfileMgr::SetInGameSyncOffsetAdjustment(float adj){ mInGameSyncOffsetAdjustment = adj; }

float ProfileMgr::GetSyncOffset(int pad) const {
    float lag = 0;
    if(pad != -1){
        lag = mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][0];
    }
    return (mSyncOffset + mInGameSyncOffsetAdjustment) - lag;
}

float ProfileMgr::GetSyncOffsetRaw() const { return mSyncOffset; }

void ProfileMgr::SetSyncOffsetRaw(float offset){
    if(mSyncOffset != offset){
        mSyncOffset = offset;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

float ProfileMgr::GetExcessVideoLag() const { return -(mPlatformVideoLatency + mSyncOffset); }

void ProfileMgr::SetExcessVideoLag(float lag){
    SetSyncOffsetRaw(-(lag + mPlatformVideoLatency));
    SetExcessAudioLag(-(mPlatformAudioLatency + mSongToTaskMgrMs + mSyncOffset));
}

float ProfileMgr::GetPlatformAudioLatency() const { return mPlatformAudioLatency; }
float ProfileMgr::GetPlatformVideoLatency() const { return mPlatformVideoLatency; }

float ProfileMgr::GetExcessAudioLagNeutral(int pad, bool b) const {
    int i2 = 0;
    if(b) i2 = 2;
    return mPlatformAudioLatency + mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][i2];
}

float ProfileMgr::GetExcessVideoLagNeutral(int pad, bool b) const {
    return mPlatformVideoLatency + mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][b];
}

float ProfileMgr::GetExcessAudioLag() const {
    return -(mPlatformAudioLatency + mSongToTaskMgrMs + mSyncOffset);
}

void ProfileMgr::SetExcessAudioLag(float lag){
    SetSongToTaskMgrMsRaw(-(lag + mPlatformAudioLatency + mSyncOffset));
}

float ProfileMgr::GetBackgroundVolumeDb() const { return SliderIxToDb(mBackgroundVolume); }
int ProfileMgr::GetBackgroundVolume() const { return mBackgroundVolume; }
float ProfileMgr::GetForegroundVolumeDb() const { return SliderIxToDb(mForegroundVolume); }
int ProfileMgr::GetForegroundVolume() const { return mForegroundVolume; }

float ProfileMgr::GetFxVolumeDb() const {
    return SliderIxToDb(unk582 ? 0 : mFxVolume);
}

float ProfileMgr::GetCrowdVolumeDb(){ return SliderIxToDb(mCrowdVolume); }
int ProfileMgr::GetCrowdVolume() const { return mCrowdVolume; }
float ProfileMgr::GetVocalCueVolumeDb(){ return SliderIxToDb(mVocalCueVolume); }
int ProfileMgr::GetVocalCueVolume() const { return mVocalCueVolume; }
float ProfileMgr::GetVoiceChatVolumeDb(){ return SliderIxToDb(mVoiceChatVolume); }
int ProfileMgr::GetVoiceChatVolume() const { return mVoiceChatVolume; }

unsigned int ProfileMgr::GetCymbalConfiguration() const { return mCymbalConfiguration; }

void ProfileMgr::SetCymbalConfiguration(unsigned int ui){
    mCymbalConfiguration = ui;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::HasLoaded(){ return unk5b2; }
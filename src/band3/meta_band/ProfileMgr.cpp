#include "meta_band/ProfileMgr.h"
#include "meta_band/ModifierMgr.h"
#include "rndobj/Rnd.h"

INIT_REVS(ProfileMgr);

namespace {
    float kNotForcingGain = -1.0f;
}

ProfileMgr::ProfileMgr() : unk1c(0), unk20(50.0f), unk24(70.0f), unk28(0), mGlobalOptionsSaveState(kMetaProfileUnloaded), mGlobalOptionsDirty(0), mBackgroundVolume(11), mForegroundVolume(11), mFxVolume(11), mCrowdVolume(11), mVocalCueVolume(11), mVoiceChatVolume(11),
    mHasSeenFirstTimeCalibration(0), mHasConnectedProGuitar(0), unk578(0), unk57c(0), mBassBoost(0), mDolby(0), unk582(0), unk584(0), mOverscan(0), mSynapseEnabled(0), unk58a(0), mSecondPedalHiHat(0), mWiiSpeakToggle(1), mWiiSpeakFriendsVolume(6), mWiiSpeakMicrophoneSensitivity(3),
    unk5b0(0), mWiiSpeakEchoSuppression(0), unk5b2(0), mWiiFriendsPromptShown(0), mUsingWiiFriends(0), unk5b8(0), unk5cc(0), unk5d8(0), mAllUnlocked(0) {
    unk578 = -unk20;
    unk57c = unk20 - unk1c;
    for(int i = 0; i < 3; i++){
        unk5bc.push_back(8);
        unk5e0.push_back(kNotForcingGain);
    }
    UpdatePrimaryProfile();
}

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
    bs << unk578;
    bs << unk57c;
    bs << mBackgroundVolume;
    bs << mForegroundVolume;
    bs << mFxVolume;
    bs << mVocalCueVolume;
    bs << mBassBoost;
    bs << mCrowdVolume;
    bs << mDolby;
    bs << unk584;
    bs << mOverscan;
    bs << mSynapseEnabled;
    bs << mWiiSpeakToggle;
    bs << mWiiSpeakFriendsVolume;
    bs << mWiiSpeakMicrophoneSensitivity;
    bs << unk5b0;
    bs << mWiiSpeakEchoSuppression;
    bs << mVoiceChatVolume;
    bs << mHasSeenFirstTimeCalibration;
    bs << mHasConnectedProGuitar;
    bs << unk5cc;
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
    bs >> unk578;
    bs >> unk57c;
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
    bs >> unk584;
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
    bs >> unk5b0;
    bs >> mWiiSpeakEchoSuppression;
    bs >> mVoiceChatVolume;
    bs >> mHasSeenFirstTimeCalibration;
    bs >> mHasConnectedProGuitar;
    bs >> unk5cc;
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
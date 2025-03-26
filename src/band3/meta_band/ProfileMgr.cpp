#include "meta_band/ProfileMgr.h"
#include "BandMachineMgr.h"
#include "bandobj/BandCharDesc.h"
#include "beatmatch/BeatMaster.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/GameMode.h"
#include "math/Decibels.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/BandProfile.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/PlatformMgr.h"
#include "rndobj/Rnd.h"
#include "synth/Faders.h"
#include "synth/FxSend.h"
#include "synth/MicManagerInterface.h"
#include "synth/Synth.h"
#include "tour/TourCharLocal.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

INIT_REVS(ProfileMgr);
MicClientID sNullMicClientID;
ProfileMgr TheProfileMgr;

typedef void (Game::*GameFunc)(float);

namespace {
    const float kNotForcingGain = -1.0f;

    void SetVolume(float f1, GameFunc func) {
        if (TheGame) {
            (TheGame->*func)(f1);
        }
    }
}

ProfileMgr::ProfileMgr()
    : mPlatformAudioLatency(0), mPlatformVideoLatency(50.0f),
      mInGameExtraVideoLatency(70.0f), mInGameSyncOffsetAdjustment(0),
      mGlobalOptionsSaveState(kMetaProfileUnloaded), mGlobalOptionsDirty(0),
      mBackgroundVolume(11), mForegroundVolume(11), mFxVolume(11), mCrowdVolume(11),
      mVocalCueVolume(11), mVoiceChatVolume(11), mHasSeenFirstTimeCalibration(0),
      mHasConnectedProGuitar(0), mSyncOffset(0), mSongToTaskMgrMs(0), mBassBoost(0),
      mDolby(0), unk582(0), mSyncPresetIx(0), mOverscan(0), mSynapseEnabled(1), unk58a(1),
      mSecondPedalHiHat(0), mWiiSpeakToggle(1), mWiiSpeakFriendsVolume(6),
      mWiiSpeakMicrophoneSensitivity(3), mWiiSpeakHeadphoneMode(0),
      mWiiSpeakEchoSuppression(1), mHasLoaded(0), mWiiFriendsPromptShown(0),
      mUsingWiiFriends(0), unk5b8(0), mCymbalConfiguration(0), mPrimaryProfile(0),
      mAllUnlocked(0) {
    mSyncOffset = -mPlatformVideoLatency;
    mSongToTaskMgrMs = mPlatformVideoLatency - mPlatformAudioLatency;
    for (int i = 0; i < 3; i++) {
        mMicVolumes.push_back(8);
        mForcedMicGains.push_back(kNotForcingGain);
    }
    for (int i = 0; i < kJoypadNumTypes; i++) {
        for (int j = 0; j < kNumLagContexts; j++) {
            mJoypadExtraLagOffsets[i][j] =
                GetJoypadExtraLagInits((JoypadType)i, (LagContext)j);
        }
    }
    UpdatePrimaryProfile();
}

void ProfileMgr::Init() {
    SystemConfig("profile_mgr");
    for (int i = 0; i < 4; i++) {
        mProfiles.push_back(new BandProfile(i));
    }
    SetName("profile_mgr", ObjectDir::Main());
    TheNetSession->AddSink(this);
    TheServer->AddSink(this, UserLoginMsg::Type());
    TheRockCentral.AddSink(this);
    TheGameMicManager->AddSink(this, GameMicsChangedMsg::Type());
    TheSaveLoadMgr->AddSink(this, SaveLoadMgrStatusUpdateMsg::Type());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    InitSliders();
    SetExcessVideoLag(0);
}

DECOMP_FORCEACTIVE(ProfileMgr, "signin_changed")

void ProfileMgr::Poll() {
    FOREACH (it, mProfiles) {
        (*it)->Poll();
    }
}

std::vector<BandProfile *> ProfileMgr::GetParticipatingProfiles() {
    std::vector<BandProfile *> signedInProfiles = GetSignedInProfiles();
    std::vector<BandProfile *> profiles;
    for (int i = 0; i < signedInProfiles.size(); i++) {
        BandProfile *profile = signedInProfiles[i];
        MILO_ASSERT(profile, 0x117);
        std::vector<LocalBandUser *> users;
        profile->GetAssociatedUsers(users);
        bool push = false;
        FOREACH (it, users) {
            if ((*it)->IsParticipating()) {
                push = true;
                break;
            }
        }
        if (push) {
            profiles.push_back(profile);
        }
    }
    return profiles;
}

std::vector<BandProfile *> ProfileMgr::GetSignedInProfiles() {
    std::vector<BandProfile *> profiles;
    FOREACH (it, mProfiles) {
        if (ThePlatformMgr.IsSignedIn((*it)->GetPadNum())) {
            profiles.push_back(*it);
        }
    }
    return profiles;
}

std::vector<BandProfile *> ProfileMgr::GetNewlySignedInProfiles() {
    std::vector<BandProfile *> profiles;
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        int pad = cur->GetPadNum();
        if (ThePlatformMgr.IsSignedIn(pad) && !ThePlatformMgr.IsPadAGuest(pad)
            && !cur->GetSaveState()) {
            profiles.push_back(*it);
        }
    }
    return profiles;
}

std::vector<BandProfile *> ProfileMgr::GetShouldAutosaveProfiles() {
    std::vector<BandProfile *> profiles;
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        int pad = cur->GetPadNum();
        if (ThePlatformMgr.IsSignedIn(pad) && TheWiiProfileMgr.GetIndexForPad(pad) >= 0
            && cur->GetSaveState() == 1 && cur->IsUnsaved()) {
            profiles.push_back(cur);
        }
    }
    return profiles;
}

BandProfile *ProfileMgr::GetProfileFromPad(int pad) {
    BandProfile *ret = nullptr;
    FOREACH (it, mProfiles) {
        if (pad == (*it)->GetPadNum()) {
            ret = *it;
            break;
        }
    }
    return ret;
}

GameplayOptions *ProfileMgr::GetGameplayOptionsFromUser(LocalBandUser *user) {
    BandProfile *profile = GetProfileForUser(user);
    if (profile)
        return &profile->mGameplayOptions;
    else
        return nullptr;
}

bool ProfileMgr::IsAutosaveEnabled(const LocalBandUser *user) {
    BandProfile *profile = GetProfileForUser(user);
    return profile && profile->GetSaveState() != 2;
}

BandProfile *ProfileMgr::GetProfileForUser(const LocalUser *user) {
    if (user && user->IsLocal() && user->CanSaveData()) {
        return GetProfileFromPad(user->GetPadNum());
    } else
        return nullptr;
}

BandProfile *ProfileMgr::GetProfileForChar(const TourCharLocal *tourchar) {
    for (int i = 0; i < mProfiles.size(); i++) {
        BandProfile *cur = mProfiles[i];
        if (cur->HasValidSaveData() && cur->HasChar(tourchar))
            return cur;
    }
    return nullptr;
}

BandProfile *ProfileMgr::GetProfileForChar(const BandCharDesc *desc) {
    for (int i = 0; i < mProfiles.size(); i++) {
        BandProfile *cur = mProfiles[i];
        if (cur->HasValidSaveData()) {
            std::vector<TourCharLocal *> chars;
            cur->GetAllChars(chars);
            for (int c = 0; c < chars.size(); c++) {
                BandCharDesc *curChar = chars[c]->GetBandCharDesc();
                if (curChar->IsSameCharDesc(*desc))
                    return cur;
            }
        }
    }
    return nullptr;
}

bool ProfileMgr::HasUnsavedDataForPad(int padNum) {
    MILO_ASSERT(padNum != -1, 0x214);
    BandProfile *profile = GetProfileFromPad(padNum);
    return ThePlatformMgr.IsSignedIn(padNum) && profile->GetSaveState() == 1
        && profile->IsUnsaved();
}

UNPOOL_DATA
void ProfileMgr::PurgeOldData() {
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        if (cur->GetSaveState() == 3) {
            static ProfilePreDeleteMsg preDeleteMsg(cur);
            preDeleteMsg[0] = cur;
            Handle(preDeleteMsg, false);
            cur->DeleteAll();
            cur->SetSaveState(kMetaProfileUnloaded);
            static ProfileChangedMsg profileChangedMsg(cur);
            profileChangedMsg[0] = cur;
            Handle(profileChangedMsg, false);
        }
    }
}
END_UNPOOL_DATA

BandProfile *ProfileMgr::FindTourProgressOwner(const TourProgress *tp) {
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        if (cur->HasValidSaveData() && cur->OwnsTourProgress(tp))
            return cur;
    }
    return nullptr;
}

BandProfile *ProfileMgr::FindCharOwnerFromGuid(const HxGuid &guid) {
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        if (cur->HasValidSaveData() && cur->GetCharFromGuid(guid))
            return cur;
    }
    return nullptr;
}

void ProfileMgr::HandlePendingGamerpicRewards() {
    std::vector<BandProfile *> profiles = GetSignedInProfiles();
    FOREACH (it, profiles) {
        BandProfile *cur = *it;
        if (cur->HasValidSaveData()) {
            cur->AccessAccomplishmentProgress().HandlePendingGamerRewards();
        }
    }
}

void ProfileMgr::CheckProfileWebLinkStatus() {
    if (TheRockCentral.IsOnline()) {
        std::vector<BandProfile *> profiles = GetSignedInProfiles();
        FOREACH (it, profiles) {
            BandProfile *cur = *it;
            if (cur->HasValidSaveData()) {
                LocalBandUser *pUser = cur->GetAssociatedLocalBandUser();
                MILO_ASSERT(pUser, 0x29C);
                int padnum = cur->GetPadNum();
                Server *netServer = TheNet.GetServer();
                MILO_ASSERT(netServer, 0x2A0);
                if (netServer->GetPlayerID(padnum)) {
                    const AccomplishmentProgress &prog = cur->GetAccomplishmentProgress();
                    if (!prog.IsAccomplished(acc_accountlink)) {
                        cur->CheckWebLinkStatus();
                    }
                }
            }
        }
    }
}

void ProfileMgr::CheckProfileWebSetlistStatus() {
    if (TheRockCentral.IsOnline()) {
        std::vector<BandProfile *> profiles = GetSignedInProfiles();
        FOREACH (it, profiles) {
            BandProfile *cur = *it;
            if (cur->HasValidSaveData()) {
                LocalBandUser *pUser = cur->GetAssociatedLocalBandUser();
                MILO_ASSERT(pUser, 0x2C9);
                int padnum = cur->GetPadNum();
                Server *netServer = TheNet.GetServer();
                MILO_ASSERT(netServer, 0x2CD);
                if (netServer->GetPlayerID(padnum)) {
                    const AccomplishmentProgress &prog = cur->GetAccomplishmentProgress();
                    if (!prog.IsAccomplished(acc_createsetlist)) {
                        cur->CheckWebSetlistStatus();
                    }
                }
            }
        }
    }
}

void ProfileMgr::HandlePendingProfileUploads() {
    if (TheRockCentral.IsOnline()) {
        std::vector<BandProfile *> profiles = GetSignedInProfiles();
        FOREACH (it, profiles) {
            BandProfile *cur = *it;
            if (cur->HasValidSaveData()) {
                int padnum = cur->GetPadNum();
                Server *netServer = TheNet.GetServer();
                MILO_ASSERT(netServer, 0x2F6);
                if (netServer->GetPlayerID(padnum)) {
                    cur->UploadDirtyData();
                    AccomplishmentProgress &prog = cur->AccessAccomplishmentProgress();
                    if (prog.IsHardCoreStatusUpdatePending()) {
                        prog.SendHardCoreStatusUpdateToRockCentral();
                    }
                }
            }
        }
    }
}

void ProfileMgr::SyncProfileSetlists() {
    if (TheRockCentral.IsOnline()) {
        std::vector<BandProfile *> profiles = GetSignedInProfiles();
        TheRockCentral.SyncSetlists(profiles, mDataResults, nullptr);
    }
}

DataNode ProfileMgr::OnMsg(const SaveLoadMgrStatusUpdateMsg &msg) {
    if (msg->Int(2) == 4) {
        SyncProfileSetlists();
    }
    return 1;
}

DataNode ProfileMgr::OnMsg(const UserLoginMsg &) {
    CheckProfileWebLinkStatus();
    CheckProfileWebSetlistStatus();
    HandlePendingProfileUploads();
    return 1;
}

DataNode ProfileMgr::OnMsg(const ServerStatusChangedMsg &) { return 1; }

DataNode ProfileMgr::OnMsg(const GameMicsChangedMsg &) {
    UpdateAllMicLevels();
    return 1;
}

bool ProfileMgr::NeedsUpload() {
    if (mAllUnlocked)
        return false;
    FOREACH (it, mProfiles) {
        BandProfile *cur = *it;
        if (cur->HasValidSaveData() && cur->HasSomethingToUpload())
            return true;
    }
    return false;
}

bool ProfileMgr::GetAllUnlocked() { return mAllUnlocked; }
int ProfileMgr::GetMaxCharacters() const { return 10; }

bool ProfileMgr::UnlockAllSongs() {
    bool old = mAllUnlocked;
    mAllUnlocked = true;
    return old == 0;
}

void ProfileMgr::RelockSongs() { mAllUnlocked = false; }

void ProfileMgr::SetGlobalOptionsSaveState(ProfileSaveState state) {
    MILO_ASSERT(mGlobalOptionsSaveState != kMetaProfileUnchanged, 0x396);
    if (state != kMetaProfileUnchanged)
        mGlobalOptionsSaveState = state;
}

bool ProfileMgr::GlobalOptionsNeedsSave() {
    if (mGlobalOptionsSaveState != kMetaProfileLoaded)
        return false;
    else
        return mGlobalOptionsDirty;
}

int ProfileMgr::GetGlobalOptionsSize() { return TheModifierMgr->SaveSize(gRev) + 0x52; }

void ProfileMgr::SaveGlobalOptions(FixedSizeSaveableStream &bs) {
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

void ProfileMgr::LoadGlobalOptions(FixedSizeSaveableStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(7, 2);
    bs >> mSyncOffset;
    bs >> mSongToTaskMgrMs;
    if (gRev != 0) {
        bs >> mBackgroundVolume;
        bs >> mForegroundVolume;
    } else {
        bs >> mBackgroundVolume;
        mForegroundVolume = mBackgroundVolume;
    }
    bs >> mFxVolume;
    if (gRev != 0)
        bs >> mVocalCueVolume;
    bs >> mBassBoost;
    bs >> mCrowdVolume;
    bs >> mDolby;
    bs >> mSyncPresetIx;
    bs >> mOverscan;
    if (gRev > 1) {
        if (gRev > 2)
            bs >> mSynapseEnabled;
        else {
            bool b;
            bs >> b;
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
    if (gRev > 4)
        bs >> mSecondPedalHiHat;
    if (gRev >= 7)
        TheModifierMgr->Load(bs, gRev);
    String str;
    bs >> str;
    bool b46;
    bs >> b46;
    long long lol;
    bs >> lol;
    if (gAltRev >= 1) {
        bs >> mWiiFriendsPromptShown;
        bs >> mUsingWiiFriends;
    }
    if (gAltRev >= 2)
        bs >> unk5b8;
    mHasLoaded = true;
    mGlobalOptionsDirty = false;
    PushAllOptions();
}

void ProfileMgr::InitSliders() {
    if (!mSliderConfig) {
        mSliderConfig = SystemConfig("sound", "slider");
    }
    if (!mVoiceChatSliderConfig) {
        mVoiceChatSliderConfig = SystemConfig("sound", "slider_voicechat");
    }
}

float ProfileMgr::SliderIxToDb(int ixVol) const {
    MILO_ASSERT(mSliderConfig, 0x4C0);
    MILO_ASSERT(0 <= ixVol && ixVol < mSliderConfig->Size() - 1, 0x4C1);
    return mSliderConfig->Float(ixVol + 1);
}

void ProfileMgr::GetMicGainInfo(
    const Symbol &s, float &f1, float &f2, float &f3, float &f4
) const {
    MILO_LOG("Mic:%s\n", s);
    DataArray *cfg = SystemConfig("sound", "ratio_sliders", s);
    DataArray *arr = cfg->Array(1);
    f1 = arr->Float(0);
    f2 = arr->Float(1);
    f3 = arr->Float(2);
    f4 = arr->Float(3);
}

int ProfileMgr::GetSliderStepCount() const {
    MILO_ASSERT(mSliderConfig, 0x4D3);
    return mSliderConfig->Size() - 1;
}

void ProfileMgr::PushAllOptions() {
    SetVolume(GetBackgroundVolumeDb(), &Game::SetBackgroundVolume);
    SetVolume(GetForegroundVolumeDb(), &Game::SetForegroundVolume);

    Fader *bgFade = TheSynth->Find<Fader>("background_music_level.fade", true);
    if (bgFade) {
        bgFade->SetVal(GetBackgroundVolumeDb());
    }
    Fader *crowdFade = TheSynth->Find<Fader>("crowd_level.fade", true);
    if (crowdFade) {
        crowdFade->SetVal(GetCrowdVolumeDb());
    }
    if (TheGame) {
        BeatMaster *bm = TheGame->GetBeatMaster();
        if (bm) {
            bm->GetAudio()->SetBaseCrowdFader(GetCrowdVolumeDb());
        }
    }
    Fader *sfxFade = TheSynth->Find<Fader>("sfx_level.fade", true);
    if (sfxFade) {
        sfxFade->SetVal(GetFxVolumeDb());
    }
    Fader *instFade = TheSynth->Find<Fader>("instrument_level.fade", true);
    if (instFade) {
        instFade->SetVal(GetForegroundVolumeDb());
    }
    FxSend *bassSend = TheSynth->Find<FxSend>("bass_boost.send", true);
    if (bassSend) {
        if (GetBassBoost()) {
            bassSend->SetProperty("wet_gain", 0.0f);
            bassSend->SetProperty("dry_gain", -96.0f);
        } else {
            bassSend->SetProperty("wet_gain", -96.0f);
            bassSend->SetProperty("dry_gain", 0.0f);
        }
    }
    if (TheGame) {
        TheGame->SetVocalCueVolume(GetVocalCueVolumeDb());
        std::vector<Player *> &players = TheGame->GetActivePlayers();
        FOREACH (it, players) {
            BandUser *user = (*it)->GetUser();
            int i9 = -1;
            if (user->IsLocal()) {
                i9 = user->GetLocalBandUser()->GetPadNum();
            }
            (*it)->SetSyncOffset(GetSyncOffset(i9));
        }
    }
    if (mOverscan != TheRnd->GetOverscan()) {
        TheRnd->SetOverscan(mOverscan);
        TheRnd->ConfigureRenderMode();
        TheRnd->ChangeYScale(true);
    }
    TheGameMicManager->unk2f = mSynapseEnabled;
    TheSynth->SetDolby(mDolby, false);
    MILO_ASSERT(mVoiceChatSliderConfig, 0x534);
    MILO_ASSERT(0 <= mVoiceChatVolume && mVoiceChatVolume < mVoiceChatSliderConfig->Size() - 1, 0x535);
    TheSynth->SetIncomingVoiceChatVolume(
        mVoiceChatSliderConfig->Float(mVoiceChatVolume + 1)
    );
    static DataNode &cv = DataVariable("crowd_audio.volume");
    cv = GetCrowdVolumeDb();
    TheWiiFriendMgr.UseConsoleFriends(mUsingWiiFriends);
}

void ProfileMgr::SetBackgroundVolume(int vol) {
    mBackgroundVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetForegroundVolume(int vol) {
    mForegroundVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetFxVolume(int vol) {
    mFxVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

FORCE_LOCAL_INLINE
int ProfileMgr::GetFxVolume() const {
    if (!unk582)
        return mFxVolume;
    else
        return 0;
}
END_FORCE_LOCAL_INLINE

void ProfileMgr::SetCrowdVolume(int vol) {
    mCrowdVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetVocalCueVolume(int vol) {
    if (vol < 0 || GetSliderStepCount() <= vol)
        return;
    else {
        mVocalCueVolume = vol;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

void ProfileMgr::SetVoiceChatVolume(int vol) {
    mVoiceChatVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetBassBoost(bool b) {
    mBassBoost = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetDolby(bool b) {
    mDolby = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetOverscan(bool b) {
    if (b != mOverscan) {
        mOverscan = b;
        TheRnd->SetOverscan(mOverscan);
        TheRnd->ConfigureRenderMode();
        TheRnd->ChangeYScale(true);
        mGlobalOptionsDirty = true;
    }
}

void ProfileMgr::SetSynapseEnabled(bool b) {
    mSynapseEnabled = b;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetWiiSpeakToggle(bool b) {
    mWiiSpeakToggle = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiSpeakFriendsVolume(int vol) {
    mWiiSpeakFriendsVolume = vol;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiSpeakMicrophoneSensitivity(int sense) {
    mWiiSpeakMicrophoneSensitivity = sense;
    mGlobalOptionsDirty = true;
}

UNPOOL_DATA
void ProfileMgr::SetWiiSpeakHeadphoneMode(bool b1) {
    static Symbol error_message("error_message");
    static Message msg("init", 0);
    if (b1) {
        msg[0] = Symbol("passive_message_use_headphones");
    } else {
        msg[0] = Symbol("passive_message_dont_use_headphones");
    }
    TheUIEventMgr->TriggerEvent(error_message, msg);
    mWiiSpeakHeadphoneMode = b1;
    mGlobalOptionsDirty = true;
}
END_UNPOOL_DATA

void ProfileMgr::SetWiiSpeakEchoSuppression(bool b) {
    mWiiSpeakEchoSuppression = b;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::GetHasSeenFirstTimeCalibration() const {
    return mHasSeenFirstTimeCalibration;
}

void ProfileMgr::SetHasSeenFirstTimeCalibration(bool b) {
    mHasSeenFirstTimeCalibration = b;
    mGlobalOptionsDirty = true;
}

int ProfileMgr::GetFirstTimeInstrumentFlag(JoypadType ty) const {
    int ret = 0;
    switch (ty) {
    case kJoypadNone:
        break;
    case kJoypadWiiCore:
    case kJoypadWiiFS:
        ret = 1;
        break;
    case kJoypadWiiGuitar:
    case kJoypadWiiHxGuitar:
    case kJoypadWiiHxGuitarRb2:
    case kJoypadWiiCoreGuitar:
        ret = 2;
        break;
    case kJoypadWiiDrums:
    case kJoypadWiiHxDrums:
    case kJoypadWiiHxDrumsRb2:
        ret = 4;
        break;
    case kJoypadWiiKeytar:
        ret = 8;
        break;
    case kJoypadWiiButtonGuitar:
        ret = 0x10;
        break;
    case kJoypadWiiRealGuitar22Fret:
        ret = 0x20;
        break;
    case kJoypadWiiMidiBoxKeyboard:
    case kJoypadWiiMidiBoxDrums:
        ret = 0x40;
        break;
    default:
        MILO_ASSERT(0, 0x637);
        break;
    }
    return ret;
}

DECOMP_FORCEACTIVE(ProfileMgr, "PlatformAudioLatency:%f\n", "PlatformVideoLatency:%f\n")

bool ProfileMgr::GetHasSeenFirstTimeInstruments(const LocalUser *u) const {
    if (u) {
        int wiiFlags = TheWiiProfileMgr.GetHasSeenFirstTimeInstrumentFlagsForUser(u);
        int userFlags = GetFirstTimeInstrumentFlag((JoypadType)u->GetPadType());
        return wiiFlags & userFlags;
    } else
        return false;
}

void ProfileMgr::SetHasSeenFirstTimeInstruments(const LocalUser *u, bool high) {
    if (u) {
        TheWiiProfileMgr.SetHasSeenFirstTimeInstrumentFlagsForUser(
            u, GetFirstTimeInstrumentFlag((JoypadType)u->GetPadType()), high
        );
    }
}

bool ProfileMgr::GetHasConnectedProGuitar() const { return mHasConnectedProGuitar; }

void ProfileMgr::SetHasConnectedProGuitar(bool b) {
    mHasConnectedProGuitar = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetWiiFriendsPromptShown() {
    mWiiFriendsPromptShown = true;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetUsingWiiFriends(int i1) {
    mGlobalOptionsDirty = true;
    mUsingWiiFriends = i1 != 0;
    TheWiiFriendMgr.UseConsoleFriends(mUsingWiiFriends);
    TheRockCentral.UpdateOnlineStatus();
    TheSaveLoadMgr->AutoSave();
}

bool ProfileMgr::GetUsingWiiFriends() { return mUsingWiiFriends; }

bool ProfileMgr::GetSecondPedalHiHat() const { return mSecondPedalHiHat; }

void ProfileMgr::SetSecondPedalHiHat(bool b) {
    mSecondPedalHiHat = b;
    mGlobalOptionsDirty = true;
}

void ProfileMgr::SetSyncPresetIx(int ix) {
    mSyncPresetIx = ix;
    mGlobalOptionsDirty = true;
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetSongToTaskMgrMsRaw() const { return mSongToTaskMgrMs; }
END_FORCE_LOCAL_INLINE

void ProfileMgr::SetSongToTaskMgrMsRaw(float ms) {
    if (mSongToTaskMgrMs != ms) {
        mSongToTaskMgrMs = ms;
        mGlobalOptionsDirty = true;
    }
}

float ProfileMgr::GetJoypadExtraLag(JoypadType type, LagContext ctx) const {
    MILO_ASSERT_RANGE(type, 0, kJoypadNumTypes, 0x6DE);
    MILO_ASSERT_RANGE(ctx, 0, kNumLagContexts, 0x6DF);
    return mJoypadExtraLagOffsets[type][ctx];
}

void ProfileMgr::SetJoypadExtraLag(JoypadType type, LagContext ctx, float lag) {
    MILO_ASSERT_RANGE(type, 0, kJoypadNumTypes, 0x6E5);
    MILO_ASSERT_RANGE(ctx, 0, kNumLagContexts, 0x6E6);
    mJoypadExtraLagOffsets[type][ctx] = lag;
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetPadExtraLag(int pad, LagContext ctx) const {
    return mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][ctx];
}
END_FORCE_LOCAL_INLINE

void ProfileMgr::SetPlatformAudioLatency(float lat) { mPlatformAudioLatency = lat; }
void ProfileMgr::SetPlatformVideoLatency(float lat) { mPlatformVideoLatency = lat; }
float ProfileMgr::GetInGameExtraVideoLatency() const { return mInGameExtraVideoLatency; }
void ProfileMgr::SetInGameExtraVideoLatency(float lat) { mInGameExtraVideoLatency = lat; }
float ProfileMgr::GetInGameSyncOffsetAdjustment() const {
    return mInGameSyncOffsetAdjustment;
}
void ProfileMgr::SetInGameSyncOffsetAdjustment(float adj) {
    mInGameSyncOffsetAdjustment = adj;
}

float ProfileMgr::GetSyncOffset(int pad) const {
    float lag = 0;
    if (pad != -1) {
        lag = GetPadExtraLag(pad, kGame);
    }
    return (GetSyncOffsetRaw() + mInGameSyncOffsetAdjustment) - lag;
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetSyncOffsetRaw() const { return mSyncOffset; }
END_FORCE_LOCAL_INLINE

void ProfileMgr::SetSyncOffsetRaw(float offset) {
    if (mSyncOffset != offset) {
        mSyncOffset = offset;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

float ProfileMgr::GetExcessVideoLag() const {
    return -(mPlatformVideoLatency + GetSyncOffsetRaw());
}

void ProfileMgr::SetExcessVideoLag(float lag) {
    float audioLag = GetExcessAudioLag();
    SetSyncOffsetRaw(-(lag + mPlatformVideoLatency));
    SetExcessAudioLag(audioLag);
}

float ProfileMgr::GetPlatformAudioLatency() const { return mPlatformAudioLatency; }
float ProfileMgr::GetPlatformVideoLatency() const { return mPlatformVideoLatency; }

float ProfileMgr::GetExcessAudioLagNeutral(int pad, bool b) const {
    return mPlatformAudioLatency + GetPadExtraLag(pad, b ? kACal : kGame);
}

float ProfileMgr::GetExcessVideoLagNeutral(int pad, bool b) const {
    LagContext ctx = (LagContext)(b != 0);
    return mPlatformVideoLatency + GetPadExtraLag(pad, ctx);
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetExcessAudioLag() const {
    return -(mPlatformAudioLatency + GetSongToTaskMgrMsRaw() + GetSyncOffsetRaw());
}
END_FORCE_LOCAL_INLINE

void ProfileMgr::SetExcessAudioLag(float lag) {
    SetSongToTaskMgrMsRaw(-(lag + mPlatformAudioLatency + GetSyncOffsetRaw()));
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetBackgroundVolumeDb() const {
    return SliderIxToDb(GetBackgroundVolume());
}
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
float ProfileMgr::GetForegroundVolumeDb() const {
    return SliderIxToDb(GetForegroundVolume());
}
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
float ProfileMgr::GetFxVolumeDb() const { return SliderIxToDb(GetFxVolume()); }
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
float ProfileMgr::GetCrowdVolumeDb() { return SliderIxToDb(GetCrowdVolume()); }
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
float ProfileMgr::GetVocalCueVolumeDb() { return SliderIxToDb(GetVocalCueVolume()); }
END_FORCE_LOCAL_INLINE

float ProfileMgr::GetVoiceChatVolumeDb() { return SliderIxToDb(GetVoiceChatVolume()); }

void ProfileMgr::SetMicVol(int i1, int i2) {
    if (!(i1 >= 0 && i1 < mMicVolumes.size()))
        return;
    if (!(i2 >= 0 && GetSliderStepCount() > i2))
        return;
    if (i2 != mMicVolumes[i1]) {
        mMicVolumes[i1] = i2;
    }
}

int ProfileMgr::GetMicVol(int i1) const {
    if (i1 < 0 || i1 >= mMicVolumes.size())
        return 0;
    else
        return mMicVolumes[i1];
}

void ProfileMgr::UpdateMicLevels(int i1) {
    int micID = TheSynth->GetMicClientMapper()->GetMicIDForClientID(MicClientID(i1, -1));
    if (micID != -1) {
        Mic *mic = TheSynth->GetMic(micID);
        if (mic && mic->IsConnected()) {
            int vol = GetMicVol(i1);
            float f38 = 0;
            float f3c = 0;
            float f40 = 1;
            float f44 = 1;
            GetMicGainInfo(mic->GetName(), f38, f3c, f40, f44);
            float f1 = -1.0f;
            if (i1 < mForcedMicGains.size()) {
                f1 = mForcedMicGains[i1];
            }
            if (f1 == -1.0f) {
                float i7 = SliderIxToDb(vol);
                if (vol == 0)
                    i7 = -96.0f;
                mic->SetVolume(i7);
                mic->SetGain(f38);
                mic->SetOutputGain(DbToRatio(f3c));
                mic->SetSensitivity(f40);
                mic->unk8 = f44;
                UpdateMultiMicDeviceSliders(mic, 9);
            } else {
                mic->SetVolume(SliderIxToDb(vol));
                mic->SetGain(f1);
            }
#ifdef MILO_DEBUG
            static DataNode &n = DataVariable("print_mic_gains");
            if (n.Int()) {
                float gain = mic->GetGain();
                if (f1 == -1) {
                    MILO_LOG("Mic gain is %f\n", gain);
                } else {
                    MILO_LOG(
                        "Mic gain is forced to %f (would be %f if not forcing)\n",
                        gain,
                        f38
                    );
                }
            }
#endif
        }
    }
}

void ProfileMgr::UpdateAllMicLevels() {
    for (int i = 0; i < 3; i++) {
        UpdateMicLevels(i);
    }
}

void ProfileMgr::UpdateMultiMicDeviceSliders(Mic *mic, int i2) {
    MILO_ASSERT(mic, 0x8F6);
    if (mic->IsMultiMicDevice()) {
        for (int i = 0; i < 3; i++) {
            int micID =
                TheSynth->GetMicClientMapper()->GetMicIDForClientID(MicClientID(i, -1));
            if (micID != -1) {
                Mic *myMic = TheSynth->GetMic(micID);
                if (mic != myMic) {
                    if (myMic->GetName() == mic->GetName()) {
                        if (myMic->GetGain() == mic->GetGain()) {
                            mMicVolumes[i] = i2;
                        }
                    }
                }
            }
        }
    }
}

void ProfileMgr::ForceMicGain(int i1, float f2) {
    if (i1 < 0 || i1 >= mForcedMicGains.size())
        return;
    if (f2 < 0)
        f2 = -1;
#ifdef MILO_DEBUG
    static DataNode &n = DataVariable("print_mic_gains");
    if (n.Int()) {
        MILO_LOG("Mic gain forcing: %s\n", f2 == -1 ? "INACTIVE" : "ACTIVE");
    }
#endif
    mForcedMicGains[i1] = f2;
    UpdateMicLevels(i1);
}

void ProfileMgr::ForceMicOutputGain(int i1, float f2) {
    if (i1 <= 2U) {
#ifdef MILO_DEBUG
        static DataNode &n = DataVariable("print_mic_gains");
        if (n.Int()) {
            MILO_LOG(
                "Mic output gain forcing: %s - output gain for mic %d is %f dB\n",
                f2 == 0 ? "INACTIVE" : "ACTIVE",
                i1,
                f2
            );
        }
#endif
        Mic *mic = TheSynth->GetMic(i1);
        if (mic && mic->IsConnected()) {
            mic->SetOutputGain(DbToRatio(f2));
        }
    }
}

unsigned int ProfileMgr::GetCymbalConfiguration() const { return mCymbalConfiguration; }

void ProfileMgr::SetCymbalConfiguration(unsigned int ui) {
    mCymbalConfiguration = ui;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::HasLoaded() { return mHasLoaded; }

int ProfileMgr::GetCount() const { return TheWiiProfileMgr.Count(0); }

int ProfileMgr::GetUnregisteredCount() const {
    return TheWiiProfileMgr.Count(0) - GetRegisteredCount();
}

FORCE_LOCAL_INLINE
int ProfileMgr::GetRegisteredCount() const { return TheWiiProfileMgr.Count(2); }
END_FORCE_LOCAL_INLINE

DataNode ProfileMgr::OnMsg(const SigninChangedMsg &msg) {
    for (unsigned int mask = msg.GetChangedMask(), i = 0; mask != 0; mask >>= 1, i++) {
        if (mask & 1) {
            BandProfile *pProfile = GetProfileFromPad(i);
            MILO_ASSERT(pProfile, 0x980);
            pProfile->SetSaveState(kMetaProfileDelete);
        }
    }
    UpdatePrimaryProfile();
    return 1;
}

DataNode ProfileMgr::OnMsg(const ProfileChangedMsg &) {
    UpdatePrimaryProfile();
    return DataNode(kDataUnhandled, 0);
}

bool ProfileMgr::ChooseNewPrimaryProfile() {
    for (int i = 0; i < mProfiles.size(); i++) {
        if (mProfiles[i]->HasValidSaveData()) {
            SetPrimaryProfile(mProfiles[i]);
            return true;
        }
    }
    return false;
}

void ProfileMgr::UpdatePrimaryProfile() {
    if (mPrimaryProfile) {
        if (!mPrimaryProfile->HasValidSaveData() && !ChooseNewPrimaryProfile()) {
            SetPrimaryProfile(nullptr);
        }
    } else
        ChooseNewPrimaryProfile();
}

bool ProfileMgr::CanChangePrimaryProfile() const {
    int count = 0;
    for (int i = 0; i < mProfiles.size(); i++) {
        BandProfile *cur = mProfiles[i];
        if (cur->HasValidSaveData()) {
            if (cur->GetAssociatedLocalBandUser()->IsParticipating()
                && cur != mPrimaryProfile) {
                count++;
            }
        }
    }
    return count > 0;
}

bool ProfileMgr::HasPrimaryProfile() const { return GetPrimaryProfile(); }

bool ProfileMgr::IsPrimaryProfileCritical(const LocalUser *user) {
    BandProfile *profile = GetPrimaryProfile();
    if (profile && user && GetProfileForUser(user) == profile) {
        if (TheGameMode->InMode("campaign") || TheGameMode->InMode("tour")
            || TheGameMode->InMode("qp_career_songinfo")
            || TheGameMode->InMode("qp_coop"))
            return true;
    }
    return false;
}

BandProfile *ProfileMgr::GetPrimaryProfile() const {
    if (mPrimaryProfile) {
        LocalBandUser *user = mPrimaryProfile->GetAssociatedLocalBandUser();
        MILO_ASSERT(user, 0xA07);
        if (!user->CanSaveData())
            return nullptr;
    }
    return mPrimaryProfile;
}

void ProfileMgr::SetPrimaryProfileByUser(const LocalUser *user) {
    MILO_ASSERT(user, 0xA15);
    BandProfile *p = GetProfileForUser(user);
    if (p)
        SetPrimaryProfile(p);
}

void ProfileMgr::SetPrimaryProfile(BandProfile *profile) {
    if (profile != mPrimaryProfile) {
        if (profile && !profile->HasValidSaveData())
            return;
        mPrimaryProfile = profile;
        static PrimaryProfileChangedMsg msg;
        Export(msg, true);
        BandMachineMgr *pMachineMgr = TheSessionMgr->GetMachineMgr();
        MILO_ASSERT(pMachineMgr, 0xA2A);
        pMachineMgr->RefreshPrimaryProfileInfo();
    }
}

void ProfileMgr::HandleProfileLoadComplete() {
    HandlePendingProfileUploads();
    HandlePendingGamerpicRewards();
}

void ProfileMgr::HandleProfileSaveComplete() {
    HandlePendingProfileUploads();
    HandlePendingGamerpicRewards();
}

void ProfileMgr::FakeProfileFill() {
    std::vector<BandProfile *> profiles = GetParticipatingProfiles();
    FOREACH (it, profiles) {
        BandProfile *profile = *it;
        MILO_ASSERT(profile, 0xA48);
        profile->FakeProfileFill();
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(ProfileMgr)
    HANDLE_EXPR(get_profile, GetProfileForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(get_save_data, GetProfileForUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_ACTION(
        set_primary_profile_by_user, SetPrimaryProfileByUser(_msg->Obj<LocalUser>(2))
    )
    HANDLE_EXPR(get_primary_profile, GetPrimaryProfile())
    HANDLE_EXPR(has_primary_profile, HasPrimaryProfile())
    HANDLE_EXPR(can_change_primary_profile, CanChangePrimaryProfile())
    HANDLE_ACTION(purge_old_data, PurgeOldData())
    HANDLE_EXPR(needs_upload, NeedsUpload())
    HANDLE_EXPR(get_profile_from_pad, GetProfileFromPad(_msg->Int(2)))
    HANDLE_EXPR(get_max_characters, GetMaxCharacters())
    HANDLE_EXPR(unlock_all_songs, UnlockAllSongs())
    HANDLE_ACTION(relock_songs, RelockSongs())
    HANDLE_EXPR(get_all_unlocked, GetAllUnlocked())
    HANDLE_EXPR(global_options_needs_save, GlobalOptionsNeedsSave())
    HANDLE_EXPR(get_background_volume, GetBackgroundVolume())
    HANDLE_EXPR(get_background_volume_db, GetBackgroundVolumeDb())
    HANDLE_EXPR(get_foreground_volume, GetForegroundVolume())
    HANDLE_EXPR(get_foreground_volume_db, GetForegroundVolumeDb())
    HANDLE_EXPR(get_fx_volume, GetFxVolume())
    HANDLE_EXPR(get_fx_volume_db, GetFxVolumeDb())
    HANDLE_EXPR(get_crowd_volume, GetCrowdVolume())
    HANDLE_EXPR(get_crowd_volume_db, GetCrowdVolumeDb())
    HANDLE_EXPR(get_vocal_cue_volume, GetVocalCueVolume())
    HANDLE_EXPR(get_vocal_cue_volume_db, GetVocalCueVolumeDb())
    HANDLE_EXPR(get_voice_chat_volume, GetVoiceChatVolume())
    HANDLE_EXPR(get_voice_chat_volume_db, GetVoiceChatVolumeDb())
    HANDLE_EXPR(get_bass_boost, GetBassBoost())
    HANDLE_EXPR(get_dolby, GetDolby())
    HANDLE_EXPR(get_overscan, GetOverscan())
    HANDLE_EXPR(get_wiispeak_toggle, GetWiiSpeakToggle())
    HANDLE_EXPR(get_wiispeak_friends_volume, GetWiiSpeakFriendsVolume())
    HANDLE_EXPR(get_wiispeak_microphone_sensitivity, GetWiiSpeakMicrophoneSensitivity())
    HANDLE_EXPR(get_wiispeak_headphone_mode, GetWiiSpeakHeadphoneMode())
    HANDLE_EXPR(get_wiispeak_echo_suppression, GetWiiSpeakEchoSuppression())
    HANDLE_EXPR(get_synapse_enabled, GetSynapseEnabled())
    HANDLE_EXPR(get_sync_preset_ix, GetSyncPresetIx())
    HANDLE_EXPR(get_sync_offset_raw, GetSyncOffsetRaw())
    HANDLE_EXPR(get_sync_offset, GetSyncOffset(_msg->Int(2)))
    HANDLE_EXPR(get_song_to_taskmgr_ms, GetSongToTaskMgrMs(kGame))
    HANDLE_EXPR(get_song_to_taskmgr_ms_raw, GetSongToTaskMgrMsRaw())
    HANDLE_EXPR(get_excess_audio_lag, GetExcessAudioLag())
    HANDLE_EXPR(get_excess_video_lag, GetExcessVideoLag())
    HANDLE_EXPR(get_pad_extra_lag, GetPadExtraLag(_msg->Int(2), kGame))
    HANDLE_EXPR(get_platform_audio_latency, GetPlatformAudioLatency())
    HANDLE_ACTION(set_platform_audio_latency, SetPlatformAudioLatency(_msg->Float(2)))
    HANDLE_EXPR(get_platform_video_latency, GetPlatformVideoLatency())
    HANDLE_ACTION(set_platform_video_latency, SetPlatformVideoLatency(_msg->Float(2)))
    HANDLE_EXPR(get_in_game_extra_video_latency, GetInGameExtraVideoLatency())
    HANDLE_ACTION(
        set_in_game_extra_video_latency, SetInGameExtraVideoLatency(_msg->Float(2))
    )
    HANDLE_EXPR(get_in_game_sync_offset_adjustment, GetInGameSyncOffsetAdjustment())
    HANDLE_ACTION(
        set_in_game_sync_offset_adjustment, SetInGameSyncOffsetAdjustment(_msg->Float(2))
    )
    HANDLE_EXPR(
        get_joypad_extra_lag,
        GetJoypadExtraLag((JoypadType)_msg->Int(2), (LagContext)_msg->Int(3))
    )
    HANDLE_ACTION(
        set_joypad_extra_lag,
        SetJoypadExtraLag(
            (JoypadType)_msg->Int(2), (LagContext)_msg->Int(3), _msg->Float(4)
        )
    )
    HANDLE_EXPR(get_mic_vol, GetMicVol(_msg->Int(2)))
    HANDLE_EXPR(get_has_seen_first_time_calibration, GetHasSeenFirstTimeCalibration())
    HANDLE_EXPR(
        get_has_seen_first_time_instruments,
        GetHasSeenFirstTimeInstruments(_msg->Obj<LocalBandUser>(2))
    )
    HANDLE_EXPR(get_second_pedal_hihat, GetSecondPedalHiHat())
    HANDLE_ACTION(set_background_volume, SetBackgroundVolume(_msg->Int(2)))
    HANDLE_ACTION(set_foreground_volume, SetForegroundVolume(_msg->Int(2)))
    HANDLE_ACTION(set_fx_volume, SetFxVolume(_msg->Int(2)))
    HANDLE_ACTION(set_crowd_volume, SetCrowdVolume(_msg->Int(2)))
    HANDLE_ACTION(set_vocal_cue_volume, SetVocalCueVolume(_msg->Int(2)))
    HANDLE_ACTION(set_voice_chat_volume, SetVoiceChatVolume(_msg->Int(2)))
    HANDLE_ACTION(set_bass_boost, SetBassBoost(_msg->Int(2)))
    HANDLE_ACTION(set_dolby, SetDolby(_msg->Int(2)))
    HANDLE_ACTION(set_overscan, SetOverscan(_msg->Int(2)))
    HANDLE_ACTION(set_wiispeak_toggle, SetWiiSpeakToggle(_msg->Int(2)))
    HANDLE_ACTION(set_wiispeak_friends_volume, SetWiiSpeakFriendsVolume(_msg->Int(2)))
    HANDLE_ACTION(
        set_wiispeak_microphone_sensitivity,
        SetWiiSpeakMicrophoneSensitivity(_msg->Int(2))
    )
    HANDLE_ACTION(set_wiispeak_headphone_mode, SetWiiSpeakHeadphoneMode(_msg->Int(2)))
    HANDLE_ACTION(set_wiispeak_echo_suppression, SetWiiSpeakEchoSuppression(_msg->Int(2)))
    HANDLE_ACTION(set_wii_friends_prompt_shown, SetWiiFriendsPromptShown())
    HANDLE_EXPR(get_should_show_wii_friends_prompt, GetShouldShowWiiFriendsPrompt())
    HANDLE_ACTION(set_using_wii_friends, SetUsingWiiFriends(_msg->Int(2)))
    HANDLE_EXPR(get_using_wii_friends, GetUsingWiiFriends())
    HANDLE_EXPR(get_count, GetCount())
    HANDLE_EXPR(get_unregistered_count, GetUnregisteredCount())
    HANDLE_EXPR(get_registered_count, GetRegisteredCount())
    HANDLE_ACTION(set_synapse_enabled, SetSynapseEnabled(_msg->Int(2)))
    HANDLE_ACTION(set_sync_preset_ix, SetSyncPresetIx(_msg->Int(2)))
    HANDLE_ACTION(set_sync_offset, SetSyncOffsetRaw(_msg->Float(2)))
    HANDLE_ACTION(set_song_to_taskmgr_ms, SetSongToTaskMgrMsRaw(_msg->Float(2)))
    HANDLE_ACTION(set_excess_audio_lag, SetExcessAudioLag(_msg->Float(2)))
    HANDLE_ACTION(set_excess_video_lag, SetExcessVideoLag(_msg->Float(2)))
    HANDLE_ACTION(set_mic_vol, SetMicVol(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(
        set_has_seen_first_time_calibration, SetHasSeenFirstTimeCalibration(_msg->Int(2))
    )
    HANDLE_ACTION(
        set_has_seen_first_time_instruments,
        SetHasSeenFirstTimeInstruments(_msg->Obj<LocalBandUser>(2), _msg->Int(3))
    )
    HANDLE_EXPR(is_autosave_enabled, IsAutosaveEnabled(_msg->Obj<LocalBandUser>(2)))
    HANDLE_ACTION(update_mic_levels, UpdateMicLevels(_msg->Int(2)))
    HANDLE_ACTION(update_all_mic_levels, UpdateAllMicLevels())
    HANDLE_ACTION(force_mic_gain, ForceMicGain(_msg->Int(2), _msg->Float(3)))
    HANDLE_ACTION(force_mic_output_gain, ForceMicOutputGain(_msg->Int(2), _msg->Float(3)))
    HANDLE_ACTION(fake_profile_fill, FakeProfileFill())
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(ProfileChangedMsg)
    HANDLE_MESSAGE(ServerStatusChangedMsg)
    HANDLE_MESSAGE(SaveLoadMgrStatusUpdateMsg)
    HANDLE_MESSAGE(UserLoginMsg)
    HANDLE_MESSAGE(GameMicsChangedMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xB42)
END_HANDLERS
#pragma pop
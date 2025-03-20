#include "meta_band/ProfileMgr.h"
#include "bandobj/BandCharDesc.h"
#include "beatmatch/BeatMaster.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Game.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/BandProfile.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/UIEventMgr.h"
#include "net/Net.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/PlatformMgr.h"
#include "rndobj/Rnd.h"
#include "synth/Faders.h"
#include "synth/FxSend.h"
#include "synth/Synth.h"
#include "tour/TourCharLocal.h"
#include "utl/Symbols2.h"

INIT_REVS(ProfileMgr);
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
      mWiiSpeakEchoSuppression(1), unk5b2(0), mWiiFriendsPromptShown(0),
      mUsingWiiFriends(0), unk5b8(0), mCymbalConfiguration(0), unk5d8(0),
      mAllUnlocked(0) {
    mSyncOffset = -mPlatformVideoLatency;
    mSongToTaskMgrMs = mPlatformVideoLatency - mPlatformAudioLatency;
    for (int i = 0; i < 3; i++) {
        unk5bc.push_back(8);
        unk5e0.push_back(kNotForcingGain);
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
    if (TheRockCentral.unk3c == 2) {
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
    if (TheRockCentral.unk3c == 2) {
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
    if (TheRockCentral.unk3c == 2) {
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
    if (TheRockCentral.unk3c == 2) {
        std::vector<BandProfile *> profiles = GetSignedInProfiles();
        TheRockCentral.SyncSetlists(profiles, unk58c, nullptr);
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
    unk5b2 = true;
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
    SetVolume(SliderIxToDb(mBackgroundVolume), &Game::SetBackgroundVolume);
    SetVolume(SliderIxToDb(mForegroundVolume), &Game::SetForegroundVolume);

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

int ProfileMgr::GetFxVolume() const {
    if (!unk582)
        return mFxVolume;
    else
        return 0;
}

void ProfileMgr::SetCrowdVolume(int vol) {
    mCrowdVolume = vol;
    mGlobalOptionsDirty = true;
    PushAllOptions();
}

void ProfileMgr::SetVocalCueVolume(int vol) {
    if (vol >= 0 && vol < GetSliderStepCount()) {
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

float ProfileMgr::GetSongToTaskMgrMsRaw() const { return mSongToTaskMgrMs; }

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

float ProfileMgr::GetPadExtraLag(int pad, LagContext ctx) const {
    return mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][ctx];
}

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
        lag = mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][0];
    }
    return (mSyncOffset + mInGameSyncOffsetAdjustment) - lag;
}

float ProfileMgr::GetSyncOffsetRaw() const { return mSyncOffset; }

void ProfileMgr::SetSyncOffsetRaw(float offset) {
    if (mSyncOffset != offset) {
        mSyncOffset = offset;
        mGlobalOptionsDirty = true;
        PushAllOptions();
    }
}

float ProfileMgr::GetExcessVideoLag() const {
    return -(mPlatformVideoLatency + mSyncOffset);
}

void ProfileMgr::SetExcessVideoLag(float lag) {
    SetSyncOffsetRaw(-(lag + mPlatformVideoLatency));
    SetExcessAudioLag(-(mPlatformAudioLatency + mSongToTaskMgrMs + mSyncOffset));
}

float ProfileMgr::GetPlatformAudioLatency() const { return mPlatformAudioLatency; }
float ProfileMgr::GetPlatformVideoLatency() const { return mPlatformVideoLatency; }

float ProfileMgr::GetExcessAudioLagNeutral(int pad, bool b) const {
    int i2 = 0;
    if (b)
        i2 = 2;
    return mPlatformAudioLatency
        + mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][i2];
}

float ProfileMgr::GetExcessVideoLagNeutral(int pad, bool b) const {
    return mPlatformVideoLatency
        + mJoypadExtraLagOffsets[JoypadGetPadData(pad)->mType][b];
}

float ProfileMgr::GetExcessAudioLag() const {
    return -(mPlatformAudioLatency + mSongToTaskMgrMs + mSyncOffset);
}

void ProfileMgr::SetExcessAudioLag(float lag) {
    SetSongToTaskMgrMsRaw(-(lag + mPlatformAudioLatency + mSyncOffset));
}

FORCE_LOCAL_INLINE
float ProfileMgr::GetBackgroundVolumeDb() const {
    return SliderIxToDb(mBackgroundVolume);
}
END_FORCE_LOCAL_INLINE

int ProfileMgr::GetBackgroundVolume() const { return mBackgroundVolume; }

FORCE_LOCAL_INLINE
float ProfileMgr::GetForegroundVolumeDb() const {
    return SliderIxToDb(mForegroundVolume);
}
END_FORCE_LOCAL_INLINE

int ProfileMgr::GetForegroundVolume() const { return mForegroundVolume; }

FORCE_LOCAL_INLINE
float ProfileMgr::GetFxVolumeDb() const { return SliderIxToDb(unk582 ? 0 : mFxVolume); }
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
float ProfileMgr::GetCrowdVolumeDb() { return SliderIxToDb(mCrowdVolume); }
END_FORCE_LOCAL_INLINE

int ProfileMgr::GetCrowdVolume() const { return mCrowdVolume; }

FORCE_LOCAL_INLINE
float ProfileMgr::GetVocalCueVolumeDb() { return SliderIxToDb(mVocalCueVolume); }
END_FORCE_LOCAL_INLINE

int ProfileMgr::GetVocalCueVolume() const { return mVocalCueVolume; }
float ProfileMgr::GetVoiceChatVolumeDb() { return SliderIxToDb(mVoiceChatVolume); }
int ProfileMgr::GetVoiceChatVolume() const { return mVoiceChatVolume; }

unsigned int ProfileMgr::GetCymbalConfiguration() const { return mCymbalConfiguration; }

void ProfileMgr::SetCymbalConfiguration(unsigned int ui) {
    mCymbalConfiguration = ui;
    mGlobalOptionsDirty = true;
}

bool ProfileMgr::HasLoaded() { return unk5b2; }

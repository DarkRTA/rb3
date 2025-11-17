#include "BandUser.h"
#include "bandtrack/Track.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandUI.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/CharData.h"
#include "meta_band/CharSync.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/MetaNetMsgs.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/Utl.h"
#include "net/NetSession.h"
#include "net/WiiFriendMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/System.h"
#include "os/User.h"
#include "tour/TourChar.h"
#include "tour/TourCharLocal.h"
#include "tour/TourCharRemote.h"
#include "utl/Symbols.h"

BandUser::BandUser()
    : mDifficulty(DefaultDifficulty()), unk_0xC(0), mTrackType(kTrackNone),
      mControllerType(kControllerNone), mHasButtonGuitar(0), mHas22FretGuitar(0),
      mPreferredScoreType(kScoreBand), mOvershellState(kState_JoinedDefault), mChar(0),
      mAutoplay(0), mLastHitFraction(0), mTrack(0), mPlayer(0), mParticipating(0),
      mIsWiiRemoteController(0), mJustDisconnected(0) {
    mPreviousAward = none;
}

BandUser::~BandUser() {}

LocalBandUser *BandUser::NewLocalBandUser() { return new LocalBandUser(); }

RemoteBandUser *BandUser::NewRemoteBandUser() { return new RemoteBandUser(); }

NullLocalBandUser *BandUser::NewNullLocalBandUser() { return new NullLocalBandUser(); }

void BandUser::Reset() {
    User::Reset();
    mOvershellState = kState_JoinedDefault;
    mDifficulty = DefaultDifficulty();
    unk_0xC = 0;
    mTrackType = kTrackNone;
    mControllerType = kControllerNone;
    mAutoplay = false;
    mPreviousAward = none;
    mParticipating = false;
    mChar = 0;
    mLastHitFraction = 0;
    mHasButtonGuitar = 0;
    mHas22FretGuitar = 0;
}

Difficulty BandUser::GetDifficulty() const { return mDifficulty; }

Symbol BandUser::GetDifficultySym() const { return DifficultyToSym(mDifficulty); }

void BandUser::SetDifficulty(Difficulty d) {
    MILO_ASSERT(IsLocal(), 0x74);
    MILO_ASSERT_RANGE(d, 0, kNumDifficulties, 0x75);
    Difficulty old = mDifficulty;
    unk_0xC = true;
    mDifficulty = d;
    if (old != d && mPlayer != nullptr) {
        mPlayer->ChangeDifficulty(d);
    }
    UpdateData(1);
}

bool BandUser::IsFullyInGame() const {
    bool ret = false;
    if (unk_0xC && mTrackType != kTrackPending && mTrackType != kTrackPendingVocals) {
        ret = true;
    }
    return ret;
}

void BandUser::SetDifficulty(Symbol s) { SetDifficulty(SymToDifficulty(s)); }

TrackType BandUser::GetTrackType() const { return mTrackType; }

Symbol BandUser::GetTrackSym() const { return TrackTypeToSym(mTrackType); }

const char *BandUser::GetTrackIcon() const {
    switch (mTrackType) {
    case kTrackNone:
    case kTrackPending:
    case kTrackPendingVocals:
        return GetFontCharFromControllerType(
            mControllerType, GetCurrentHardcoreIconLevel()
        );
    case kTrackVocals:
        if (mPlayer && mPlayer->GetSongNumVocalParts() > 1) {
            return GetFontCharForHarmonyMics(
                mPlayer->GetSongNumVocalParts(), GetCurrentHardcoreIconLevel()
            );
        }
    default:
        break;
    }

    if (mTrackType == kTrackDrum && mPreferredScoreType == kScoreRealDrum) {
        return GetFontCharForProDrums(GetCurrentHardcoreIconLevel());
    } else {
        return GetFontCharFromTrackType(mTrackType, GetCurrentHardcoreIconLevel());
    }
}

void BandUser::SetOvershellSlotState(OvershellSlotStateID id) {
    mOvershellState = id;
    UpdateData(1);
}

const char *BandUser::GetOvershellFocus() { return mOvershellFocus.c_str(); }

void BandUser::SetTrackType(TrackType ty) {
    MILO_ASSERT(IsLocal(), 0xC1);
    mTrackType = ty;
    UpdateData(1);
}

void BandUser::SetTrackType(Symbol s) { SetTrackType(SymToTrackType(s)); }

ScoreType BandUser::GetPreferredScoreType() const { return mPreferredScoreType; }

void BandUser::SetPreferredScoreType(ScoreType ty) {
    MILO_ASSERT(IsLocal(), 0xD2);
    mPreferredScoreType = ty;
    UpdateData(1);
}

ControllerType BandUser::GetControllerType() const { return mControllerType; }

Symbol BandUser::GetControllerSym() const { return ControllerTypeToSym(mControllerType); }

void BandUser::SetControllerType(ControllerType ty) {
    MILO_ASSERT(IsLocal(), 0xE4);
    mControllerType = ty;
    UpdateData(1);
}

void BandUser::SetControllerType(Symbol s) { SetControllerType(SymToControllerType(s)); }

void BandUser::SetHasButtonGuitar(bool b) {
    MILO_ASSERT(IsLocal(), 0xF0);
    mHasButtonGuitar = b;
    UpdateData(1);
}

void BandUser::BandUser::SetHas22FretGuitar(bool b) {
    MILO_ASSERT(IsLocal(), 0xF7);
    mHas22FretGuitar = b;
    UpdateData(1);
}

bool BandUser::HasChar() { return mChar; }

CharData *BandUser::GetChar() { return mChar; }

TourCharLocal *BandUser::GetCharLocal() {
    MILO_ASSERT(IsLocal(), 0x108);
    return dynamic_cast<TourCharLocal *>(mChar);
}

void BandUser::SetChar(CharData *cd) {
    MILO_ASSERT(IsLocal(), 0x110);
    if (mChar != cd) {
        mChar = nullptr;
        if (cd) {
            mChar = cd;
            if (TheCharSync && TheBandUserMgr->GetSlot(mUserGuid) != -1) {
                TheCharSync->UpdateCharCache();
            }
            BandProfile *profile = TheProfileMgr.GetProfileForUser(GetLocalBandUser());
            if (profile) {
                CharData *lastdata = nullptr;
                if (cd->IsCustomizable()) {
                    lastdata = dynamic_cast<TourCharLocal *>(cd);
                } else {
                    PrefabChar *pc = dynamic_cast<PrefabChar *>(cd);
                    if (pc) {
                        profile->SetLastPrefabCharUsed(pc->GetPrefabName());
                    }
                }
                profile->SetLastCharUsed(lastdata);
            }
        }
        UpdateData(2);
        if (DataVariable("send_fake_patches").Int()) {
            SendJunkPatchesToAll();
        }
    }
}

void BandUser::SetLoadedPrefabChar(int i1) {
    SetChar(PrefabMgr::GetPrefabMgr()->GetDefaultPrefab(i1));
}

int BandUser::GetSlot() const { return TheBandUserMgr->GetSlot(mUserGuid); }

GameplayOptions *BandUser::GetGameplayOptions() {
    if (!IsLocal())
        return &mGameplayOptions;
    else {
        GameplayOptions *opts =
            TheProfileMgr.GetGameplayOptionsFromUser(GetLocalBandUser());
        if (!opts)
            opts = &mGameplayOptions;
        return opts;
    }
}

const char *BandUser::IntroName() const { return UserName(); }

const char *BandUser::ProfileName() const {
    if (IsLocal()) {
        const LocalBandUser *pLocalUser = GetLocalBandUser();
        MILO_ASSERT(pLocalUser, 0x178);
        BandProfile *p = TheProfileMgr.GetProfileForUser(pLocalUser);
        if (p)
            return p->GetName();
    }
    return "";
}

void BandUser::DeletePlayer() {
    mPlayer = nullptr;
    if (mTrack)
        mTrack->RemovePlayer();
}

void BandUser::SyncSave(BinStream &bs, unsigned int flags) const {
    User::SyncSave(bs, flags);
    if (flags & 2) {
        bool charDataExists = mChar;
        bs << charDataExists;
        if (charDataExists) {
            PrefabChar *pChar = dynamic_cast<PrefabChar *>(mChar);
            bool prefabExists = pChar;
            bs << prefabExists;
            if (prefabExists) {
                bs << pChar->GetPrefabName();
            } else {
                TourChar *customChar = dynamic_cast<TourChar *>(mChar);
                MILO_ASSERT(customChar, 0x1A7);
                customChar->SyncSave(bs);
            }
        }
    }
    if (flags & 1) {
        bs << (unsigned char)mDifficulty;
        bs << (unsigned char)mTrackType;
        bs << (unsigned char)mControllerType;
        bs << mHasButtonGuitar;
        bs << mHas22FretGuitar;
        bs << GetCurrentInstrumentCareerScore();
        bs << (unsigned char)mOvershellState;
        bs << mOvershellFocus;
        bs << (unsigned char)mPreferredScoreType;
        bs << (unsigned char)GetCurrentHardcoreIconLevel();
        bs << (unsigned char)GetCymbalConfiguration();
    }
}

void BandUser::UpdateData(unsigned int data) {
    if (TheNetSession->HasUser(this)) {
        TheNetSession->UpdateUserData(this, data);
    }
}

DataNode BandUser::OnSetDifficulty(DataArray *da) {
    const DataNode &eval = da->Node(2).Evaluate();
    if (eval.Type() == kDataInt) {
        SetDifficulty((Difficulty)eval.Int());
    } else if (eval.Type() == kDataSymbol) {
        SetDifficulty(eval.Sym());
    } else if (eval.Type() == kDataString) {
        SetDifficulty(eval.ForceSym());
    } else
        MILO_FAIL("bad difficulty arg");
    return 1;
}

DataNode BandUser::OnSetTrackType(DataArray *da) {
    const DataNode &eval = da->Node(2).Evaluate();
    if (eval.Type() == kDataInt) {
        SetTrackType((TrackType)eval.Int());
    } else if (eval.Type() == kDataSymbol || eval.Type() == kDataString) {
        SetTrackType(eval.ForceSym());
    } else
        MILO_FAIL("bad TrackType arg");
    return 1;
}

DataNode BandUser::OnSetHas22FretGuitar(DataArray *da) {
    const DataNode &eval = da->Node(2).Evaluate();
    if (eval.Type() == kDataInt) {
        SetHas22FretGuitar(eval.Int());
    } else
        MILO_FAIL("bad bool arg");
    return 1;
}

DataNode BandUser::OnSetPreferredScoreType(DataArray *da) {
    const DataNode &eval = da->Node(2).Evaluate();
    if (eval.Type() == kDataInt) {
        SetPreferredScoreType((ScoreType)eval.Int());
    } else
        MILO_FAIL("bad ScoreType arg");
    return 1;
}

DataNode BandUser::OnSetControllerType(DataArray *da) {
    const DataNode &eval = da->Node(2).Evaluate();
    if (eval.Type() == kDataInt) {
        SetControllerType((ControllerType)eval.Int());
    } else if (eval.Type() == kDataSymbol || eval.Type() == kDataString) {
        SetControllerType(eval.ForceSym());
    } else
        MILO_FAIL("bad ControllerType arg");
    return 1;
}

DECOMP_FORCEACTIVE(BandUser, "%d")

DataNode BandUser::OnSetPrefabChar(DataArray *a) {
    Symbol sym = a->Sym(2);
    int i2 = a->Int(3);
    bool b1 = false;
    std::vector<PrefabChar *> prefabs;
    PrefabMgr::GetPrefabMgr()->GetPrefabs(prefabs);
    for (int i = 0; i < prefabs.size(); i++) {
        if (prefabs[i]->GetPrefabName() == sym) {
            b1 = true;
            SetChar(prefabs[i]);
            break;
        }
    }
    if (!b1)
        SetLoadedPrefabChar(i2);
    return 1;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandUser)
    HANDLE_EXPR(get_difficulty, GetDifficulty())
    HANDLE_EXPR(get_difficulty_sym, GetDifficultySym())
    HANDLE(set_difficulty, OnSetDifficulty)
    HANDLE_EXPR(intro_name, IntroName())
    HANDLE_EXPR(get_user_name, UserName())
    HANDLE_EXPR(get_slot_num, GetSlot())
    HANDLE_EXPR(get_track_type, GetTrackType())
    HANDLE_EXPR(get_track_sym, GetTrackSym())
    HANDLE_EXPR(get_track_icon, GetTrackIcon())
    HANDLE(set_track_type, OnSetTrackType)
    HANDLE_EXPR(get_preferred_score_type, GetPreferredScoreType())
    HANDLE(set_preferred_score_type, OnSetPreferredScoreType)
    HANDLE_EXPR(get_controller_type, GetControllerType())
    HANDLE_EXPR(get_controller_sym, GetControllerSym())
    HANDLE(set_controller_type, OnSetControllerType)
    HANDLE(set_has_22_fret_guitar, OnSetHas22FretGuitar)
    HANDLE_EXPR(get_gameplay_options, GetGameplayOptions())
    HANDLE_EXPR(is_participating, IsParticipating())
    HANDLE_EXPR(player, mPlayer)
    HANDLE_EXPR(get_player, mPlayer)
    HANDLE_EXPR(get_hardcore_icon_level, GetCurrentHardcoreIconLevel())
    HANDLE(set_prefab_char, OnSetPrefabChar)
    HANDLE_EXPR(has_char, mChar != 0)
    HANDLE_EXPR(is_char_customizable, mChar->IsCustomizable())
    HANDLE_EXPR(get_last_hit_fraction, GetLastHitFraction())
    HANDLE_ACTION(set_last_hit_fraction, SetLastHitFraction(_msg->Float(2)))
    HANDLE_SUPERCLASS(User)
    HANDLE_CHECK(0x2D5)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(BandUser)
    SYNC_PROP(autoplay, mAutoplay)
    SYNC_PROP(previous_award, mPreviousAward)
    SYNC_SUPERCLASS(User)
END_PROPSYNCS

LocalBandUser::LocalBandUser() : mControllerTypeOverride(kControllerNone) {
    unkc = 1;
    mHasSeenRealGuitarPrompt = 0;
}

LocalBandUser *LocalBandUser::GetLocalBandUser() { return this; }
LocalBandUser *LocalBandUser::GetLocalBandUser() const { return (LocalBandUser *)this; }

RemoteBandUser *LocalBandUser::GetRemoteBandUser() {
    MILO_FAIL("Bad Conversion");
    return 0;
}

RemoteBandUser *LocalBandUser::GetRemoteBandUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

const std::vector<u64> &LocalBandUser::GetFriendsConsoleCodes() const {
    return TheBandUI.mOvershell->unk4c0;
}

void LocalBandUser::Reset() {
    BandUser::Reset();
    LocalUser::Reset();
    mShownIntrosSet.clear();
    mHasSeenRealGuitarPrompt = 0;
    unkc = 1;
}

ControllerType LocalBandUser::ConnectedControllerType() const {
    if (!IsJoypadConnected()) {
        return kControllerNone;
    } else {
        ControllerType tyOverride =
            TheBandUserMgr->DebugGetControllerTypeOverride(GetPadNum());
        if (tyOverride != kControllerNone)
            return tyOverride;
        else {
            Symbol joypadType = JoypadControllerTypePadNum(GetPadNum());
            DataArray *cfg = SystemConfig(joypad, instrument_mapping);
            int ct = cfg->FindArray(joypadType)->Int(1);
            MILO_ASSERT_RANGE_EQ(ct, 0, kNumControllerTypes, 0x337);
            static DataNode &fake_controllers = DataVariable("fake_controllers");
            if (fake_controllers.Int() != 0 && ct == 5)
                ct = 2;
            return (ControllerType)ct;
        }
    }
}

bool LocalBandUser::HasSeenRealGuitarPrompt() const { return mHasSeenRealGuitarPrompt; }
void LocalBandUser::SetHasSeenRealGuitarPrompt() { mHasSeenRealGuitarPrompt = true; }

void LocalBandUser::SetOvershellFocus(const char *cc) {
    mOvershellFocus = cc;
    UpdateData(1);
}

int LocalBandUser::GetCurrentInstrumentCareerScore() const {
    if (!TheContentMgr->RefreshDone())
        return 0;
    else {
        ControllerType ct = ConnectedControllerType();
        BandProfile *profile = TheProfileMgr.GetProfileForUser(this);
        if (!profile)
            return 0;
        else {
            SongStatusMgr *mgr = profile->GetSongStatusMgr();
            if (!mgr)
                return 0;
            switch (ct) {
            case kControllerGuitar:
                return mgr->GetCachedTotalDiscScore(kScoreGuitar);
            case kControllerDrum:
                return mgr->GetCachedTotalDiscScore(kScoreDrum);
            case kControllerVocals:
                return mgr->GetCachedTotalDiscScore(kScoreVocals);
            default:
                return 0;
            }
        }
    }
}

int LocalBandUser::GetCurrentHardcoreIconLevel() const {
    BandProfile *profile = TheProfileMgr.GetProfileForUser(this);
    if (!profile)
        return 0;
    else
        return profile->GetHardcoreIconLevel();
}

int LocalBandUser::GetCymbalConfiguration() const {
    return TheProfileMgr.GetCymbalConfiguration();
}

void LocalBandUser::SetShownIntroHelp(TrackType t, bool shown) {
    if (shown)
        mShownIntrosSet.insert(t);
    else
        mShownIntrosSet.erase(t);
}

bool LocalBandUser::HasShownIntroHelp(TrackType t) const {
    return mShownIntrosSet.find(t) != mShownIntrosSet.end();
}

ControllerType LocalBandUser::DebugGetControllerTypeOverride() const {
    return mControllerTypeOverride;
}

void LocalBandUser::DebugSetControllerTypeOverride(ControllerType ct) {
    MILO_ASSERT_RANGE_EQ(ct, 0, kNumControllerTypes, 0x3B2);
    mControllerTypeOverride = ct;
}

BEGIN_HANDLERS(LocalBandUser)
    HANDLE_EXPR(can_save_data, CanSaveData())
    HANDLE_EXPR(can_get_achievements, CanGetAchievements())
    HANDLE_EXPR(connected_controller_type, ConnectedControllerType())
    HANDLE_EXPR(connected_controller_sym, ControllerTypeToSym(ConnectedControllerType()))
    HANDLE_ACTION(set_contributes_song_progress, unkc = _msg->Int(2))
    HANDLE_EXPR(has_as_friend, (_msg->Obj<BandUser>(2), 1))
    HANDLE_SUPERCLASS(LocalUser)
    HANDLE_SUPERCLASS(BandUser)
    HANDLE_CHECK(0x3CC)
END_HANDLERS

RemoteBandUser::RemoteBandUser()
    : unk19(), unk1a(), mCurrentInstrumentCareerScore(), mCurrentHardcoreIconLevel(),
      mCymbalConfiguration() {
    TheWiiFriendMgr.AddSink(this, WiiFriendsListChangedMsg::Type());
    mRemoteChar = new TourCharRemote();
}

RemoteBandUser::~RemoteBandUser() {
    TheWiiFriendMgr.RemoveSink(this, WiiFriendsListChangedMsg::Type());
    delete mRemoteChar;
}

LocalBandUser *RemoteBandUser::GetLocalBandUser() {
    MILO_FAIL("Bad Conversion");
    return 0;
}

LocalBandUser *RemoteBandUser::GetLocalBandUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

RemoteBandUser *RemoteBandUser::GetRemoteBandUser() { return this; }
RemoteBandUser *RemoteBandUser::GetRemoteBandUser() const {
    return (RemoteBandUser *)this;
}

int RemoteBandUser::GetCurrentInstrumentCareerScore() const {
    return mCurrentInstrumentCareerScore;
}
int RemoteBandUser::GetCurrentHardcoreIconLevel() const {
    return mCurrentHardcoreIconLevel;
}
int RemoteBandUser::GetCymbalConfiguration() const { return mCymbalConfiguration; }
const std::vector<unsigned long long> &RemoteBandUser::GetFriendsConsoleCodes() const {
    return mFriendsConsoleCodes;
}

void RemoteBandUser::Reset() {
    BandUser::Reset();
    mUserGuid.Generate();
}

void RemoteBandUser::SyncLoad(BinStream &bs, unsigned int mask) {
    MILO_ASSERT(!TheNetSession->HasUser(this) || !IsLocal(), 0x420);
    RemoteUser::SyncLoad(bs, mask);
    if (mask & 2) {
        bool b860;
        bs >> b860;
        if (b860) {
            bool b79f;
            bs >> b79f;
            if (b79f) {
                Symbol s;
                bs >> s;
                PrefabChar *pc = PrefabMgr::GetPrefabMgr()->GetPrefab(s);
                mChar = pc;
            } else {
                mRemoteChar->SyncLoad(bs);
                mChar = mRemoteChar;
            }
            if (TheCharSync)
                TheCharSync->UpdateCharCache();
        }
    }
    if (mask & 1) {
        Difficulty curDiff = mDifficulty;
        unsigned char diff;
        bs >> diff;
        mDifficulty = (Difficulty)diff;
        unk_0xC = 1;
        if (mDifficulty != curDiff && mPlayer) {
            mPlayer->ChangeDifficulty(mDifficulty);
        }
        unsigned char trackTy;
        bs >> trackTy;
        mTrackType = (TrackType)trackTy;
        unsigned char cntTy;
        bs >> cntTy;
        mControllerType = (ControllerType)cntTy;
        bs >> mHasButtonGuitar;
        bs >> mHas22FretGuitar;
        bs >> mCurrentInstrumentCareerScore;
        unsigned char oState;
        bs >> oState;
        mOvershellState = (OvershellSlotStateID)oState;
        bs >> mOvershellFocus;
        unsigned char scoreTy;
        bs >> scoreTy;
        mPreferredScoreType = (ScoreType)scoreTy;
        unsigned char level;
        bs >> level;
        mCurrentHardcoreIconLevel = level;
        unsigned char cymbalCfg;
        bs >> cymbalCfg;
        mCymbalConfiguration = cymbalCfg;
    }
    if (mask & 0x80) {
        bs >> unk1a;
        unsigned int count;
        bs >> count;
        mFriendsConsoleCodes.clear();
        MILO_LOG("Remote console codes:\n");
        for (int i = 0; i < count; i++) {
            unsigned long long code;
            bs >> code;
            mFriendsConsoleCodes.push_back(code);
            MILO_LOG("\t%llu\n", code);
        }
    }
}

DataNode RemoteBandUser::OnMsg(const WiiFriendsListChangedMsg &msg) {
    // TODO: replace this with the proper WiiFriendsListChangedMsg getter
    if (!msg->Int(2))
        ShowCustomCharacter();
    return 1;
}

void RemoteBandUser::ShowCustomCharacter() {
    if (unk18 && mChar != mRemoteChar && mOnlineID->mValid) {
        int id = mOnlineID->GetPrincipalID();
        WiiFriendList wfl;
        TheWiiFriendMgr.GetCachedFriends(&wfl);
        WiiFriendProfile *wfp = wfl.GetProfile(id);
        if (wfp != NULL)
            mChar = mRemoteChar;
    }
}

BEGIN_HANDLERS(RemoteBandUser)
    HANDLE_MESSAGE(WiiFriendsListChangedMsg)
    HANDLE_SUPERCLASS(BandUser)
    HANDLE_CHECK(0x4AB)
END_HANDLERS
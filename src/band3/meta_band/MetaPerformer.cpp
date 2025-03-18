#include "meta_band/MetaPerformer.h"
#include "bandobj/BandDirector.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameConfig.h"
#include "game/Performer.h"
#include "math/Rand.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/Campaign.h"
#include "meta_band/Instarank.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/Utl.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "meta_band/SessionMgr.h"
#include "net/Net.h"
#include "net/Server.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentral.h"
#include "net_band/RockCentralMsgs.h"
#include "network/net/NetSession.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/ModifierMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "rndobj/Rnd.h"
#include "synth/MicManagerInterface.h"
#include "synth/Synth.h"
#include "tour/Tour.h"
#include "ui/UILabel.h"
#include "utl/DataPointMgr.h"
#include "utl/Loader.h"
#include "utl/PoolAlloc.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MetaPerformer *MetaPerformer::sMetaPerformer;
MicClientID sNullMicClientID;

PerformerStatsInfo::PerformerStatsInfo()
    : mInstrumentMask(0), mScoreType(kScoreBand), unkc(-1), unk10(-1),
      mDifficulty(kDifficultyEasy), mScore(0), mStars(0), mAccuracy(0), mStreak(0),
      mAwesomes(0), mDoubleAwesomes(0), mTripleAwesomes(0), mSoloPercent(0),
      mHOPOPercent(0), mUnisonPhrasesHit(0) {}

PerformerStatsInfo::~PerformerStatsInfo() {}

void PerformerStatsInfo::Clear() {
    mInstrumentMask = 0;
    unkc = -1;
    unk10 = -1;
    mScoreType = kScoreBand;
    mDifficulty = kDifficultyEasy;
    mScore = 0;
    mStars = 0;
    mAccuracy = 0;
    mStreak = 0;
    mAwesomes = 0;
    mDoubleAwesomes = 0;
    mTripleAwesomes = 0;
    mSoloPercent = 0;
    mHOPOPercent = 0;
    mUnisonPhrasesHit = 0;
}

void PerformerStatsInfo::Update(
    int i1, int i2, ScoreType ty, Difficulty diff, short s, Performer *performer
) {
    MILO_ASSERT(!performer->GetQuarantined(), 0x62);
    Stats &stats = performer->mStats;
    unkc = i1;
    unk10 = i2;
    mInstrumentMask = s;
    mScoreType = ty;
    mDifficulty = diff;
    if (ty == kScoreBand)
        mScore = performer->GetScore();
    else
        mScore = performer->GetIndividualScore();
    mStars = performer->GetNumStars();
    mAccuracy = performer->GetNotesHitFraction(0) * 100.0f;
    mStreak = stats.GetLongestStreak();
    mAwesomes = stats.mHitCount;
    mDoubleAwesomes = stats.mDoubleHarmonyHit;
    mTripleAwesomes = stats.mTripleHarmonyHit;
    mSoloPercent = stats.mSoloPercentage;
    mHOPOPercent = ((float)stats.mHopoGemsHopoed / (float)stats.mHopoGemCount) * 100.0f;
    mUnisonPhrasesHit = stats.mUnisonPhraseCompleted;
}

BandStatsInfo::BandStatsInfo() {}

BandStatsInfo::~BandStatsInfo() { Clear(); }

void BandStatsInfo::Clear() {
    mSoloStats.clear();
    mBandStats.Clear();
}

void BandStatsInfo::UpdateBandStats(Difficulty d, short s, Performer *p) {
    mBandStats.Update(-1, -1, kScoreBand, d, s, p);
}

FORCE_LOCAL_INLINE
const PerformerStatsInfo &BandStatsInfo::GetBandStats() const { return mBandStats; }
END_FORCE_LOCAL_INLINE

BandProfile *BandStatsInfo::GetSoloProfile(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xB6);
    BandProfile *profile = mSoloStats[index].first;
    MILO_ASSERT(profile, 0xBB);
    return profile;
}

const PerformerStatsInfo &BandStatsInfo::GetSoloStats(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xC3);
    return mSoloStats[index].second;
}

QuickplayPerformerImpl::QuickplayPerformerImpl() {}
bool QuickplayPerformerImpl::IsRandomSetList() const { return false; }
bool QuickplayPerformerImpl::HasSyncPermission() const { return IsLeaderLocal(); }

void MetaPerformer::Init() {
    MILO_ASSERT(!sMetaPerformer, 0xE9);
    sMetaPerformer = new MetaPerformer(TheSongMgr, "meta_performer");
}

MetaPerformer::MetaPerformer(const BandSongMgr &mgr, const char *cc)
    : Synchronizable(cc), unk38(0), unk40(0), mVenue(gNullStr), unk48(), unk4c(gNullStr),
      unk5c(0), unk5d(0), mSongMgr((BandSongMgr *)&mgr), unk2bc(0), unk2bd(0), unk2c0(0),
      unk2c4(0), unk2c5(0), unk334(0), unk338(0), unk33c(-1), mRecordBattleContextID(-1),
      unk35c(0), unk35d(0), unk360(2), mVenueOverride(gNullStr) {
    SetName(cc, ObjectDir::sMainDir);
    mQpPerformer = new QuickplayPerformerImpl();
    if (TheGameMode)
        TheGameMode->AddSink(this, mode_changed);
    if (TheSessionMgr)
        TheSessionMgr->AddSink(this, new_remote_user);
    if (mVenueOverride == gNullStr)
        mVenueOverride = no_venue_override;
    TheNetSession->AddSink(this);
    TheProfileMgr.AddSink(this, Symbol("primary_profile_changed_msg"));
    unk64 = false;
}

MetaPerformer::~MetaPerformer() {
    TheNetSession->RemoveSink(this);
    if (TheGameMode)
        TheGameMode->RemoveSink(this, mode_changed);
    if (TheSessionMgr)
        TheSessionMgr->RemoveSink(this, new_remote_user);
    TheProfileMgr.RemoveSink(this, Symbol("primary_profile_changed_msg"));
    delete mQpPerformer;
}

MetaPerformer *MetaPerformer::Current() { return sMetaPerformer; }

MetaPerformerImpl *MetaPerformer::CurrentImpl() const {
    bool b2 = false;
    bool b1 = false;
    if (TheTour && TheGameMode->InMode(tour) && TheTour->m_pTourPerformer) {
        return mQpPerformer;
    }
    // supposedly also can return this? but if that's the case then we gotta fix the
    // return type
}

Symbol MetaPerformer::GetVenue() const { return mVenue; }

Symbol MetaPerformer::GetVenueClass() const {
    String venue(mVenue.Str());
    unsigned int idx = venue.find_last_of('_');
    if (idx == String::npos)
        return mVenue;
    else
        return venue.substr(0, idx).c_str();
}

Symbol MetaPerformer::GetLastVenueClass() const {
    String venue(unk48.Str());
    unsigned int idx = venue.find_last_of('_');
    if (idx == String::npos)
        return unk48;
    else
        return venue.substr(0, idx).c_str();
}

bool MetaPerformer::SongEndsWithEndgameSequence() const {
    return IsWinning() && IsLastSong();
}

FORCE_LOCAL_INLINE
int MetaPerformer::NumSongs() const { return mSongs.size(); }
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
int MetaPerformer::NumCompleted() const { return unk78.size(); }
END_FORCE_LOCAL_INLINE

Symbol MetaPerformer::Song() const {
    int num_complete = NumCompleted();
    MILO_ASSERT(num_complete <= NumSongs(), 0x189);
    if (mSongs.empty())
        return gNullStr;
    else if (num_complete == NumSongs())
        return gNullStr;
    else {
        MILO_ASSERT(!mSongs[num_complete].Null(), 0x192);
        return mSongs[num_complete];
    }
}

int MetaPerformer::SongsID() const {
    return TheSongMgr.GetSongIDFromShortName(Song(), true);
}

bool MetaPerformer::HasSong() const { return Song() != gNullStr; }

bool MetaPerformer::IsWinning() const {
    bool b1 = false;
    if (unk2c5 && IsLastSong())
        b1 = true;
    if (b1)
        return true;
    else {
        MetaPerformerImpl *pImpl = CurrentImpl();
        MILO_ASSERT(pImpl, 0x1AA);
        return pImpl->IsWinning();
    }
}

const char *MetaPerformer::GetSetlistName() const { return unk50.c_str(); }
bool MetaPerformer::HasSetlist() const { return unk4c != gNullStr; }

void MetaPerformer::SetSetlist(Symbol s) {
    MILO_ASSERT(HasSyncPermission(), 0x1C1);
    ResetSongs();
    unk4c = s;
    unk50 = Localize(unk4c, nullptr);
    unk5c = false;
    std::vector<Symbol> songs;
    TheSongSortMgr->InqSongsForSetlist(unk4c, songs);
    MILO_ASSERT(!songs.empty(), 0x1CC);
    for (int i = 0; i < songs.size(); i++) {
        MILO_ASSERT(!songs[i].Null(), 0x1D1);
        mSongs.push_back(songs[i]);
    }
    SetSyncDirty(-1, true);
}

void MetaPerformer::SetSetlist(const SavedSetlist *setlist) {
    SetSetlistImpl(setlist, true);
    if (setlist->GetType() - 3U <= 1) {
        unk5d = true;
    }
}

void MetaPerformer::SetSetlistImpl(const SavedSetlist *setlist, bool reset) {
    MILO_ASSERT(HasSyncPermission(), 0x1E5);
    if (reset)
        ResetSongs();
    unk4c = setlist->GetIdentifyingToken();
    unk50 = setlist->GetTitle();
    unk5c = setlist->GetType() == 0;
    FOREACH (it, setlist->mSongs) {
        Symbol shortName = TheSongMgr.GetShortNameFromSongID(*it, true);
        MILO_ASSERT(!shortName.Null(), 0x1FB);
        mSongs.push_back(shortName);
    }
    SetSyncDirty(-1, true);
}

ScoreType MetaPerformer::GetBattleInstrument() const {
    if (unk64)
        return unk6c;
    else
        return kScoreBand;
}

int MetaPerformer::GetBattleID() const {
    if (unk64)
        return unk60;
    else
        return 0;
}

bool MetaPerformer::HasValidBattleInstarank() const {
    if (GetBattleID() >= 0) {
        return false;
    } else {
        return unk84.mIsValid;
    }
}

FORCE_LOCAL_INLINE
bool MetaPerformer::HasBattle() const { return GetBattleID() > 0; }
END_FORCE_LOCAL_INLINE

const char *MetaPerformer::GetBattleName() {
    MILO_ASSERT(HasBattle(), 0x22C);
    return unk50.c_str();
}

int MetaPerformer::GetBattleInstrumentMask() {
    MILO_ASSERT(HasBattle(), 0x233);
    return 1 << unk6c;
}

int MetaPerformer::GetBattleScore() {
    MILO_ASSERT(HasBattle(), 0x23D);
    return unk68;
}

void MetaPerformer::UpdateBattleTypeLabel(UILabel *label) {
    MILO_ASSERT(label, 0x244);
    MILO_ASSERT(HasBattle(), 0x245);
    ScoreType inst = GetBattleInstrument();
    label->SetTokenFmt(
        battle_instrument_fmt, GetFontCharFromScoreType(inst, 0), ScoreTypeToSym(inst)
    );
}

void MetaPerformer::SetBattle(const BattleSavedSetlist *setlist) {
    ResetSongs();
    unk60 = setlist->mID;
    unk6c = setlist->unk6c;
    unk68 = 0;
    unk64 = true;
    SetSetlistImpl(setlist, false);
}

void MetaPerformer::SetSongs(const std::vector<Symbol> &songs) {
    MILO_ASSERT(HasSyncPermission(), 0x265);
    ResetSongs();
    for (int i = 0; i < songs.size(); i++) {
        MILO_ASSERT(!songs[i].Null(), 0x269);
        mSongs.push_back(songs[i]);
    }
    SetSyncDirty(-1, true);
}

void MetaPerformer::SetSongs(const std::vector<int> &vec) {
    std::vector<Symbol> songs;
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        songs.push_back(TheSongMgr.GetShortNameFromSongID(*it, true));
    }
    SetSongs(songs);
}

void MetaPerformer::SetSong(Symbol s) {
    std::vector<Symbol> songs;
    songs.push_back(s);
    SetSongs(songs);
}

void MetaPerformer::SetSongs(DataArray *arr) {
    std::vector<Symbol> songs;
    for (int i = 0; i < arr->Size(); i++) {
        songs.push_back(arr->Sym(i));
    }
    SetSongs(songs);
}

Symbol MetaPerformer::GetCompletedSong() const {
    if (unk78.empty()) {
        if (TheGameMode->Property("loop_setlist", true)->Int()) {
            MILO_ASSERT(!mSongs.empty(), 0x290);
            return mSongs.back();
        } else {
            MILO_FAIL("GetCompletedSong called without a song having been played!");
            return gNullStr;
        }
    } else {
        int idx = unk78.size() - 1;
        MILO_ASSERT(idx < mSongs.size(), 0x29C);
        return mSongs[idx];
    }
}

const std::vector<Symbol> &MetaPerformer::GetSongs() const { return mSongs; }

bool MetaPerformer::IsFirstSong() const { return unk78.empty(); }

bool MetaPerformer::IsLastSong() const {
    int num_complete = NumCompleted();
    MILO_ASSERT(num_complete < NumSongs(), 0x2B0);
    return mSongs.size() - 1 == num_complete;
}

bool MetaPerformer::IsSetComplete() const {
    MILO_ASSERT(NumCompleted() <= NumSongs(), 0x2B6);
    return NumCompleted() == NumSongs();
}

bool MetaPerformer::PartPlaysInSet(Symbol s) const {
    for (std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end();
         ++it) {
        if (*it == gNullStr || *it == any || *it == random)
            return true;
        BandSongMetadata *data =
            (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true)
            );
        if (data && data->HasPart(s, false))
            return true;
    }
    return false;
}

bool MetaPerformer::PartPlaysInSong(Symbol s) const {
    BandSongMetadata *data =
        (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(Song(), true)
        );
    return data && data->HasPart(s, false);
}

bool MetaPerformer::VocalHarmonyInSong() const {
    BandSongMetadata *data =
        (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(Song(), true)
        );
    return data && data->HasVocalHarmony();
}

int MetaPerformer::GetSetlistMaxVocalParts() const {
    int parts = 1;
    for (std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end();
         ++it) {
        if (*it != gNullStr && *it != any && *it != random) {
            BandSongMetadata *data = (BandSongMetadata *)mSongMgr->Data(
                mSongMgr->GetSongIDFromShortName(*it, true)
            );
            if (data) {
                int dataparts = data->NumVocalParts();
                if (dataparts > parts)
                    parts = dataparts;
            }
        }
    }
    return parts;
}

bool MetaPerformer::SetlistHasVocalHarmony() const {
    for (std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end();
         ++it) {
        if (*it != gNullStr && *it != any && *it != random) {
            BandSongMetadata *data = (BandSongMetadata *)mSongMgr->Data(
                mSongMgr->GetSongIDFromShortName(*it, true)
            );
            if (data && data->HasVocalHarmony())
                return true;
        }
    }
    return false;
}

bool MetaPerformer::SetHasMissingPart(Symbol s) const {
    for (std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end();
         ++it) {
        BandSongMetadata *data =
            (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true)
            );
        if (data && !data->HasPart(s, false))
            return true;
    }
    return false;
}

bool MetaPerformer::SetHasMissingVocalHarmony() const {
    for (std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end();
         ++it) {
        BandSongMetadata *data =
            (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true)
            );
        if (data && !data->HasVocalHarmony())
            return true;
    }
    return false;
}

bool MetaPerformer::SongAllowsVocalHarmony() const {
    int id;
    if (IsSetComplete()) {
        id = mSongMgr->GetSongIDFromShortName(GetCompletedSong(), true);
    } else
        id = mSongMgr->GetSongIDFromShortName(Song(), true);
    BandSongMetadata *data = (BandSongMetadata *)mSongMgr->Data(id);
    if (data && !data->HasVocalHarmony())
        return false;
    else
        return true;
}

bool MetaPerformer::IsNowUsingVocalHarmony() const {
    if (!SongAllowsVocalHarmony())
        return false;
    else if (unk35c)
        return true;
    else {
        std::vector<BandUser *> users;
        TheBandUserMgr->GetParticipatingBandUsers(users);
        FOREACH (it, users) {
            BandUser *cur = *it;
            if (cur->GetTrackType() == kTrackVocals) {
                return cur->GetPreferredScoreType() == kScoreHarmony;
            }
        }
        return false;
    }
}

bool MetaPerformer::IsUsingRealDrums() const {
    if (unk35d)
        return true;
    else {
        std::vector<BandUser *> users;
        TheBandUserMgr->GetParticipatingBandUsers(users);
        FOREACH (it, users) {
            BandUser *cur = *it;
            if (cur->GetTrackType() == kTrackDrum) {
                return cur->GetPreferredScoreType() == kScoreRealDrum;
            }
        }
        return false;
    }
}

ScoreType MetaPerformer::GetScoreTypeForUser(BandUser *user) {
    MILO_ASSERT(user, 0x366);
    TrackType ty = user->GetTrackType();
    return TrackTypeToScoreType(ty, IsNowUsingVocalHarmony(), IsUsingRealDrums());
}

bool MetaPerformer::IsPlayingDemo() const {
    Symbol thesong = Song();
    if (thesong.Null())
        return false;
    else
        return TheSongMgr.IsDemo(TheSongMgr.GetSongIDFromShortName(thesong, true));
}

bool MetaPerformer::IsNoFailActive() const {
    bool set = IsBandNoFailSet();
    bool ret = false;
    if (set) {
        if (TheGameMode->Property(nofail_allowed, true)->Int())
            ret = true;
    }
    return ret;
}

bool MetaPerformer::IsBandNoFailSet() const {
    if (TheModifierMgr)
        return TheModifierMgr->IsModifierActive(mod_no_fail_band);
    else
        return false;
}

void MetaPerformer::LockBandOrSolo() {
    unk360 = TheBandUserMgr->GetNumParticipants() > 1;
}

void MetaPerformer::UnlockBandOrSolo() { unk360 = 2; }

bool MetaPerformer::CanUpdateScoreLeaderboards() {
    if (TheGameMode) {
        if (!TheGameMode->Property("update_leaderboards", true)->Int())
            return false;
    }
    if (TheGame->ResumedNoScore())
        return false;
    else
        return true;
}

int MetaPerformer::GetHighestDifficultyForPart(Symbol s) const {
    int diff = 0;
    FOREACH (it, mSongs) {
        if (*it == gNullStr || *it == any || *it == random)
            return -1;
        BandSongMetadata *data =
            (BandSongMetadata *)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true)
            );
        if (data && data->HasPart(s, false)) {
            if (diff < mSongMgr->GetPartDifficulty(*it, s)) {
                diff = mSongMgr->GetPartDifficulty(*it, s);
            }
        }
    }
    return diff;
}

void MetaPerformer::PopulatePlayerBandScores(
    const BandStatsInfo &info, std::vector<PlayerScore> &scores
) {
    int numStats = info.mSoloStats.size();
    for (int i = 0; i < numStats; i++) {
        BandProfile *profile = info.GetSoloProfile(i);
        MILO_ASSERT(profile, 0x3DF);
        int padnum = profile->GetPadNum();
        Server *netServer = TheNet.GetServer();
        MILO_ASSERT(netServer, 0x3E3);
        if (netServer->GetPlayerID(padnum) != 0) {
            PlayerScore score;
            PopulateSoloPlayerScore(info.GetBandStats(), profile, score);
            scores.push_back(score);
        }
    }
}

void MetaPerformer::PopulateSoloPlayerScore(
    const PerformerStatsInfo &info, BandProfile *profile, PlayerScore &score
) {
    MILO_ASSERT(profile, 0x3F3);
    SongStatusMgr *songStatusMgr = profile->GetSongStatusMgr();
    MILO_ASSERT(songStatusMgr, 0x3F6);
    Server *netServer = TheNet.GetServer();
    MILO_ASSERT(netServer, 0x3F9);
    int i4 = info.unkc;
    if (info.mScoreType == kScoreBand) {
        i4 = profile->GetPadNum();
    }
    score.mPlayerID = netServer->GetPlayerID(i4);
    score.unk18 = info.unk10;
    score.mScoreType = info.mScoreType;
    score.mDiff = info.mDifficulty;
    score.mTotalScore = songStatusMgr->GetCachedTotalScore(score.mScoreType);
    score.mTotalDiscScore = songStatusMgr->GetCachedTotalDiscScore(info.mScoreType);
    score.mAccuracy = info.mAccuracy;
    score.mScore = info.mScore;
    score.mStars = info.mStars;
}

void MetaPerformer::PopulatePlayerScores(
    const BandStatsInfo &info, std::vector<PlayerScore> &scores
) {
    PopulatePlayerBandScores(info, scores);
    int numStats = info.mSoloStats.size();
    for (int i = 0; i < numStats; i++) {
        const PerformerStatsInfo &curPerfInfo = info.GetSoloStats(i);
        BandProfile *profile = info.GetSoloProfile(i);
        MILO_ASSERT(profile, 0x415);
        int padnum = profile->GetPadNum();
        Server *netServer = TheNet.GetServer();
        MILO_ASSERT(netServer, 0x419);
        if (netServer->GetPlayerID(padnum) != 0) {
            PlayerScore score;
            PopulateSoloPlayerScore(curPerfInfo, profile, score);
            scores.push_back(score);
        }
    }
}

void MetaPerformer::UpdateScores(Symbol s, const BandStatsInfo &info, bool b3) {
    int songID = mSongMgr->GetSongIDFromShortName(s, true);
    int numStats = info.mSoloStats.size();
    for (int i = 0; i < numStats; i++) {
        BandProfile *profile = info.GetSoloProfile(i);
        MILO_ASSERT(profile, 0x432);
        int padnum = profile->GetPadNum();
        Server *netServer = TheNet.GetServer();
        MILO_ASSERT(netServer, 0x437);
        bool b8 = netServer->GetPlayerID(padnum) != 0 && !b3;
        profile->UpdateScore(songID, info.GetSoloStats(i), b8);
        profile->UpdateScore(songID, info.GetBandStats(), b8);
    }
}

void MetaPerformer::UpdateLastOfflineScores(Symbol s, const BandStatsInfo &info) {
    unk294 = mSongMgr->GetSongIDFromShortName(s, true);
    BandProfile *p = TheProfileMgr.GetPrimaryProfile();
    if (p) {
        unk298 = p->GetSongHighScore(unk294, kScoreBand);
    }
    int numStats = info.mSoloStats.size();
    for (int i = 0; i < numStats; i++) {
        const PerformerStatsInfo &stats = info.GetSoloStats(i);
        BandProfile *profile = info.GetSoloProfile(i);
        MILO_ASSERT(profile, 0x459);
        int idx = stats.unk10;
        unk29c[idx] = profile->GetSongHighScore(unk294, stats.mScoreType);
        unk2ac[idx] = stats.mScoreType;
    }
}

void MetaPerformer::SaveAndUploadScores(
    std::vector<LocalBandUser *> &users, Symbol s, const BandStatsInfo &info
) {
    if (users.empty())
        return;
    if (!TheGame->IsInvalidScore()) {
        bool instaRankProp = TheGameMode->Property(insta_rank, true)->Int();
        UpdateLastOfflineScores(s, info);
        UpdateScores(s, info, !instaRankProp);
        if (instaRankProp) {
            int songID = mSongMgr->GetSongIDFromShortName(s, true);
            unk2c8.friendMode = true;
            std::vector<PlayerScore> scores;
            PopulatePlayerScores(info, scores);
            int pID = 0;
            BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
            if (profile) {
                int padnum = profile->GetPadNum();
                Server *netServer = TheNet.GetServer();
                MILO_ASSERT(netServer, 0x490);
                pID = netServer->GetPlayerID(padnum);
            }
            if (unk33c != -1) {
                MILO_WARN(
                    "We are sending out a record score (song = %s) while waiting for another to come back still...",
                    s.mStr
                );
            }
            if (TheNet.GetServer() && TheNet.GetServer()->IsConnected()
                && scores.size()) {
                unk2bc = true;
                int old = unk338++;
                unk33c = old;
                TheRockCentral.RecordScore(
                    songID,
                    unk33c,
                    scores,
                    pID,
                    info.GetBandStats().mInstrumentMask,
                    true,
                    this,
                    unk2c8.ir_result
                );
                TheRockCentral.RecordOptionData();
            } else
                unk2bc = false;
        }
        if (unk64) {
            RecordBattleScore(info, IsLastSong());
        }
    }
}

ScoreType
MetaPerformer::GetInstarankScoreTypeForSlot(int slot, const BandStatsInfo &info) {
    Server *netServer = TheNet.GetServer();
    MILO_ASSERT(netServer, 0x4BE);
    std::vector<LocalBandUser *> users;
    TheBandUserMgr->GetLocalParticipants(users);
    FOREACH (it, users) {
        LocalBandUser *user = *it;
        MILO_ASSERT(user, 0x4C6);
        int userSlot = user->GetSlot();
        if (userSlot == slot) {
            int numStats = info.mSoloStats.size();
            for (int i = 0; i < numStats; i++) {
                const PerformerStatsInfo &curPerfInfo = info.GetSoloStats(i);
                if (curPerfInfo.unk10 == userSlot) {
                    return curPerfInfo.mScoreType;
                }
            }
            break;
        }
    }
    return kScoreBand;
}

Instarank &MetaPerformer::GetInstarankForPlayerID(int slotNum) {
    MILO_ASSERT_RANGE( slotNum, 0, GameConfig::kMaxPlayers, 0x4DE);
    return unk134[slotNum];
}

void MetaPerformer::UpdateInstarankData(
    DataResultList &results, const BandStatsInfo &info
) {
    for (int i = 0; i < results.NumDataResults(); i++) {
        DataResult *res = results.GetDataResult(i);

        DataNode ne8;
        res->GetDataResultValue("id", ne8);
        int i3 = ne8.Int();

        DataNode nf0;
        res->GetDataResultValue("slot", nf0);
        int i10 = nf0.Int();

        DataNode nf8;
        res->GetDataResultValue("is_boi", nf8);
        bool i4 = nf8.Int();

        DataNode n100;
        res->GetDataResultValue("insta_rank", n100);
        int i5 = n100.Int();

        DataNode n108;
        res->GetDataResultValue("is_percentile", n108);
        bool i6 = n108.Int();

        DataNode n110;
        res->GetDataResultValue("part_1", n110);
        String str50 = n110.Str();

        DataNode n118;
        res->GetDataResultValue("part_2", n118);
        String str5c = n118.Str();

        if (i4) {
            unkdc.Init(i3, i4, kScoreBand, i5, i6, str50, str5c);
        } else {
            Instarank &rank = GetInstarankForPlayerID(i10);
            ScoreType s = GetInstarankScoreTypeForSlot(i10, info);
            rank.Init(i3, i4, s, i5, i6, str50, str5c);
        }
    }
}

void MetaPerformer::UpdateBattleInstarankData(DataResultList &results) {
    if (results.NumDataResults() < 1) {
        MILO_WARN("No data returned from RecordBattle call!\n");
    } else {
        DataResult *res = results.GetDataResult(0);

        DataNode n8c0;
        res->GetDataResultValue("id", n8c0);
        int i5 = n8c0.Int();

        DataNode n8c8;
        res->GetDataResultValue("is_boi", n8c8);
        bool i2 = n8c8.Int();

        DataNode n8d0;
        res->GetDataResultValue("insta_rank", n8d0);
        int i6 = n8d0.Int();

        DataNode n8d8;
        res->GetDataResultValue("is_percentile", n8d8);
        bool i7 = n8d8.Int();

        DataNode n8e0;
        res->GetDataResultValue("part_1", n8e0);
        String str84c = n8e0.Str();

        DataNode n8e8;
        res->GetDataResultValue("part_2", n8e8);
        String str858 = n8e8.Str();

        unk84.Init(i5, i2, GetBattleInstrument(), i6, i7, str84c, str858);
    }
}

void MetaPerformer::ClearInstarankData() {
    unkdc.Clear();
    for (int i = 0; i < 4; i++) {
        unk134[i].Clear();
    }
    for (int i = 0; i < 4; i++) {
        unk29c[i] = 0;
        unk2ac[i] = kScoreBand;
    }
}

void MetaPerformer::ClearBattleInstarankData() { unk84.Clear(); }
Symbol MetaPerformer::GetVenueOverride() { return mVenueOverride; }

#pragma push
#pragma pool_data off
DataNode MetaPerformer::OnMsg(const RockCentralOpCompleteMsg &msg) {
    MILO_ASSERT(TheGameMode->Property(insta_rank), 0x566);
    int arg2 = msg.Arg2().Int();
    if (arg2 == unk33c) {
        unk33c = -1;
        if (msg.Arg0()) {
            ClearInstarankData();
            unk2c8.ir_result.Update(nullptr);
            UpdateInstarankData(unk2c8.ir_result, unk2c8.stats);
            static InstarankDoneMsg instarankDoneMsg;
            Export(instarankDoneMsg, true);
        } else {
            UpdateScores(unk2c8.song, unk2c8.stats, true);
        }
        unk2c8.Clear();
    } else if (arg2 == mRecordBattleContextID) {
        mRecordBattleContextID = -1;
        if (msg.Arg0()) {
            ClearBattleInstarankData();
            unk344.Update(nullptr);
            UpdateBattleInstarankData(unk344);
            static InstarankDoneMsg instarankDoneMsg;
            Export(instarankDoneMsg, true);
        }
    }
    return 1;
}
#pragma pop

DataNode MetaPerformer::OnMsg(const ModeChangedMsg &) {
    int numPlayers = TheGameMode->Property(local_vocalist_player_count, true)->Int();
    if (TheSynth->GetMicClientMapper()) {
        TheSynth->GetMicClientMapper()->SetNumberOfPlayers(numPlayers);
    }
    return 1;
}

void MetaPerformer::SetBandNoFail(bool b1) {
    if (b1 != IsBandNoFailSet()) {
        TheModifierMgr->ToggleModifierEnabled(mod_no_fail_band);
        SetSyncDirty(-1, false);
        ExportUpdateMetaPerformer();
    }
}

void MetaPerformer::SelectRandomVenue() {
    DataArray *cfg = SystemConfig(video_venues);
    cfg->FindFloat(probability);
    cfg->FindFloat(artist_specific_probability);
    bool autoVox = TheModifierMgr->IsModifierActive(mod_auto_vocals);
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (!autoVox && profile && profile->HasCampaignKey(key_video_venues)) {
        Symbol s50;
        cfg = SystemConfig(video_venues, venues);
        Symbol s54;
        for (int i = 1; i < cfg->Size(); i++) {
            DataArray *curArr = cfg->Array(i);
            s54 = curArr->Sym(0);
            DataArray *artistArr = curArr->FindArray(artists, false);
            bool b2 = false;
            if (artistArr && mSongs.size()) {
                b2 = true;
                FOREACH (it, mSongs) {
                    Symbol cur = *it;
                    bool b1 = false;
                    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(
                        TheSongMgr.GetSongIDFromShortName(cur, false)
                    );
                    for (int j = 1; j < artistArr->Size(); j++) {
                        if (data && streq(artistArr->Str(j), data->Artist())) {
                            b1 = true;
                            break;
                        }
                    }
                    if (!b1) {
                        b2 = false;
                        break;
                    }
                }
            }
            if (b2) {
                s50 = s54;
                break;
            }
        }
        if (!s50.Null()) {
            DataArray *videoVenueCfg = SystemConfig(video_venues);
            DataArray *probArr =
                videoVenueCfg->FindArray(artist_specific_probability, true);
            if (RandomFloat() < probArr->Float(1) || autoVox) {
                SetVenue(s50);
                return;
            }
        } else {
            DataArray *videoVenueCfg = SystemConfig(video_venues);
            DataArray *probArr = videoVenueCfg->FindArray(probability, true);
            if (RandomFloat() < probArr->Float(1) || autoVox) {
                std::vector<Symbol> validVenues;
                DataArray *venuesVideoCfg = SystemConfig(venues_video);
                for (int i = 1; i < venuesVideoCfg->Size(); i++) {
                    Symbol curSym = venuesVideoCfg->Sym(i);
                    DataArray *curSymArr = cfg->FindArray(curSym, true);
                    if (!curSymArr->FindArray(artists, false)) {
                        validVenues.push_back(curSym);
                    }
                }
                MILO_ASSERT(!validVenues.empty(), 0x620);
                SetVenue(validVenues[RandomInt(0, validVenues.size())]);
                return;
            }
        }
    }
    Symbol venueSym = subway_venues;
    if (profile) {
        LocalBandUser *user = profile->GetAssociatedLocalBandUser();
        MILO_ASSERT(user, 0x633);
        if (TheCampaign->HasReachedCampaignLevel(user, campaignlevel_jet)) {
            venueSym = jet_venues;
        } else if (TheCampaign->HasReachedCampaignLevel(user, campaignlevel_bus)) {
            venueSym = bus_venues;
        } else if (TheCampaign->HasReachedCampaignLevel(user, campaignlevel_van)) {
            venueSym = van_venues;
        }
    }
    DataArray *venueCfg = SystemConfig(venueSym);
    SetVenue(venueCfg->Sym(RandomInt(1, venueCfg->Size())));
}

void MetaPerformer::SetVenue(Symbol s) {
    bool changed = false;
    if (mVenue != s)
        changed = true;
    unk48 = mVenue = s;
    if (TheNetSession && !TheNetSession->IsLocal()) {
        char videobuf[16] = "video_01";
        videobuf[7] = RandomInt(0, 7) + '1';
        unk48 = mVenue = videobuf;
        MILO_LOG(
            "\n#\n#Wii Net Play Venue Override: %s used in place of %s\n#\n\n",
            mVenue.mStr,
            s.mStr
        );
    }
    if (mVenueOverride != no_venue_override) {
        mVenue = mVenueOverride;
        unk48 = mVenueOverride;
    }
    if (changed && TheSessionMgr && HasSyncPermission()) {
        SetSyncDirty(-1, false);
    }
    unk2c4 = GetVenueClass() == festival
        && TheAccomplishmentMgr->HasNewRewardVignetteFestival();
}

void MetaPerformer::LoadFestival() {
    MILO_LOG("LOADING VENUE: %s\n", mVenue.mStr);
    TheBandDirector->LoadVenue(mVenue, kLoadBack);
}

void MetaPerformer::ClearVenues() {
    bool hasVenue = false;
    if (mVenue != gNullStr)
        hasVenue = true;
    mVenue = gNullStr;
    unk2c4 = false;
    if (hasVenue && TheSessionMgr && HasSyncPermission()) {
        SetSyncDirty(-1, false);
    }
    TheBandDirector->UnloadVenue(true);
}

void MetaPerformer::ResetSongs() {
    ResetCompletion();
    mSongs.clear();
    unk4c = gNullStr;
    unk5d = false;
    unk50 = gNullStr;
    unk5c = false;
    unk68 = 0;
    unk64 = false;
    unk2bd = false;
}

void MetaPerformer::ResetCompletion() { unk78.clear(); }

void MetaPerformer::HostRestartLastSong() {
    MILO_ASSERT(IsLeaderLocal(), 0x6C2);
    MILO_ASSERT(HasSyncPermission(), 0x6C3);
    unk78.pop_back();
    CurrentImpl()->RestartLastSong();
    SetSyncDirty(-1, true);
}

void MetaPerformer::Restart() {
    MILO_ASSERT(HasSyncPermission(), 0x6D0);
    MILO_ASSERT(NumSongs() == NumCompleted(), 0x6D1);
    ResetCompletion();
    SetSyncDirty(-1, true);
}

void MetaPerformer::TriggerSongCompletion() {
    bool m16 = unk334;
    SetCheating(false);
    Difficulty d15 = kDifficultyExpert;
    short i14 = 0;
    BandStatsInfo info;
    Band *band = TheGame->GetBand();
    Performer *perf = band->MainPerformer();
    std::vector<BandUser *> users;
    int numPlayers = band->NumActivePlayers();
    int songID = TheSongMgr.GetSongIDFromShortName(Song(), true);
    Symbol gameMode = TheGameMode->GetMode();
    for (int i = 0; i < numPlayers; i++) {
        Player *player = band->GetActivePlayer(i);
        MILO_ASSERT(player, 0x6F0);
        BandUser *user = player->GetUser();
        users.push_back(user);
        ScoreType s = GetScoreTypeForUser(user);
        i14 |= 1 << s;
        if (d15 > user->GetDifficulty()) {
            d15 = user->GetDifficulty();
        }
        if (user->IsLocal()) {
            LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
            MILO_ASSERT(localUser, 0x700);
            BandProfile *profile = TheProfileMgr.GetProfileForUser(localUser);
            if (profile) {
                Difficulty d8 = localUser->GetDifficulty();
                if (!player->GetQuarantined() && localUser->unkc) {
                    int i7 = localUser->GetPadNum();
                    info.AddSoloStats(i7, localUser->GetSlot(), s, d8, profile, player);
                    if (player->IsAutoplay()) {
                        m16 = true;
                    }
                    profile->UpdatePerformanceData(
                        player->mStats,
                        songID,
                        s,
                        d8,
                        gameMode,
                        player->GetNumStars(),
                        GetBattleID(),
                        m16
                    );
                }
            }
        }
    }
    unk2c0 = i14;
    info.UpdateBandStats(d15, i14, perf);
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        profile->UpdatePerformanceData(
            perf->mStats,
            songID,
            kScoreBand,
            d15,
            gameMode,
            perf->GetNumStars(),
            GetBattleID(),
            m16
        );
    }
    CompleteSong(users, &info, false);
}

void MetaPerformer::CompleteSong(
    std::vector<BandUser *> &users, const BandStatsInfo *stats, bool b3
) {
    MILO_ASSERT(stats, 0x72A);
    MILO_ASSERT(NumCompleted() < NumSongs(), 0x72B);
    SendDataPoint(
        "debug/rc/context/highwatermark",
        "high",
        TheRockCentral.GetActiveContextHighWatermark()
    );
    CurrentImpl()->CompleteSong(users, stats, b3);
    Symbol songSym = Song();
    TheAccomplishmentMgr->HandlePreSongCompleted(songSym);
    PotentiallyUpdateLeaderboards(users, b3, songSym, *stats);
    IncrementSongPlayCount(users, songSym);
    TheAccomplishmentMgr->HandleSongCompleted(songSym, stats->GetBandStats().mDifficulty);
    if (IsLastSong() && !unk4c.Null() && !unk2bd) {
        int totalStars = stats->GetBandStats().mStars + TotalStars(true);
        TheAccomplishmentMgr->HandleSetlistCompleted(
            unk4c, unk5d, stats->GetBandStats().mDifficulty, totalStars
        );
    }
}

void MetaPerformer::IncrementSongPlayCount(std::vector<BandUser *> &users, Symbol s) {
    int songID = TheSongMgr.GetSongIDFromShortName(s, true);
    FOREACH (it, users) {
        BandUser *user = *it;
        MILO_ASSERT(user, 0x758);
        if (user->IsLocal()) {
            LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
            MILO_ASSERT(localUser, 0x75D);
            BandProfile *profile = TheProfileMgr.GetProfileForUser(localUser);
            if (profile) {
                SongStatusMgr *songStatusMgr = profile->GetSongStatusMgr();
                MILO_ASSERT(songStatusMgr, 0x763);
                songStatusMgr->SetSongPlayCount(
                    songID, songStatusMgr->GetSongPlayCount(songID) + 1
                );
                profile->MakeDirty();
            }
        }
    }
}

void MetaPerformer::RecordBattleScore(const BandStatsInfo &stats, bool battleFinished) {
    std::vector<BandProfile *> profiles;
    if (unk6c == kScoreBand) {
        unk68 += stats.GetBandStats().mScore;
        if (battleFinished) {
            profiles = TheProfileMgr.GetParticipatingProfiles();
        }
    } else {
        int numStats = stats.mSoloStats.size();
        for (int i = 0; i < numStats; i++) {
            const PerformerStatsInfo &curPerfInfo = stats.GetSoloStats(i);
            if (curPerfInfo.mScoreType == unk6c) {
                unk68 += curPerfInfo.mScore;
                if (battleFinished) {
                    BandProfile *profile = stats.GetSoloProfile(i);
                    MILO_ASSERT(profile, 0x78D);
                    profiles.push_back(profile);
                }
            }
        }
    }
    Server *netServer = TheNet.GetServer();
    MILO_ASSERT(netServer, 0x795);

    std::vector<BandProfile *> profiles40;
    FOREACH (it, profiles) {
        BandProfile *cur = *it;
        if (netServer->GetPlayerID(cur->GetPadNum())) {
            profiles40.push_back(cur);
        }
    }
    if (!profiles40.empty()) {
        MILO_ASSERT(battleFinished, 0x7A6);
        MILO_ASSERT(mRecordBattleContextID == -1, 0x7A9);
        mRecordBattleContextID = unk338;
        unk338++;
        unk344.Clear();
        TheRockCentral.RecordBattleScore(
            unk60, mRecordBattleContextID, profiles40, unk68, unk344, this
        );
    }
}

bool MetaPerformer::IsRandomSetList() const { return CurrentImpl()->IsRandomSetList(); }

void MetaPerformer::SkipSong() {
    unk2bd = true;
    AdvanceSong(0);
}

void MetaPerformer::AdvanceSong(int x) {
    MILO_ASSERT(NumCompleted() < NumSongs(), 0x7C3);
    unk78.push_back(x);
    if (HasSyncPermission()) {
        SetSyncDirty(-1, false);
    }
}

void MetaPerformer::OnSynchronized(unsigned int ui) {
    ExportUpdateMetaPerformer();
    CurrentImpl()->OnSynchronized(ui);
}

void MetaPerformer::ExportUpdateMetaPerformer() {
    DataArrayPtr ptr(update_meta_performer);
    ptr->Execute();
}

void MetaPerformer::SyncSave(BinStream &bs, unsigned int ui) const {
    bs << mVenue;
    bs << unk2c4;
    bs << unk4c;
    bs << (unk5c ? String(gNullStr) : unk50);
    bs << unk5d;
    bs << mSongs;
    bs << unk78;
    bs << IsBandNoFailSet();
    bs << unk2bd;
    bs << unk64;
    if (unk64) {
        bs << unk60;
        bs << unk6c;
    }
    CurrentImpl()->SyncSave(bs, ui);
}

void MetaPerformer::SyncLoad(BinStream &bs, unsigned int ui) {
    Symbol old = mVenue;
    bs >> mVenue;
    bs >> unk2c4;
    if (old != mVenue) {
        if (mVenue == gNullStr) {
            TheBandDirector->UnloadVenue(true);
        } else if (!unk2c4) {
            TheBandDirector->LoadVenue(mVenue, kLoadStayBack);
        }
    }
    bs >> unk4c;
    bs >> unk50;
    bs >> unk5d;
    bs >> mSongs;
    bs >> unk78;
    bool nofailset = IsBandNoFailSet();
    bool noFail;
    bs >> noFail;
    SetBandNoFail(noFail);
    if (nofailset != noFail && TheGame) {
        TheGame->SetNoFail(noFail);
    }
    bs >> unk2bd;
    bs >> unk64;
    if (unk64) {
        bs >> unk60;
        int score;
        bs >> score;
        unk6c = (ScoreType)score;
    }
    CurrentImpl()->SyncLoad(bs, ui);
}

bool MetaPerformer::HasSyncPermission() const {
    return CurrentImpl()->HasSyncPermission();
}

void MetaPerformer::PotentiallyUpdateLeaderboards(
    std::vector<BandUser *> &users, bool b2, Symbol s3, const BandStatsInfo &info
) {
    ClearInstarankData();
    ClearBattleInstarankData();
    unk2bc = false;
    unk2c8.stats = info;
    unk2c8.song = s3;
    if (TheBandUserMgr && !b2 && CanUpdateScoreLeaderboards()) {
        int numUsers = users.size();
        std::vector<LocalBandUser *> users;
        std::vector<LocalBandUser *> filteredUsers;
        TheBandUserMgr->GetLocalParticipants(users);
        FOREACH (it, users) {
            if ((*it)->CanSaveData()) {
                filteredUsers.push_back(*it);
            }
        }
        if (numUsers == 1 && filteredUsers.empty()) {
            TheBandUserMgr->GetLocalBandUsers(users);
            FOREACH (it, users) {
                if ((*it)->CanSaveData()) {
                    filteredUsers.push_back(*it);
                }
            }
            if (filteredUsers.size() > 1)
                filteredUsers.clear();
        }
        SaveAndUploadScores(filteredUsers, s3, info);
    }
}

int MetaPerformer::TotalStars(bool b1) const {
    int stars = 0;
    FOREACH (it, unk78) {
        if (b1) {
            stars += Min(5, *it);
        } else
            stars += *it;
    }
    return stars;
}

bool MetaPerformer::HasBattleHighscore() { return unk84.HasHighscore(); }

bool MetaPerformer::HasHighscore() {
    if (unk2bc) {
        return unkdc.HasHighscore();
    } else {
        BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
        if (profile) {
            return profile->GetSongHighScore(unk294, kScoreBand) > unk298;
        } else
            return false;
    }
}

int MetaPerformer::GetLastOfflineScore() { return unk298; }

int MetaPerformer::GetLastOfflineSoloScore(BandUser *user) {
    if (user->IsLocal()) {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x878);
        return unk29c[localUser->GetSlot()];
    } else
        return 0;
}

bool MetaPerformer::HasSoloHighscore(BandUser *user) {
    if (!user->IsLocal())
        return false;
    else {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x88A);
        if (localUser->GetPlayer() && !localUser->GetPlayer()->GetQuarantined()) {
            BandProfile *profile = TheProfileMgr.GetProfileForUser(localUser);
            if (profile) {
                int padnum = localUser->GetPadNum();
                int slot = localUser->GetSlot();
                Server *netServer = TheNet.GetServer();
                MILO_ASSERT(netServer, 0x895);
                int pID = netServer->GetPlayerID(padnum);
                if (unk2bc && pID) {
                    Instarank &rank = GetInstarankForPlayerID(slot);
                    if (rank.mIsValid) {
                        return rank.HasHighscore();
                    }
                }
                int highscore = profile->GetSongHighScore(unk294, unk2ac[slot]);
                return highscore > unk29c[slot];
            }
        }
    }
    return false;
}

bool MetaPerformer::HasValidBandScore() { return unk2c8.stats.mSoloStats.size() > 0; }

bool MetaPerformer::HasValidUserScore(BandUser *user) {
    if (user->IsLocal()) {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x8B4);
        BandProfile *profile = TheProfileMgr.GetProfileForUser(localUser);
        if (profile) {
            int numStats = unk2c8.stats.mSoloStats.size();
            for (int i = 0; i < numStats; i++) {
                if (unk2c8.stats.GetSoloProfile(i) == profile)
                    return true;
            }
        }
    }
    return false;
}

bool MetaPerformer::HasValidInstarankData() const { return unkdc.mIsValid; }

void MetaPerformer::UpdateInstarankRankLabel(UILabel *label) {
    MILO_ASSERT(label, 0x8D0);
    if (unkdc.mIsValid) {
        unkdc.UpdateRankLabel(label);
    } else {
        MILO_WARN(
            "can't update instarank label %s - mBandInstarank is uninitialized!\n",
            label->Name()
        );
    }
}

void MetaPerformer::UpdateInstarankHighscore1Label(UILabel *label) {
    MILO_ASSERT(label, 0x8DE);
    if (unkdc.mIsValid) {
        unkdc.UpdateString1Label(label);
    } else {
        MILO_WARN(
            "can't update string1 label %s - mBandInstarank is uninitialized!\n",
            label->Name()
        );
    }
}

void MetaPerformer::UpdateInstarankHighscore2Label(UILabel *label) {
    MILO_ASSERT(label, 0x8EC);
    if (unkdc.mIsValid) {
        unkdc.UpdateString2Label(label);
    } else {
        MILO_WARN(
            "can't update string2 label %s - mBandInstarank is uninitialized!\n",
            label->Name()
        );
    }
}

void MetaPerformer::UpdateBattleInstarankHighscore1Label(UILabel *label) {
    MILO_ASSERT(label, 0x8FA);
    if (unk84.mIsValid) {
        unk84.UpdateString1Label(label);
    } else {
        MILO_WARN(
            "can't update HighScore1 label %s - mBattleInstarank is uninitialized!\n",
            label->Name()
        );
    }
}

void MetaPerformer::UpdateBattleInstarankHighscore2Label(UILabel *label) {
    MILO_ASSERT(label, 0x908);
    if (unk84.mIsValid) {
        unk84.UpdateString2Label(label);
    } else {
        MILO_WARN(
            "can't update HighScore2 label %s - mBattleInstarank is uninitialized!\n",
            label->Name()
        );
    }
}

const char *MetaPerformer::GetSoloScoreTypeIcon(BandUser *user) {
    if (user->IsLocal()) {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x919);
        int padnum = localUser->GetPadNum();
        int slot = localUser->GetSlot();
        Server *netServer = TheNet.GetServer();
        MILO_ASSERT(netServer, 0x91E);
        int pID = netServer->GetPlayerID(padnum);
        ScoreType s;
        if (unk2bc && pID) {
            Instarank &rank = GetInstarankForPlayerID(slot);
            if (rank.mIsValid)
                s = rank.mScoreType;
            else
                s = unk2ac[slot];
        } else
            s = unk2ac[slot];
        return GetFontCharFromScoreType(s, 0);
    } else
        return "j";
}

void MetaPerformer::UpdateSoloInstarankRankLabel(BandUser *user, UILabel *label) {
    MILO_ASSERT(label, 0x93B);
    MILO_ASSERT(user, 0x93C);
    if (!user->IsLocal()) {
        label->SetTextToken(gNullStr);
    } else {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x946);
        if (!localUser->GetPlayer() || localUser->GetPlayer()->GetQuarantined()) {
            label->SetTextToken(gNullStr);
        } else if (!TheProfileMgr.GetProfileForUser(localUser)) {
            label->SetTextToken(gNullStr);
        } else {
            int padnum = localUser->GetPadNum();
            int slot = localUser->GetSlot();
            Server *netServer = TheNet.GetServer();
            MILO_ASSERT(netServer, 0x95B);
            if (!netServer->GetPlayerID(padnum)) {
                label->SetTextToken(gNullStr);
            } else {
                Instarank &rank = GetInstarankForPlayerID(slot);
                if (rank.mIsValid) {
                    rank.UpdateRankLabel(label);
                }
            }
        }
    }
}

void MetaPerformer::UpdateSoloInstarankHighscore1Label(BandUser *user, UILabel *label) {
    MILO_ASSERT(label, 0x96D);
    MILO_ASSERT(user, 0x96E);
    if (!user->IsLocal()) {
        label->SetTextToken(gNullStr);
    } else {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x978);
        if (!localUser->GetPlayer() || localUser->GetPlayer()->GetQuarantined()) {
            label->SetTextToken(gNullStr);
        } else if (!TheProfileMgr.GetProfileForUser(localUser)) {
            label->SetTextToken(gNullStr);
        } else {
            int padnum = localUser->GetPadNum();
            int slot = localUser->GetSlot();
            Server *netServer = TheNet.GetServer();
            MILO_ASSERT(netServer, 0x98D);
            if (!netServer->GetPlayerID(padnum)) {
                label->SetTextToken(gNullStr);
            } else {
                Instarank &rank = GetInstarankForPlayerID(slot);
                if (rank.mIsValid) {
                    rank.UpdateString1Label(label);
                }
            }
        }
    }
}

void MetaPerformer::UpdateSoloInstarankHighscore2Label(BandUser *user, UILabel *label) {
    MILO_ASSERT(label, 0x99F);
    MILO_ASSERT(user, 0x9A0);
    if (!user->IsLocal()) {
        label->SetTextToken(gNullStr);
    } else {
        LocalBandUser *localUser = dynamic_cast<LocalBandUser *>(user);
        MILO_ASSERT(localUser, 0x9AA);
        if (!localUser->GetPlayer() || localUser->GetPlayer()->GetQuarantined()) {
            label->SetTextToken(gNullStr);
        } else if (!TheProfileMgr.GetProfileForUser(localUser)) {
            label->SetTextToken(gNullStr);
        } else {
            int padnum = localUser->GetPadNum();
            int slot = localUser->GetSlot();
            Server *netServer = TheNet.GetServer();
            MILO_ASSERT(netServer, 0x9BF);
            if (!netServer->GetPlayerID(padnum)) {
                label->SetTextToken(gNullStr);
            } else {
                Instarank &rank = GetInstarankForPlayerID(slot);
                if (rank.mIsValid) {
                    rank.UpdateString2Label(label);
                }
            }
        }
    }
}

void MetaPerformer::UploadDebugStats() {
    TheRnd->UploadDebugStats();
    Symbol::UploadDebugStats();
    ChunkAllocator::UploadDebugStats();
}

void MetaPerformer::SetCreditsPending() {
    static OvershellPanel *pOvershellPanel =
        ObjectDir::Main()->Find<OvershellPanel>("overshell", true);
    pOvershellPanel->UpdateAll();
    unk40 = true;
}

void MetaPerformer::ClearCreditsPending() {
    static OvershellPanel *pOvershellPanel =
        ObjectDir::Main()->Find<OvershellPanel>("overshell", true);
    pOvershellPanel->UpdateAll();
    unk40 = false;
}

bool MetaPerformer::AreCreditsPending() const { return unk40; }
void MetaPerformer::SetWiiPending(WiiPendingFlags flags) { unk38 |= flags; }
void MetaPerformer::ClearWiiPending(WiiPendingFlags flags) { unk38 &= ~flags; }
bool MetaPerformer::IsWiiPending(WiiPendingFlags flags) const { return unk38 & flags; }
void MetaPerformer::SetCheating(bool b) { unk334 = b; }
short MetaPerformer::GetRecentInstrumentMask() const { return 0x400; }
bool MetaPerformer::CheatToggleFinale() { return unk2c5 = !unk2c5; }

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(MetaPerformer)
    HANDLE_EXPR(current, Current())
    HANDLE_ACTION(set_venue, SetVenue(_msg->ForceSym(2)))
    HANDLE_ACTION(load_festival, LoadFestival())
    HANDLE_EXPR(festival_reward, unk2c4)
    HANDLE_ACTION(select_random_venue, SelectRandomVenue())
    HANDLE_EXPR(get_venue, GetVenue())
    HANDLE_EXPR(get_venue_class, GetVenueClass())
    HANDLE_EXPR(get_last_venue_class, GetLastVenueClass())
    HANDLE_ACTION(clear_venues, ClearVenues())
    HANDLE_EXPR(has_setlist, HasSetlist())
    HANDLE_ACTION(set_song, SetSong(_msg->Sym(2)))
    HANDLE_ACTION(set_songs, SetSongs(_msg->Array(2)))
    HANDLE_ACTION(reset_songs, ResetSongs())
    HANDLE_ACTION(restart, Restart())
    HANDLE_ACTION(host_restart_last_song, HostRestartLastSong())
    HANDLE_EXPR(num_songs, NumSongs())
    HANDLE_EXPR(num_completed, NumCompleted())
    HANDLE_EXPR(song, Song())
    HANDLE_EXPR(song_id, SongsID())
    HANDLE_EXPR(indexed_song, GetSongSymbol(_msg->Int(2)))
    HANDLE_EXPR(win_metric, GetWinMetric())
    HANDLE_EXPR(get_completed_song, GetCompletedSong())
    HANDLE_EXPR(is_first_song, IsFirstSong())
    HANDLE_EXPR(is_last_song, IsLastSong())
    HANDLE_EXPR(is_set_complete, IsSetComplete())
    HANDLE_EXPR(part_plays_in_set, PartPlaysInSet(_msg->Sym(2)))
    HANDLE_EXPR(part_plays_in_song, PartPlaysInSong(_msg->Sym(2)))
    HANDLE_EXPR(is_winning, IsWinning())
    HANDLE_EXPR(has_sync_permission, HasSyncPermission())
    HANDLE_EXPR(cheat_toggle_finale, CheatToggleFinale())
    HANDLE_ACTION(trigger_song_completion, TriggerSongCompletion())
    HANDLE_ACTION(advance_song, AdvanceSong(_msg->Int(2)))
    HANDLE_ACTION(skip_song, SkipSong())
    HANDLE_EXPR(is_no_fail_active, IsNoFailActive())
    HANDLE_EXPR(is_band_no_fail_set, IsBandNoFailSet())
    HANDLE_ACTION(set_band_no_fail, SetBandNoFail(_msg->Int(2)))
    HANDLE_ACTION(set_harmony_override, unk35c = _msg->Int(2))
    HANDLE_ACTION(set_realdrums_override, unk35d = _msg->Int(2))
    HANDLE_EXPR(get_venue_override, GetVenueOverride())
    HANDLE_ACTION(set_venue_override, mVenueOverride = _msg->Sym(2))
    HANDLE_EXPR(is_now_using_vocal_harmony, IsNowUsingVocalHarmony())
    HANDLE_EXPR(is_playing_demo, IsPlayingDemo())
    HANDLE_EXPR(are_credits_pending, AreCreditsPending())
    HANDLE_ACTION(set_credits_pending, SetCreditsPending())
    HANDLE_ACTION(clear_credits_pending, ClearCreditsPending())
    HANDLE_EXPR(is_wiiprofile_create_pending, IsWiiPending((WiiPendingFlags)1))
    HANDLE_ACTION(set_wiiprofile_create_pending, SetWiiPending((WiiPendingFlags)1))
    HANDLE_ACTION(clear_wiiprofile_create_pending, ClearWiiPending((WiiPendingFlags)1))
    HANDLE_EXPR(is_using_persistent_data, GetPersistentGameData() != 0)
    HANDLE_EXPR(total_stars, TotalStars(_msg->Int(2)))
    HANDLE_EXPR(get_total_stars_capped, TotalStars(true))
    HANDLE_EXPR(get_recent_instrument_mask, GetRecentInstrumentMask())
    HANDLE_ACTION(upload_debug_stats, UploadDebugStats())
    HANDLE_EXPR(has_online_scoring, unk2bc)
    HANDLE_EXPR(has_valid_band_score, HasValidBandScore())
    HANDLE_EXPR(has_valid_user_score, HasValidUserScore(_msg->Obj<BandUser>(2)))
    HANDLE_EXPR(has_online_scoring, unk2bc)
    HANDLE_EXPR(has_valid_instarank_data, HasValidInstarankData())
    HANDLE_ACTION(
        update_instarank_rank_label, UpdateInstarankRankLabel(_msg->Obj<UILabel>(2))
    )
    HANDLE_ACTION(
        update_instarank_highscore_1_label,
        UpdateInstarankHighscore1Label(_msg->Obj<UILabel>(2))
    )
    HANDLE_ACTION(
        update_instarank_highscore_2_label,
        UpdateInstarankHighscore2Label(_msg->Obj<UILabel>(2))
    )
    HANDLE_EXPR(has_highscore, HasHighscore())
    HANDLE_EXPR(get_last_offline_score, GetLastOfflineScore())
    HANDLE_EXPR(get_solo_score_type_icon, GetSoloScoreTypeIcon(_msg->Obj<BandUser>(2)))
    HANDLE_ACTION(
        update_instarank_solo_rank_label,
        UpdateSoloInstarankRankLabel(_msg->Obj<BandUser>(2), _msg->Obj<UILabel>(3))
    )
    HANDLE_ACTION(
        update_instarank_solo_highscore_1_label,
        UpdateSoloInstarankHighscore1Label(_msg->Obj<BandUser>(2), _msg->Obj<UILabel>(3))
    )
    HANDLE_ACTION(
        update_instarank_solo_highscore_2_label,
        UpdateSoloInstarankHighscore2Label(_msg->Obj<BandUser>(2), _msg->Obj<UILabel>(3))
    )
    HANDLE_EXPR(has_solo_highscore, HasSoloHighscore(_msg->Obj<BandUser>(2)))
    HANDLE_EXPR(
        get_last_offline_solo_score, GetLastOfflineSoloScore(_msg->Obj<BandUser>(2))
    )
    HANDLE_ACTION(
        update_battle_instarank_highscore_1_label,
        UpdateBattleInstarankHighscore1Label(_msg->Obj<UILabel>(2))
    )
    HANDLE_ACTION(
        update_battle_instarank_highscore_2_label,
        UpdateBattleInstarankHighscore2Label(_msg->Obj<UILabel>(2))
    )
    HANDLE_EXPR(has_battle_highscore, HasBattleHighscore())
    HANDLE_EXPR(has_valid_battle_instarank_data, HasValidBattleInstarank())
    HANDLE_EXPR(has_battle, HasBattle())
    HANDLE_EXPR(get_battle_name, GetBattleName())
    HANDLE_EXPR(get_battle_instrument_mask, GetBattleInstrumentMask())
    HANDLE_EXPR(get_battle_score, GetBattleScore())
    HANDLE_ACTION(update_battle_type_label, UpdateBattleTypeLabel(_msg->Obj<UILabel>(2)))
    HANDLE_ACTION(set_cheating, SetCheating(_msg->Int(2)))
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MESSAGE(ModeChangedMsg)
    HANDLE_MEMBER_PTR(CurrentImpl())
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xADB)
END_HANDLERS
#pragma pop
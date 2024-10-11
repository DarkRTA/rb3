#include "meta_band/MetaPerformer.h"
#include "game/Performer.h"
#include "meta_band/Utl.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "meta_band/SessionMgr.h"
#include "network/net/NetSession.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/ModifierMgr.h"
#include "utl/Symbols.h"

MetaPerformer* MetaPerformer::sMetaPerformer;

PerformerStatsInfo::PerformerStatsInfo() : mInstrumentMask(0), mScoreType(kScoreBand), unkc(-1), unk10(-1), mDifficulty(kDifficultyEasy), mScore(0), mStars(0), mAccuracy(0), mStreak(0), mAwesomes(0), mDoubleAwesomes(0),
    mTripleAwesomes(0), mSoloPercent(0), unk38(0), mUnisonPhrasesHit(0) {

}

PerformerStatsInfo::~PerformerStatsInfo(){

}

void PerformerStatsInfo::Clear(){
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
    unk38 = 0;
    mUnisonPhrasesHit = 0;
}

void PerformerStatsInfo::Update(int i1, int i2, ScoreType ty, Difficulty diff, short s, Performer* performer){
    MILO_ASSERT(!performer->GetQuarantined(), 0x62);
    Stats& stats = performer->mStats;
    unkc = i1;
    unk10 = i2;
    mInstrumentMask = s;
    mScoreType = ty;
    mDifficulty = diff;
    if(ty == kScoreBand) mScore = performer->GetScore();
    else mScore = performer->GetIndividualScore();
    mStars = performer->GetNumStars();
    mAccuracy = performer->GetNotesHitFraction(0) * 100.0f;
    mStreak = stats.GetLongestStreak();
    mAwesomes = stats.mHitCount;
    mDoubleAwesomes = stats.mDoubleHarmonyHit;
    mTripleAwesomes = stats.mTripleHarmonyHit;
    mSoloPercent = stats.mSoloPercentage;
    unk38 = ((float)stats.mHopoGemInfo1 / (float)stats.mHopoGemInfo3) * 100.0f;
    mUnisonPhrasesHit = stats.mUnisonPhraseCompleted;
}

BandStatsInfo::BandStatsInfo(){}

BandStatsInfo::~BandStatsInfo(){ Clear(); }

void BandStatsInfo::Clear(){
    mSoloStats.clear();
    mBandStats.Clear();
}

void BandStatsInfo::UpdateBandStats(Difficulty d, short s, Performer* p){
    mBandStats.Update(-1, -1, kScoreBand, d, s, p);
}

const PerformerStatsInfo& BandStatsInfo::GetBandStats() const { return mBandStats; }

BandProfile* BandStatsInfo::GetSoloProfile(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xB6);
    BandProfile* profile = mSoloStats[index].first;
    MILO_ASSERT(profile, 0xBB);
    return profile;
}

const PerformerStatsInfo& BandStatsInfo::GetSoloStats(int index) const {
    MILO_ASSERT(index < mSoloStats.size(), 0xC3);
    return mSoloStats[index].second;
}

QuickplayPerformerImpl::QuickplayPerformerImpl(){}
bool QuickplayPerformerImpl::IsRandomSetList() const { return false; }
bool QuickplayPerformerImpl::HasSyncPermission() const { return IsLeaderLocal(); }

void MetaPerformer::Init(){
    MILO_ASSERT(!sMetaPerformer, 0xE9);
    sMetaPerformer = new MetaPerformer(*TheSongMgr, "meta_performer");
}

MetaPerformer::MetaPerformer(const BandSongMgr& mgr, const char* cc) : Synchronizable(cc), unk38(0), unk40(0), mVenue(gNullStr), unk48(), unk4c(gNullStr), unk5c(0), unk5d(0),
    mSongMgr((BandSongMgr*)&mgr), unk2bc(0), unk2bd(0), unk2c0(0), unk2c4(0), unk2c5(0), unk334(0), unk338(0), unk33c(-1), unk340(-1), unk35c(0), unk35d(0), unk360(2), mVenueOverride(gNullStr) {
    SetName(cc, ObjectDir::sMainDir);
    mQpPerformer = new QuickplayPerformerImpl();
    if(TheGameMode) TheGameMode->AddSink(this, mode_changed);
    if(TheSessionMgr) TheSessionMgr->AddSink(this, new_remote_user);
    if(mVenueOverride == gNullStr) mVenueOverride = no_venue_override;
    TheNetSession->AddSink(this);
    TheProfileMgr.AddSink(this, Symbol("primary_profile_changed_msg"));
    unk64 = false;
}

MetaPerformer::~MetaPerformer(){
    TheNetSession->RemoveSink(this);
    if(TheGameMode) TheGameMode->RemoveSink(this, mode_changed);
    if(TheSessionMgr) TheSessionMgr->RemoveSink(this, new_remote_user);
    TheProfileMgr.RemoveSink(this, Symbol("primary_profile_changed_msg"));
    delete mQpPerformer;
}

MetaPerformer* MetaPerformer::Current(){ return sMetaPerformer; }

Symbol MetaPerformer::GetVenue() const { return mVenue; }

Symbol MetaPerformer::GetVenueClass() const {
    String venue(mVenue.Str());
    unsigned int idx = venue.find_last_of('_');
    if(idx == String::npos) return mVenue;
    else return venue.substr(0, idx).c_str();
}

Symbol MetaPerformer::GetLastVenueClass() const {
    String venue(unk48.Str());
    unsigned int idx = venue.find_last_of('_');
    if(idx == String::npos) return unk48;
    else return venue.substr(0, idx).c_str();
}

bool MetaPerformer::SongEndsWithEndgameSequence() const {
    return IsWinning() && IsLastSong();
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(MetaPerformer, MetaPerformer, NumSongs())
DECOMP_FORCEFUNC(MetaPerformer, MetaPerformer, NumCompleted())
#pragma pop

Symbol MetaPerformer::Song() const {
    int num_complete = NumCompleted();
    MILO_ASSERT(num_complete <= NumSongs(), 0x189);
    if(mSongs.empty()) return gNullStr;
    else if(num_complete == NumSongs()) return gNullStr;
    else {
        MILO_ASSERT(!mSongs[num_complete].Null(), 0x192);
        return mSongs[num_complete];
    }
}

int MetaPerformer::SongsID() const {
    return TheSongMgr->GetSongIDFromShortName(Song(), true);
}

bool MetaPerformer::HasSong() const { return Song() != gNullStr; }

bool MetaPerformer::IsWinning() const {
    bool b1 = false;
    if(unk2c5 && IsLastSong()) b1 = true;
    if(b1) return true;
    else {
        QuickplayPerformerImpl* pImpl = CurrentImpl();
        MILO_ASSERT(pImpl, 0x1AA);
        return pImpl->IsWinning();
    }
}

const char* MetaPerformer::GetSetlistName() const { return unk50.c_str(); }

bool MetaPerformer::HasSetlist() const {
    return unk4c != gNullStr;
}

void MetaPerformer::SetSongs(const std::vector<Symbol>& songs){
    MILO_ASSERT(HasSyncPermission(), 0x265);
    ResetSongs();
    for(int i = 0; i < songs.size(); i++){
        MILO_ASSERT(!songs[i].Null(), 0x269);
        mSongs.push_back(songs[i]);
    }
    SetSyncDirty(-1, true);
}

void MetaPerformer::SetSongs(const std::vector<int>& vec){
    std::vector<Symbol> songs;
    for(std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it){
        songs.push_back(TheSongMgr->GetShortNameFromSongID(*it, true));
    }
    SetSongs(songs);
}

void MetaPerformer::SetSongs(DataArray* arr){
    std::vector<Symbol> songs;
    for(int i = 0; i < arr->Size(); i++){
        songs.push_back(arr->Sym(i));
    }
    SetSongs(songs);
}

Symbol MetaPerformer::GetCompletedSong() const {
    if(unk78.empty()){
        if(TheGameMode->Property("loop_setlist", true)->Int(0)){
            MILO_ASSERT(!mSongs.empty(), 0x290);
            return mSongs.back();
        }
        else {
            MILO_FAIL("GetCompletedSong called without a song having been played!");
            return gNullStr;
        }
    }
    else {
        int idx = unk78.size() - 1;
        MILO_ASSERT(idx < mSongs.size(), 0x29C);
        return mSongs[idx];
    }
}

const std::vector<Symbol>& MetaPerformer::GetSongs() const { return mSongs; }

bool MetaPerformer::IsFirstSong() const {
    return unk78.empty();
}

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
    for(std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
        if(*it == gNullStr || *it == any || *it == random) return true;
        BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true));
        if(data && data->HasPart(s, false)) return true;
    }
    return false;
}

bool MetaPerformer::PartPlaysInSong(Symbol s) const {
    BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(Song(), true));
    return data && data->HasPart(s, false);
}

bool MetaPerformer::VocalHarmonyInSong() const {
    BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(Song(), true));
    return data && data->HasVocalHarmony();
}

int MetaPerformer::GetSetlistMaxVocalParts() const {
    int parts = 1;
    for(std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
        if(*it != gNullStr && *it != any && *it != random){
            BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true));
            if(data){
                int dataparts = data->NumVocalParts();
                if(dataparts > parts) parts = dataparts;
            }
        }
    }
    return parts;
}

bool MetaPerformer::SetlistHasVocalHarmony() const {
    for(std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
        if(*it != gNullStr && *it != any && *it != random){
            BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true));
            if(data && data->HasVocalHarmony()) return true;
        }
    }
    return false;
}

bool MetaPerformer::SetHasMissingPart(Symbol s) const {
    for(std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
        BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true));
        if(data && !data->HasPart(s, false)) return true;
    }
    return false;
}

bool MetaPerformer::SetHasMissingVocalHarmony() const {
    for(std::vector<Symbol>::const_iterator it = mSongs.begin(); it != mSongs.end(); ++it){
        BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(mSongMgr->GetSongIDFromShortName(*it, true));
        if(data && !data->HasVocalHarmony()) return true;
    }
    return false;
}

bool MetaPerformer::SongAllowsVocalHarmony() const {
    int id;
    if(IsSetComplete()){
        id = mSongMgr->GetSongIDFromShortName(GetCompletedSong(), true);
    }
    else id = mSongMgr->GetSongIDFromShortName(Song(), true);
    BandSongMetadata* data = (BandSongMetadata*)mSongMgr->Data(id);
    if(data && !data->HasVocalHarmony()) return false;
    else return true;
}

ScoreType MetaPerformer::GetScoreTypeForUser(BandUser* user){
    MILO_ASSERT(user, 0x366);
    TrackType ty = user->GetTrackType();
    return TrackTypeToScoreType(ty, IsNowUsingVocalHarmony(), IsUsingRealDrums());
}

bool MetaPerformer::IsPlayingDemo() const {
    Symbol thesong = Song();
    if(thesong.Null()) return false;
    else return TheSongMgr->IsDemo(TheSongMgr->GetSongIDFromShortName(thesong, true));
}

bool MetaPerformer::IsNoFailActive() const {
    bool set = IsBandNoFailSet();
    bool ret = false;
    if(set){
        if(TheGameMode->Property(nofail_allowed, true)->Int(0)) ret = true;
    }
    return ret;
}

bool MetaPerformer::IsBandNoFailSet() const {
    if(TheModifierMgr) return TheModifierMgr->IsModifierActive(mod_no_fail_band);
    else return false;
}

bool MetaPerformer::CanUpdateScoreLeaderboards(){
    if(TheGameMode){
        if(!TheGameMode->Property("update_leaderboards", true)->Int(0)) return false;
    }
    if(TheGame->ResumedNoScore()) return false;
    else return true;
}
#include "SongStatusMgr.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "net/Net.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "obj/ObjMacros.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"

bool SongStatusMgr::sFakeLeaderboardUploadFailure;

void SongStatusData::Clear(ScoreType ty){
    mStars = 0;
    mAccuracy = 0;
    mStreak = 0;
    mFlags = 0;
    if(ty == kScoreVocals || ty == kScoreHarmony){
        mShared.mVocals.mAwesomes = 0;
        mShared.mVocals.mDoubleAwesomes = 0;
        mShared.mVocals.mTripleAwesomes = 0;
    }
    else {
        mShared.mGuitarDrums.mHoposPercentage = 0;
        mShared.mGuitarDrums.mSoloPercentage = 0;
    }
}

int SongStatusData::SaveSize(int){
    REPORT_SIZE("SongStatusData", 8);
}

void SongStatusData::SaveToStream(BinStream& bs, ScoreType ty) const {
    bs << mStars;
    bs << mAccuracy;
    bs << mStreak;
    bs << mFlags;
    if(ty == kScoreVocals || ty == kScoreHarmony){
        bs << mShared.mVocals.mAwesomes;
        bs << mShared.mVocals.mDoubleAwesomes;
        bs << mShared.mVocals.mTripleAwesomes;
    }
    else {
        bs << mShared.mGuitarDrums.mHoposPercentage;
        bs << mShared.mGuitarDrums.mSoloPercentage;
        bs << mShared.mVocals.mTripleAwesomes;
    }
}

void SongStatusData::LoadFromStream(BinStream& bs, ScoreType){
    bs >> mStars;
    bs >> mAccuracy;
    bs >> mStreak;
    bs >> mFlags;
    bs >> mShared.mVocals.mAwesomes;
    bs >> mShared.mVocals.mDoubleAwesomes;
    bs >> mShared.mVocals.mTripleAwesomes;
}

void SongStatus::Clear(){
    mSongID = 0;
    mBandScoreInstrumentMask = 0;
    mReview = 0;
    mLastPlayed = 0;
    mPlayCount = 0;
    for(int i = 0; i < 4; i++){
        mProGuitarLessonParts[i] = 0;
        mProBassLessonParts[i] = 0;
        mProKeyboardLessonParts[i] = 0;
    }
    for(int i = 0; i < 11; i++){
        mHighScores[i] = 0;
        mHighScoreDiffs[i] = kDifficultyEasy;
        for(int j = 0; j < 4; j++){
            mSongData[i][j].Clear((ScoreType)i);
        }
    }
}

int SongStatus::SaveSize(int i){
    int i3 = 0x1F;
    if(i >= 0x90) i3 = 0x2F;
    i3 += 0x47;
    i3 += SongStatusData::SaveSize(i) * 0x2C;
    REPORT_SIZE("SongStatus", i3);
}

void SongStatus::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mSongID;
    stream << mBandScoreInstrumentMask;
    stream << mReview;
    stream << mLastPlayed;
    stream << mPlayCount;
    for(int i = 0; i < 4; i++){
        stream << mProGuitarLessonParts[i];
        stream << mProBassLessonParts[i];
        stream << mProKeyboardLessonParts[i];
    }
    for(int i = 0; i < 11; i++){
        stream << mHighScores[i];
        stream << (unsigned char)mHighScoreDiffs[i];
        for(int j = 0; j < 4; j++){
            mSongData[i][j].SaveToStream(stream, (ScoreType)i);
        }
    }
}

void SongStatus::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> mSongID;
    stream >> mBandScoreInstrumentMask;
    stream >> mReview;
    stream >> mLastPlayed;
    stream >> mPlayCount;
    for(int i = 0; i < 4; i++){
        stream >> mProGuitarLessonParts[i];
        if(rev >= 0x90){
            stream >> mProBassLessonParts[i];
        }
        stream >> mProKeyboardLessonParts[i];
    }
    for(int i = 0; i < 11; i++){
        stream >> mHighScores[i];
        unsigned char uc;
        stream >> uc;
        mHighScoreDiffs[i] = (Difficulty)uc;
        for(int j = 0; j < 4; j++){
            mSongData[i][j].LoadFromStream(stream, (ScoreType)i);
        }
    }
}

void SongStatus::SetDirty(ScoreType ty, Difficulty diff, bool high){
    if(high){
        SetFlag(kSongStatusFlag_Dirty, ty, diff);
    }
    else {
        ClearFlag(kSongStatusFlag_Dirty, ty, diff);
    }
}

void SongStatus::SetLastPlayed(int lp){ mLastPlayed = lp; }
int SongStatus::GetLastPlayed() const { return mLastPlayed; }
void SongStatus::SetPlayCount(int count){ mPlayCount = count; }

void SongStatus::SetBitmapLessonComplete(unsigned int& mask, int bit, bool high){
    if(high){
        mask |= (1 << bit);
    }
    else {
        mask &= ~(1 << bit);
    }
}

void SongStatus::SetProGuitarLessonSectionComplete(Difficulty diff, int bit, bool high){
    SetBitmapLessonComplete(mProGuitarLessonParts[diff], bit, high);
}

void SongStatus::SetProBassLessonSectionComplete(Difficulty diff, int bit, bool high){
    SetBitmapLessonComplete(mProBassLessonParts[diff], bit, high);
}

void SongStatus::SetProKeyboardLessonSectionComplete(Difficulty diff, int bit, bool high){
    SetBitmapLessonComplete(mProKeyboardLessonParts[diff], bit, high);
}

void SongStatus::SetID(int id){ mSongID = id; }
int SongStatus::GetID() const { return mSongID; }
void SongStatus::SetReview(unsigned char r){ mReview = r; }
void SongStatus::SetInstrumentMask(unsigned short mask){ mBandScoreInstrumentMask = mask; }

void SongStatus::SetFlag(SongStatusFlagType flag, ScoreType score, Difficulty diff){
    mSongData[score][diff].mFlags |= flag;
}

void SongStatus::ClearFlag(SongStatusFlagType flag, ScoreType score, Difficulty diff){
    mSongData[score][diff].mFlags &= ~flag;
}

unsigned char SongStatus::GetSoloPercent(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x20D);
    return mSongData[scoreType][diff].mShared.mGuitarDrums.mSoloPercentage;
}

unsigned char SongStatus::GetHOPOPercent(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x214);
    return mSongData[scoreType][diff].mShared.mGuitarDrums.mHoposPercentage;
}

unsigned char SongStatus::GetAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x21B);
    return mSongData[scoreType][diff].mShared.mVocals.mAwesomes;
}

unsigned char SongStatus::GetDoubleAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x222);
    return mSongData[scoreType][diff].mShared.mVocals.mDoubleAwesomes;
}

unsigned char SongStatus::GetTripleAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x229);
    return mSongData[scoreType][diff].mShared.mVocals.mTripleAwesomes;
}

bool SongStatus::UpdateScore(ScoreType ty, Difficulty diff, int score){
    if(score > mHighScores[ty]){
        mHighScores[ty] = score;
        mHighScoreDiffs[ty] = diff;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateStars(ScoreType ty, Difficulty diff, unsigned char stars){
    if(stars > mSongData[ty][diff].mStars){
        mSongData[ty][diff].mStars = stars;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateAccuracy(ScoreType ty, Difficulty diff, unsigned char acc){
    if(acc > mSongData[ty][diff].mAccuracy){
        mSongData[ty][diff].mAccuracy = acc;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateStreak(ScoreType ty, Difficulty diff, unsigned short streak){
    if(streak > mSongData[ty][diff].mStreak){
        mSongData[ty][diff].mStreak = streak;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateSoloPercent(ScoreType scoreType, Difficulty diff, unsigned char solopct){
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x25D);
    if(solopct > mSongData[scoreType][diff].mShared.mGuitarDrums.mSoloPercentage){
        mSongData[scoreType][diff].mShared.mGuitarDrums.mSoloPercentage = solopct;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateHOPOPercent(ScoreType scoreType, Difficulty diff, unsigned char hopopct){
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x26A);
    if(hopopct > mSongData[scoreType][diff].mShared.mGuitarDrums.mHoposPercentage){
        mSongData[scoreType][diff].mShared.mGuitarDrums.mHoposPercentage = hopopct;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x277);
    if(awesomes > mSongData[scoreType][diff].mShared.mVocals.mAwesomes){
        mSongData[scoreType][diff].mShared.mVocals.mAwesomes = awesomes;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateDoubleAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x284);
    if(awesomes > mSongData[scoreType][diff].mShared.mVocals.mDoubleAwesomes){
        mSongData[scoreType][diff].mShared.mVocals.mDoubleAwesomes = awesomes;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateTripleAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x291);
    if(awesomes > mSongData[scoreType][diff].mShared.mVocals.mTripleAwesomes){
        mSongData[scoreType][diff].mShared.mVocals.mTripleAwesomes = awesomes;
        return true;
    }
    else return false;
}

SongStatusLookup::SongStatusLookup(){
    Clear();
}

SongStatusLookup::~SongStatusLookup(){

}

void SongStatusLookup::Clear(){
    mSongID = 0;
    mLastPlayed = 0;
}

void SongStatusLookup::Save(FixedSizeSaveableStream& stream) const {
    stream << mSongID;
    stream << mLastPlayed;
}

void SongStatusLookup::Load(FixedSizeSaveableStream& stream, int){
    stream >> mSongID;
    stream >> mLastPlayed;
}

SongStatusCacheMgr::SongStatusCacheMgr(const LocalBandUser** user) : mUser(user), unk1f54(0) {
    mpSongStatusFull = new SongStatus[1000];
    Clear();
    mSaveSizeMethod = &SaveSize;
}

SongStatus::SongStatus(){
    mSaveSizeMethod = &SaveSize;
    Clear();
}

SongStatus::~SongStatus(){

}

SongStatusCacheMgr::~SongStatusCacheMgr(){
    delete [] mpSongStatusFull;
    mpSongStatusFull = 0;
}

void SongStatusCacheMgr::Clear(){
    MILO_ASSERT(mpSongStatusFull, 0x2F0);
    for(int i = 0; i < 1000; i++){
        mLookups[i].Clear();
        mpSongStatusFull[i].Clear();
    }
    mCurrentIndex = -1;
}

int SongStatusCacheMgr::SaveSize(int){
    REPORT_SIZE("SongStatusCacheMgr", 8000);
}

void SongStatusCacheMgr::SaveFixed(FixedSizeSaveableStream& stream) const {
    for(int i = 0; i < 1000; i++){
        mLookups[i].Save(stream);
    }
}

void SongStatusCacheMgr::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    for(int i = 0; i < 1000; i++){
        mLookups[i].Load(stream, rev);
    }
}

SongStatus** SongStatusCacheMgr::GetFullCachePtr(){ return &mpSongStatusFull; }

int SongStatusCacheMgr::GetSongID(int idx){
    if(idx <= 999U){
        return mLookups[idx].mSongID;
    }
    else return 0;
}

int SongStatusCacheMgr::GetSongStatusIndex(int idx){
    for(int i = 0; i < 1000; i++){
        if(idx == mLookups[i].mSongID) return i;
    }
    return -1;
}

SongStatus* SongStatusCacheMgr::GetSongStatusPtrForIndex(int idx){
    if(idx <= 999U){
        MILO_ASSERT(mpSongStatusFull, 0x334);
        mCurrentIndex = idx;
        return &mpSongStatusFull[idx];
    }
    else {
        mCurrentIndex = -1;
        return nullptr;
    }
}

void SongStatusCacheMgr::SetLastPlayed(int last){
    if(mCurrentIndex <= 999U){
        mLookups[mCurrentIndex].SetLastPlayed(last);
    }
}

bool SongStatusCacheMgr::HasSongStatus(int idx){
    for(int i = 0; i < 1000; i++){
        if(idx == mLookups[i].mSongID) return true;
    }
    return false;
}

SongStatus* SongStatusCacheMgr::AccessSongStatus(int idx){
    MILO_ASSERT(mpSongStatusFull, 0x360);
    int songidx = GetSongStatusIndex(idx);
    if(songidx >= 0){
        mCurrentIndex = songidx;
        return &mpSongStatusFull[songidx];
    }
    else return nullptr;
}

SongStatus* SongStatusCacheMgr::CreateOrAccessSongStatus(int id){
    SongStatus* status = AccessSongStatus(id);
    if(status) return status;
    else {
        int i = GetEmptyIndex();
        MILO_ASSERT(i >= 0, 0x376);
        mLookups[i].SetSongID(id);
        MILO_ASSERT(mpSongStatusFull, 0x379);
        mCurrentIndex = i;
        mpSongStatusFull[i].Clear();
        mpSongStatusFull[i].SetID(id);
        return &mpSongStatusFull[i];
    }
}

int SongStatusCacheMgr::ClearLeastImportantSongStatusEntry(){
    int lowestlast = 0x7FFFFFFF; // isn't this just -1?
    int ret = 0;
    for(int i = 0; i < 1000; i++){
        if(!TheSongMgr->HasSong(mLookups[i].mSongID) || mLookups[i].mSongID == 0){
            ClearIndex(i);
            return i;
        }
        else if(mLookups[i].mLastPlayed < lowestlast){
            ret = i;
            lowestlast = mLookups[i].mLastPlayed;
        }
    }
    ClearIndex(ret);
    return ret;
}

SongStatus* SongStatusCacheMgr::GetSongStatus(int id){
    CreateOrAccessSongStatus(id);
    MILO_ASSERT(mpSongStatusFull, 0x3A5);
    return &mpSongStatusFull[mCurrentIndex];
}

int SongStatusCacheMgr::GetEmptyIndex(){
    for(int i = 0; i < 1000; i++){
        if(mLookups[i].Empty()) return i;
    }
    return ClearLeastImportantSongStatusEntry();
}

void SongStatusCacheMgr::ClearIndex(int idx){
    if(idx >= 0) mLookups[idx].Clear();
}

SongStatusMgr::SongStatusMgr(LocalBandUser* u, BandSongMgr* mgr) : mLocalUser(u), mSongMgr(mgr), mCacheMgr((const LocalBandUser**)&mLocalUser), mUpdatingStatus(0) {
    mSaveSizeMethod = &SaveSize;
}

SongStatusMgr::~SongStatusMgr(){
    Clear();
}

void SongStatusMgr::Clear(){
    if(mUpdatingStatus){
        TheRockCentral.CancelOutstandingCalls(this);
        mUpdatingStatus = 0;
    }
    mCacheMgr.Clear();
    for(int i = 0; i < 11; i++){
        mCachedTotalScores[i] = 0;
        mCachedTotalDiscScores[i] = 0;
        mCachedTotalStars[i] = 0;
    }
}

bool SongStatusMgr::UpdateSongStats(ScoreType ty, Difficulty diff, const PerformerStatsInfo& stats, SongStatus* songStatus){
    MILO_ASSERT(songStatus, 0x409);
    bool updated = songStatus->UpdateStars(ty, diff, stats.mStars);
    if(updated){
        UpdateCachedTotalStars(ty);
    }
    updated |= songStatus->UpdateAccuracy(ty, diff, stats.mAccuracy);
    updated |= songStatus->UpdateStreak(ty, diff, stats.mStreak);
    if(ty == kScoreVocals || ty == kScoreHarmony){
        updated |= songStatus->UpdateAwesomes(ty, diff, stats.mAwesomes);
        updated |= songStatus->UpdateDoubleAwesomes(ty, diff, stats.mDoubleAwesomes);
        updated |= songStatus->UpdateTripleAwesomes(ty, diff, stats.mTripleAwesomes);
        return updated;
    }
    else {
        updated |= songStatus->UpdateSoloPercent(ty, diff, stats.mSoloPercent);
        updated |= songStatus->UpdateHOPOPercent(ty, diff, stats.mHOPOPercent);
        return updated;
    }
}

bool SongStatusMgr::UpdateSong(int songID, const PerformerStatsInfo& stats, bool b){
    MILO_ASSERT(songID != kSongID_Invalid && songID != kSongID_Any && songID != kSongID_Random, 0x42D);
    ScoreType ty = stats.mScoreType;
    Difficulty diff = stats.mDifficulty;
    SongStatus* status = CreateOrAccessSongStatus(songID);
    bool updated = status->UpdateScore(ty, diff, stats.mScore);
    if(updated){
        UpdateCachedTotalDiscScore(ty);
        UpdateCachedTotalScore(ty);
    }
    updated |= UpdateSongStats(ty, diff, stats, status);
    if(ty == kScoreBand && updated){
        status->SetInstrumentMask(stats.mInstrumentMask);
    }
    DateTime dt;
    GetDateAndTime(dt);
    status->SetLastPlayed(dt.ToCode());
    mCacheMgr.SetLastPlayed(dt.ToCode());
    if(mUpdatingStatus){
        if(songID == mUpdatingStatus->mSongID){
            if(mUpdatingScoreType == ty){
                if(mUpdatingDifficulty == diff){
                    TheRockCentral.CancelOutstandingCalls(this);
                    mUpdatingStatus = 0;
                }
            }
        }
    }
    status->SetDirty(ty, diff, !b && updated);
    if(ty == kScoreRealDrum){
        bool updatestats = UpdateSongStats(kScoreDrum, diff, stats, status);
        if(mUpdatingStatus && (songID == mUpdatingStatus->mSongID) && (mUpdatingScoreType == kScoreDrum) && (mUpdatingDifficulty == diff)){
            TheRockCentral.CancelOutstandingCalls(this);
            mUpdatingStatus = 0;
        }
        status->SetDirty(kScoreDrum, diff, !b && updated);
        updated |= updatestats;
    }
    return updated;
}

unsigned short SongStatusMgr::GetBandInstrumentMask(int idx) const {
    if(HasSongStatus(idx)){
        return GetSongStatus(idx)->GetInstrumentMask();
    }
    else return 0;
}

Difficulty SongStatusMgr::GetHighScoreDifficulty(int idx, ScoreType ty) const {
    if(HasSongStatus(idx)){
        return GetSongStatus(idx)->GetHighScoreDifficulty(ty);
    }
    else return kDifficultyEasy;
}

int SongStatusMgr::GetHighScore(int idx, ScoreType ty) const {
    if(HasSongStatus(idx)){
        return GetSongStatus(idx)->GetHighScore(ty);
    }
    else return 0;
}

int SongStatusMgr::GetScore(int idx, ScoreType ty) const {
    if(HasSongStatus(idx)){
        return GetSongStatus(idx)->GetScore(ty);
    }
    else return 0;
}

int SongStatusMgr::GetStars(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetStars(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestStars(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int stars = GetStars(idx, ty, (Difficulty)i);
        if(stars > best){
            best = stars;
        }
    }
    return best;
}

bool SongStatusMgr::IsSongPlayed(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetAccuracy(ty, diff);
    }
    else return 0;
}

bool SongStatusMgr::IsSongPlayedAtMinDifficulty(int idx, ScoreType ty, Difficulty diff) const {
    for(int i = diff; i < 4; i++){
        if(IsSongPlayed(idx, ty, (Difficulty)i)) return true;
    }
    return false;
}

int SongStatusMgr::GetAccuracy(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetAccuracy(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestAccuracy(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetAccuracy(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetStreak(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetStreak(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestStreak(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetStreak(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetSoloPercent(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetSoloPercent(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestSoloPercent(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetSoloPercent(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetHOPOPercent(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetHOPOPercent(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestHOPOPercent(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetHOPOPercent(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetAwesomes(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetAwesomes(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetDoubleAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetDoubleAwesomes(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestDoubleAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetDoubleAwesomes(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetTripleAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetTripleAwesomes(ty, diff);
    }
    else return 0;
}

int SongStatusMgr::GetBestTripleAwesomes(int idx, ScoreType ty, Difficulty diff) const {
    int best = 0;
    for(int i = diff; i < 4; i++){
        int acc = GetTripleAwesomes(idx, ty, (Difficulty)i);
        if(acc > best){
            best = acc;
        }
    }
    return best;
}

int SongStatusMgr::GetBestSongStatusFlag(Symbol, SongStatusFlagType, ScoreType, Difficulty) const {

}

int SongStatusMgr::GetCachedTotalDiscScore(ScoreType ty) const {
    return mCachedTotalDiscScores[ty];
}

int SongStatusMgr::GetCachedTotalScore(ScoreType ty) const {
    return mCachedTotalScores[ty];
}

int SongStatusMgr::GetCachedTotalStars(ScoreType ty) const {
    return mCachedTotalStars[ty];
}

void SongStatusMgr::UpdateCachedTotalDiscScore(ScoreType ty){
    mCachedTotalDiscScores[ty] = CalculateTotalScore(ty, rb3);
}

void SongStatusMgr::UpdateCachedTotalScore(ScoreType ty){
    mCachedTotalScores[ty] = CalculateTotalScore(ty, gNullStr);
}

void SongStatusMgr::UpdateCachedTotalStars(ScoreType ty){
    mCachedTotalStars[ty] = CalculateTotalStars(ty);
}

int SongStatusMgr::CalculateTotalScore(ScoreType ty, Symbol s) const {
    int ret = 0;
    for(int i = 0; i < 1000; i++){
        int songID = mCacheMgr.GetSongID(i);
        if(songID && mSongMgr->HasSong(songID)){
            if(s != gNullStr){
                BandSongMetadata* metaData = (BandSongMetadata*)mSongMgr->Data(songID);
                MILO_ASSERT(metaData, 0x63E);
                if(s != metaData->SourceSym()) continue;
            }
            SongStatus* status = mCacheMgr.GetSongStatusPtrForIndex(i);
            if(status){
                ret += status->GetHighScore(ty);
                if(ret > 2000000000) return 2000000000;
            }
        }
    }
    return ret;
}

int SongStatusMgr::GetTotalBestStars(ScoreType ty, Difficulty diff, Symbol s) const {
    int ret = 0;
    for(int i = 0; i < 1000; i++){
        int songID = mCacheMgr.GetSongID(i);
        if(songID && mSongMgr->HasSong(songID)){
            if(s != gNullStr){
                BandSongMetadata* metaData = (BandSongMetadata*)mSongMgr->Data(songID);
                MILO_ASSERT(metaData, 0x63E);
                if(s != metaData->SourceSym()) continue;
            }
            int beststars = GetBestStars(songID, ty, diff);
            int count = ret + beststars;
            if(beststars > 5) count = ret + 5;
            ret = count;
            if(count > 5000) return 5000;
        }
    }
    return ret;
}

int SongStatusMgr::CalculateTotalStars(ScoreType ty) const {
    
}

int SongStatusMgr::GetPossibleStars(ScoreType ty, Symbol s) const {
    int total = GetTotalSongs(ty, s);
    return Min(total * 5, 5000);
}

int SongStatusMgr::GetTotalSongs(ScoreType ty, Symbol s) const {
    TrackType trackty = ScoreTypeToTrackType(ty);
    return TheSongMgr->NumRankedSongs(trackty, ty == kScoreHarmony, s);
}

int SongStatusMgr::GetCompletedSongs(ScoreType, Difficulty, Symbol) const {

}

int SongStatusMgr::GetSongPlayCount(int idx) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetPlayCount();
    }
    else return 0;
}

void SongStatusMgr::SetSongPlayCount(int idx, int count){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x734);
    songStatus->SetPlayCount(count);
}

void SongStatusMgr::SetProGuitarSongLessonComplete(int idx, Difficulty diff){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x73C);
    songStatus->SetFlag(kSongStatusFlag_LessonComplete, kScoreRealGuitar, diff);
}

void SongStatusMgr::SetProBassSongLessonComplete(int idx, Difficulty diff){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x744);
    songStatus->SetFlag(kSongStatusFlag_LessonComplete, kScoreRealBass, diff);
}

void SongStatusMgr::SetProKeyboardSongLessonComplete(int idx, Difficulty diff){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x74C);
    songStatus->SetFlag(kSongStatusFlag_LessonComplete, kScoreRealKeys, diff);
}

bool SongStatusMgr::IsProGuitarSongLessonComplete(int idx, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckFlag(kSongStatusFlag_LessonComplete, kScoreRealGuitar, diff);
    }
    else return false;
}

bool SongStatusMgr::IsProBassSongLessonComplete(int idx, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckFlag(kSongStatusFlag_LessonComplete, kScoreRealBass, diff);
    }
    else return false;
}

bool SongStatusMgr::IsProKeyboardSongLessonComplete(int idx, Difficulty diff) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckFlag(kSongStatusFlag_LessonComplete, kScoreRealKeys, diff);
    }
    else return false;
}

void SongStatusMgr::SetProGuitarSongLessonSectionComplete(int idx, Difficulty diff, int bit){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x775);
    songStatus->SetProGuitarLessonSectionComplete(diff, bit, true);
}

void SongStatusMgr::SetProBassSongLessonSectionComplete(int idx, Difficulty diff, int bit){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x77D);
    songStatus->SetProBassLessonSectionComplete(diff, bit, true);
}

void SongStatusMgr::SetProKeyboardSongLessonSectionComplete(int idx, Difficulty diff, int bit){
    SongStatus* songStatus = CreateOrAccessSongStatus(idx);
    MILO_ASSERT(songStatus, 0x785);
    songStatus->SetProKeyboardLessonSectionComplete(diff, bit, true);
}

bool SongStatusMgr::IsProGuitarSongLessonSectionComplete(int idx, Difficulty diff, int bit) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckProGuitarLessonBit(diff, bit);
    }
    else return false;
}

bool SongStatusMgr::IsProBassSongLessonSectionComplete(int idx, Difficulty diff, int bit) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckProBassLessonBit(diff, bit);
    }
    else return false;
}

bool SongStatusMgr::IsProKeyboardSongLessonSectionComplete(int idx, Difficulty diff, int bit) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->CheckProKeyboardLessonBit(diff, bit);
    }
    else return false;
}

unsigned char SongStatusMgr::GetSongReview(int idx) const {
    if(HasSongStatus(idx)){
        SongStatus* status = GetSongStatus(idx);
        return status->GetReview();
    }
    else return 0;
}

bool SongStatusMgr::SetSongReview(int songID, unsigned char review){
    MILO_ASSERT(songID != kSongID_Invalid && songID != kSongID_Any && songID != kSongID_Random, 0x7BA);
    unsigned char cur = GetSongReview(songID);
    if(review == cur) return false;
    else {
        SongStatus* status = CreateOrAccessSongStatus(songID);
        status->SetReview(review);
        return true;
    }
}

void SongStatusMgr::SetSongStatusFlag(Symbol s, SongStatusFlagType flag, ScoreType ty, Difficulty diff){
    int songID = mSongMgr->GetSongIDFromShortName(s, true);
    SongStatus* status = CreateOrAccessSongStatus(songID);
    status->SetFlag(flag, ty, diff);
}

bool SongStatusMgr::GetSongStatusFlag(Symbol s, SongStatusFlagType flag, ScoreType ty, Difficulty diff) const {
    int songID = mSongMgr->GetSongIDFromShortName(s, true);
    if(HasSongStatus(songID)){
        SongStatus* status = GetSongStatus(songID);
        return status->CheckFlag(flag, ty, diff);
    }
    else {
        return false;
    }
}

void SongStatusMgr::PopulatePlayerScore(SongStatus* status, ScoreType ty, Difficulty diff, PlayerScore& pscore){
    int padnum = mLocalUser->GetPadNum();
    Server* netServer = TheNet.GetServer();
    MILO_ASSERT(netServer, 0x7E4);
    pscore.mPlayerID = netServer->GetPlayerID(padnum);
    pscore.mScoreType = ty;
    pscore.mDiff = diff;
    pscore.mTotalScore = mCachedTotalScores[ty];
    pscore.mTotalDiscScore = mCachedTotalDiscScores[ty];
    pscore.mAccuracy = status->GetAccuracy(ty, diff);
    pscore.mScore = status->GetScore(ty);
    pscore.mStars = status->GetStars(ty, diff);
}

void SongStatusMgr::UploadDirtyScores(){

}

DataNode SongStatusMgr::OnMsg(const RockCentralOpCompleteMsg& msg){
    int arg2 = msg->Int(2);
    bool fail = sFakeLeaderboardUploadFailure;
    bool upload = !fail && arg2;
    MILO_ASSERT(mUpdatingStatus, 0x85B);
    mUpdatingStatus->SetDirty(mUpdatingScoreType, mUpdatingDifficulty, !upload);
    mUpdatingStatus = 0;
    if(upload){
        UploadDirtyScores();
    }
    return 1;
}

int SongStatusMgr::SaveSize(int rev){
    int size = SongStatusCacheMgr::SaveSize(rev);
    if(rev >= 0x92) size += 0x58;
    if(rev >= 0x93) size += 0x2C;
    REPORT_SIZE("SongStatusMgr", size);
}

void SongStatusMgr::SaveFixed(FixedSizeSaveableStream& stream) const {
    mCacheMgr.SaveFixed(stream);
    for(int i = 0; i < 11; i++){
        stream << mCachedTotalScores[i];
        stream << mCachedTotalDiscScores[i];
        stream << mCachedTotalStars[i];
    }
}

void SongStatusMgr::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    mCacheMgr.LoadFixed(stream, rev);
    for(int i = 0; i < 11; i++){
        if(rev >= 0x92){
            stream >> mCachedTotalScores[i];
            stream >> mCachedTotalDiscScores[i];
        }
        else {
            UpdateCachedTotalScore((ScoreType)i);
            UpdateCachedTotalDiscScore((ScoreType)i);
        }
        if(rev >= 0x93){
            stream >> mCachedTotalStars[i];
        }
        else {
            UpdateCachedTotalStars((ScoreType)i);
        }
    }
}

void SongStatusMgr::FakeFill(){
    for(int i = 0; i < 1005; i++){
        CreateOrAccessSongStatus(i + 10000);
    }
}

BEGIN_HANDLERS(SongStatusMgr)
    HANDLE_EXPR(get_stars, GetStars(_msg->Int(2), (ScoreType)_msg->Int(3), (Difficulty)_msg->Int(4)))
    HANDLE_EXPR(get_accuracy, GetAccuracy(_msg->Int(2), (ScoreType)_msg->Int(3), (Difficulty)_msg->Int(4)))
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_CHECK(0x8EA)
END_HANDLERS
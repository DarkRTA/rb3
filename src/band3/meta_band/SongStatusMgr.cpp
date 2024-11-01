#include "SongStatusMgr.h"
#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include "utl/BinStream.h"

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
        mScores[i] = 0;
        // words at 0x74?
        mScoreDiffs[i] = 0;
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
        stream << mScores[i];
        // bytes at mScoreDiffs?
        stream << (unsigned char)mScoreDiffs[i];
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
        stream >> mScores[i];
        unsigned char uc;
        stream >> uc;
        mScoreDiffs[i] = uc;
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
    if(score > mScores[ty]){
        mScores[ty] = score;
        mScoreDiffs[ty] = diff;
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

SongStatusCacheMgr::SongStatusCacheMgr(const LocalBandUser** user) : mUser(user), unk1f54(0) {
    mStatuses = new SongStatus[1000];
    Clear();
    mSaveSizeMethod = &SaveSize;
}

SongStatus::SongStatus(){
    mSaveSizeMethod = &SaveSize;
    Clear();
}

SongStatus::~SongStatus(){

}
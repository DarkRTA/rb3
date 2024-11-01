#include "SongStatusMgr.h"
#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"
#include "os/Debug.h"
#include "utl/BinStream.h"

void SongStatusData::Clear(ScoreType ty){
    unk0 = 0;
    unk1 = 0;
    unk2 = 0;
    mFlags = 0;
    if(ty == kScoreVocals || ty == kScoreHarmony){
        unk5 = 0;
        unk6 = 0;
        unk7 = 0;
    }
    else {
        unk5 = 0;
        unk6 = 0;
    }
}

int SongStatusData::SaveSize(int){
    REPORT_SIZE("SongStatusData", 8);
}

void SongStatusData::SaveToStream(BinStream& bs, ScoreType ty) const {
    bs << unk0;
    bs << unk1;
    bs << unk2;
    bs << mFlags;
    if(ty == kScoreVocals || ty == kScoreHarmony){
        bs << unk5;
        bs << unk6;
        bs << unk7;
    }
    else {
        bs << unk5;
        bs << unk6;
        bs << unk7;
    }
}

void SongStatusData::LoadFromStream(BinStream& bs, ScoreType){
    bs >> unk0;
    bs >> unk1;
    bs >> unk2;
    bs >> mFlags;
    bs >> unk5;
    bs >> unk6;
    bs >> unk7;
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
        unk48[i] = 0;
        // words at 0x74?
        unk74[i] = 0;
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
        stream << unk48[i];
        // bytes at unk74?
        stream << (unsigned char)unk74[i];
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
        stream >> unk48[i];
        unsigned char uc;
        stream >> uc;
        unk74[i] = uc;
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
    return mSongData[scoreType][diff].unk6;
}

unsigned char SongStatus::GetHOPOPercent(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x214);
    return mSongData[scoreType][diff].unk5;
}

unsigned char SongStatus::GetAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x21B);
    return mSongData[scoreType][diff].unk5;
}

unsigned char SongStatus::GetDoubleAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x222);
    return mSongData[scoreType][diff].unk6;
}

unsigned char SongStatus::GetTripleAwesomes(ScoreType scoreType, Difficulty diff) const {
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x229);
    return mSongData[scoreType][diff].unk7;
}

bool SongStatus::UpdateScore(ScoreType ty, Difficulty diff, int score){
    if(score > unk48[ty]){
        unk48[ty] = score;
        unk74[ty] = diff;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateStars(ScoreType ty, Difficulty diff, unsigned char stars){
    if(stars > mSongData[ty][diff].unk0){
        mSongData[ty][diff].unk0 = stars;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateAccuracy(ScoreType ty, Difficulty diff, unsigned char acc){
    if(acc > mSongData[ty][diff].unk1){
        mSongData[ty][diff].unk1 = acc;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateStreak(ScoreType ty, Difficulty diff, unsigned short streak){
    if(streak > mSongData[ty][diff].unk2){
        mSongData[ty][diff].unk2 = streak;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateSoloPercent(ScoreType scoreType, Difficulty diff, unsigned char solopct){
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x25D);
    if(solopct > mSongData[scoreType][diff].unk6){
        mSongData[scoreType][diff].unk6 = solopct;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateHOPOPercent(ScoreType scoreType, Difficulty diff, unsigned char hopopct){
    MILO_ASSERT(( scoreType != kScoreHarmony ) && ( scoreType != kScoreVocals ), 0x26A);
    if(hopopct > mSongData[scoreType][diff].unk5){
        mSongData[scoreType][diff].unk5 = hopopct;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x277);
    if(awesomes > mSongData[scoreType][diff].unk5){
        mSongData[scoreType][diff].unk5 = awesomes;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateDoubleAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x284);
    if(awesomes > mSongData[scoreType][diff].unk6){
        mSongData[scoreType][diff].unk6 = awesomes;
        return true;
    }
    else return false;
}

bool SongStatus::UpdateTripleAwesomes(ScoreType scoreType, Difficulty diff, unsigned char awesomes){
    MILO_ASSERT(( scoreType == kScoreHarmony ) || ( scoreType == kScoreVocals ), 0x291);
    if(awesomes > mSongData[scoreType][diff].unk7){
        mSongData[scoreType][diff].unk7 = awesomes;
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
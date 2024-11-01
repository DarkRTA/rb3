#include "SongStatusMgr.h"
#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"
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
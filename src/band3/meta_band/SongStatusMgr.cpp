#include "SongStatusMgr.h"
#include "game/Defines.h"
#include "meta/FixedSizeSaveable.h"

void SongStatusData::Clear(ScoreType ty){
    unk0 = 0;
    unk1 = 0;
    unk2 = 0;
    unk4 = 0;
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
    bs << unk4;
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
    bs >> unk4;
    bs >> unk5;
    bs >> unk6;
    bs >> unk7;
}

void SongStatus::Clear(){
    mSongID = 0;
    mBandScoreInstrumentMask = 0;
    mReview = 0;
    mLastPlayed = 0;
    mLastPlayed = 0;
    for(int i = 0; i < 4; i++){
        mProGuitarLessonParts[i] = 0;
        mProBassLessonParts[i] = 0;
        mProKeyboardLessonParts[i] = 0;
    }
    
//   pSVar3 = this + 0xa0;
//   SVar2 = 0;
//   do {
//     *(undefined4 *)(this + 0x48) = 0;
//     iVar1 = 0;
//     *(undefined4 *)(this + 0x74) = 0;
//     this_00 = pSVar3;
//     do {
//       SongStatusData::Clear((SongStatusData *)this_00,SVar2);
//       iVar1 = iVar1 + 1;
//       this_00 = (SongStatus *)((SongStatusData *)this_00 + 8);
//     } while (iVar1 < 4);
//     SVar2 = SVar2 + 1;
//     pSVar3 = pSVar3 + 0x20;
//     this = this + 4;
//   } while ((int)SVar2 < 0xb);
//   return;
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
    
//   pSVar2 = this + 0xa0;
//   SVar1 = 0;
//   do {
//     local_34 = *(undefined4 *)(this + 0x48);
//     BinStream::WriteEndian((BinStream *)param_1,&local_34,4);
//     local_38 = (undefined)*(undefined4 *)(this + 0x74);
//     BinStream::Write((BinStream *)param_1,&local_38,1);
//     iVar3 = 0;
//     this_00 = pSVar2;
//     do {
//       SongStatusData::SaveToStream((SongStatusData *)this_00,(BinStream *)param_1,SVar1);
//       iVar3 = iVar3 + 1;
//       this_00 = (SongStatus *)((SongStatusData *)this_00 + 8);
//     } while (iVar3 < 4);
//     SVar1 = SVar1 + 1;
//     pSVar2 = pSVar2 + 0x20;
//     this = this + 4;
//   } while ((int)SVar1 < 0xb);
//   return;
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

SongStatus::SongStatus(){
    mSaveSizeMethod = &SaveSize;
    Clear();
}

SongStatus::~SongStatus(){

}
#include "beatmatch/GameGem.h"
#include "beatmatch/BeatMatchUtl.h"
#include "utl/TempoMap.h"

#define kMaxRGStrings 6

const char* gameGemStrings = "Bad slots %d\n";

GameGem::GameGem(const MultiGemInfo& info){
    mMs = info.ms;
    mTick = info.tick;
    mDurationMs = info.duration_ms;
    mDurationTicks = info.duration_ticks;
    mSlots = info.slots;
    unk10b7 = false;
    unk10b6 = info.no_strum == kStrumForceOn;
    unk10b5 = info.ignore_duration;
    unk10b4 = info.is_cymbal;
    mShowChordNames = true;
    mShowSlashes = true;
    unk10b1 = false;
    mRealGuitar = false;

    mLoose = false;
    mShowChordNums = false;
    mLeftHandSlide = false;
    mReverseSlide = false;
    mEnharmonic = false;

    unk18 = info.players;
    mChordNameOverride = gNullStr;
    mImportantStrings = 0;
}

GameGem::GameGem(const RGGemInfo& info){

}

GameGem::~GameGem(){

}

GameGem& GameGem::operator=(const GameGem& gem){
    mMs = gem.mMs;
    mTick = gem.mTick;
    mDurationMs = gem.mDurationMs;
    mDurationTicks = gem.mDurationTicks;
    mSlots = gem.mSlots;
    unk18 = gem.unk18;
    // 10
    unk10b7 = gem.unk10b7;
    unk10b6 = gem.unk10b6;
    unk10b5 = gem.unk10b5;
    unk10b4 = gem.unk10b4;
    mShowChordNames = gem.mShowChordNames;
    mShowSlashes = gem.mShowSlashes;
    unk10b1 = gem.unk10b1;
    mRealGuitar = gem.mRealGuitar;
    // 12
    mStrumType = gem.mStrumType;
    // 13
    mHandPosition = gem.mHandPosition;
    mRootNote = gem.mRootNote;
    mRGChordID = gem.mRGChordID;
    mChordNameOverride = gem.mChordNameOverride;
    // 11
    mLoose = gem.mLoose;
    mShowChordNums = gem.mShowChordNums;
    mLeftHandSlide = gem.mLeftHandSlide;
    mReverseSlide = gem.mReverseSlide;
    mEnharmonic = gem.mEnharmonic;

    mImportantStrings = gem.mImportantStrings;
    for(unsigned int i = 0; i < 6; i++){
        mFrets[i] = gem.mFrets[i];
        SetRGNoteTypeEntry(i, (RGNoteType)GetRGNoteTypeEntry(i));
    }
    return *this;
}

int GameGem::CountBitsInSlotType(unsigned int ui){
    int i1 = 0;
    for(unsigned int i = 32, i2 = 0; i != 0; i--, i2++){
        if(ui & 1 << i2){
            ui &= ~(1 << i2);
            i1++;
            if(ui == 0) return ui;
        }
        i2++;
    }
    return i1;
}

bool GameGem::IsRealGuitar() const { return mRealGuitar; }
bool GameGem::GetShowSlashes() const { return mShowSlashes; }
bool GameGem::GetShowChordNames() const { return mShowChordNames; }
unsigned char GameGem::GetRootNote() const { return mRootNote; }
bool GameGem::Loose() const { return mLoose; }
bool GameGem::ShowChordNums() const { return mShowChordNums; }
bool GameGem::LeftHandSlide() const { return mLeftHandSlide; }
bool GameGem::ReverseSlide() const { return mReverseSlide; }
bool GameGem::Enharmonic() const { return mEnharmonic; }

unsigned char GameGem::GetRGNoteType(unsigned int string) const {
    MILO_ASSERT(string < kMaxRGStrings, 0x14C);
    return GetRGNoteTypeEntry(string);
}

unsigned char GameGem::GetImportantStrings() const { return mImportantStrings; }
void GameGem::SetImportantStrings(unsigned char c){ mImportantStrings = c; }
unsigned char GameGem::GetHandPosition() const { return mHandPosition; }
int GameGem::GetRGChordID() const { return mRGChordID; }
const char* GameGem::GetChordNameOverride() const { return mChordNameOverride; }

char GameGem::GetFret(unsigned int string) const {
    MILO_ASSERT(string < kMaxRGStrings, 0x10C);
    return mFrets[string];
}

bool GameGem::RightHandTap() const {
    for(unsigned int i = 0; i < 6; i++){
        char curFret = mFrets[i];
        if(0 <= curFret){
            if((char)GetRGNoteTypeEntry(i) == 4) return true;
        }
    }
    return false;
}

unsigned int GameGem::GetLowestString() const {
    for(unsigned int i = 0; i < 6; i++){
        if(GetFret(i) != -1) return i;
    }
    return -1;
}

unsigned int GameGem::GetHighestString() const {
    for(int i = 5; i >= 0; i--){
        if(GetFret(i) != -1) return i;
    }
    return -1;
}

unsigned char GameGem::GetRGStrumType() const {
    return mStrumType;
}

void GameGem::SetFret(unsigned int string, signed char fret){
    MILO_ASSERT(string < kMaxRGStrings, 0x1BD);
    mFrets[string] = fret;
}

bool GameGem::PlayableBy(int i) const {
    return GemPlayableBy(unk18, i);
}

int GameGem::NumSlots() const {
    int bits = CountBitsInSlotType(mSlots);
    if(bits == 0){
        MILO_FAIL("Bad slots %d\n", mSlots);
    }
    return bits;
}

void GameGem::Flip(const GameGem& gem){
    unsigned int slot = gem.mSlots;
    if(slot == 2){
        mSlots = 4;
        unk10b4 = true;
        return;
    }
    if(slot != 4) return;
    mSlots = 2;
    unk10b4 = false;
}

void GameGem::RecalculateTimes(TempoMap* tmap){
    mMs = tmap->TickToTime(mTick);
    mDurationMs = tmap->TickToTime(mTick + mDurationTicks) - mMs;
}

bool GameGem::IsMuted() const {
    if(!mRealGuitar) return false;
    for(unsigned int i = 0; i < 6; i++){
        if(GetFret(i) == -1) continue;
        RGNoteType ty = (RGNoteType)GetRGNoteType(i);
        if(ty == kRGMuted) return true;
    }
    return false;
}

int GameGem::GetFret() const {
    int count = 0;
    int ret = -1;
    for(unsigned int i = 0; i < 6; i++){
        if(GetFret(i) != -1){
            ret = 3;
            count++;
        }
    }
    MILO_ASSERT(count == 1, 0x1A1);
    return ret;
}

int GameGem::GetNumStrings() const {
    int count = 0;
    for(unsigned int i = 0; i < 6; i++){
        if(GetFret(i) != -1){
            count++;
        }
    }
    return count;
}

int GameGem::GetNumFingers() const {
    int count = 0;
    for(unsigned int i = 0; i < 6; i++){
        if(GetFret(i) > 0){
            count++;
        }
    }
    return count;
}
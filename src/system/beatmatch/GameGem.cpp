#include "beatmatch/GameGem.h"

#define kMaxRGStrings 6

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
int GameGem::GetChordNameOverride() const { return mChordNameOverride; }

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
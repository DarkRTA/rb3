#ifndef BEATMATCH_GAMEGEM_H
#define BEATMATCH_GAMEGEM_H
#include "os/Debug.h"

class GameGem {
public:
    char GetFret(unsigned int) const;
    bool GetShowSlashes() const;
    unsigned char GetRootNote() const;
    bool IsRealGuitar() const;
    bool GetShowChordNames() const;
    bool Loose() const;
    bool ShowChordNums() const;
    bool LeftHandSlide() const;
    bool ReverseSlide() const;
    bool Enharmonic() const;
    unsigned char GetRGNoteType(unsigned int) const;
    unsigned char GetImportantStrings() const;
    void SetImportantStrings(unsigned char);
    unsigned char GetHandPosition() const;
    int GetRGChordID() const;
    bool RightHandTap() const;
    unsigned int GetLowestString() const;
    unsigned int GetHighestString() const;
    unsigned char GetRGStrumType() const;
    int GetChordNameOverride() const;
    void SetFret(unsigned int, signed char);

    unsigned char GetRGNoteTypeEntry(int x) const {
        switch(x){
            case 0: return unk14top;
            case 1: return unk14bot;
            case 2: return unk15top;
            case 3: return unk15bot;
            case 4: return unk16top;
            case 5: return unk16bot;
            default:
                MILO_ASSERT(0, 0xEE);
                return 0;
        }
    }

    float mMs;
    int mTick;
    unsigned short mDurationMs;
    unsigned short mDurationTicks;
    int unkc; // slot type?
    unsigned char unk10b7 : 1;
    unsigned char unk10b6 : 1;
    unsigned char unk10b5 : 1;
    unsigned char unk10b4 : 1;
    unsigned char mShowChordNames : 1;
    unsigned char mShowSlashes : 1;
    unsigned char unk10b1 : 1;
    unsigned char mRealGuitar : 1;
    unsigned char mLoose : 1;
    unsigned char mShowChordNums : 1;
    unsigned char mLeftHandSlide : 1;
    unsigned char mReverseSlide : 1;
    unsigned char mEnharmonic : 1;
    unsigned char unk11b2 : 1;
    unsigned char unk11b1 : 1;
    unsigned char unk11b0 : 1;    
    unsigned char mStrumType : 4;
    unsigned char unk12bot : 4;
    unsigned char mHandPosition : 5;
    unsigned char unk13bot : 3;

    unsigned char unk14top : 4;
    unsigned char unk14bot : 4;
    unsigned char unk15top : 4;
    unsigned char unk15bot : 4;
    unsigned char unk16top : 4;
    unsigned char unk16bot : 4;

    unsigned char mRootNote;
    unsigned char unk18;
    char mFrets[6];
    int mRGChordID;
    int mChordNameOverride;
    unsigned char mImportantStrings;
};

#endif
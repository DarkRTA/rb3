#ifndef BEATMATCH_GAMEGEM_H
#define BEATMATCH_GAMEGEM_H
#include "os/Debug.h"
#include "utl/PoolAlloc.h"
#include "beatmatch/GemInfo.h"

class TempoMap; // forward dec

class GameGem {
public:
    GameGem(const MultiGemInfo&);
    GameGem(const RGGemInfo&);
    ~GameGem();
    GameGem& operator=(const GameGem&);

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
    RGNoteType GetRGNoteType(unsigned int) const;
    unsigned char GetImportantStrings() const;
    void SetImportantStrings(unsigned char);
    unsigned char GetHandPosition() const;
    int GetRGChordID() const;
    bool RightHandTap() const;
    unsigned int GetLowestString() const;
    unsigned int GetHighestString() const;
    unsigned char GetRGStrumType() const;
    const char* GetChordNameOverride() const;
    void SetFret(unsigned int, signed char);
    bool PlayableBy(int) const;
    static int CountBitsInSlotType(unsigned int);
    int NumSlots() const;
    void Flip(const GameGem&);
    void RecalculateTimes(TempoMap*);
    bool IsMuted() const;
    int GetFret() const;
    int GetNumStrings() const;
    int GetNumFingers() const;
    void PackRealGuitarData();
    static int GetHighestSlot(unsigned int);
    bool IsRealGuitarChord() const;

    void* operator new(size_t s){
        return _PoolAlloc(s, 0x10, FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(GameGem), FastPool, v);
    }

    int GetSlot() const {
        for(unsigned int i = 0, ret = 0; i < 32; i++, ret++){
            if(mSlots & 1 << ret) return ret;
        }
        MILO_FAIL("Bad slots %d\n", mSlots);
        return -1;
    }

    RGNoteType GetRGNoteTypeEntry(int string) const {
        switch(string){
            case 0: return (RGNoteType)mRGNoteTypeStr0;
            case 1: return (RGNoteType)mRGNoteTypeStr1;
            case 2: return (RGNoteType)mRGNoteTypeStr2;
            case 3: return (RGNoteType)mRGNoteTypeStr3;
            case 4: return (RGNoteType)mRGNoteTypeStr4;
            case 5: return (RGNoteType)mRGNoteTypeStr5;
            default:
                MILO_ASSERT(0, 0xEE);
                return kRGNormal;
        }
    }

    void SetRGNoteTypeEntry(int x, RGNoteType ty){
        switch(x){
            case 0: mRGNoteTypeStr0 = ty; break;
            case 1: mRGNoteTypeStr1 = ty; break;
            case 2: mRGNoteTypeStr2 = ty; break;
            case 3: mRGNoteTypeStr3 = ty; break;
            case 4: mRGNoteTypeStr4 = ty; break;
            case 5: mRGNoteTypeStr5 = ty; break;
            default:
                MILO_ASSERT(0, 0xFC);
                break;
        }
    }

    bool GetPlayed(){ return mPlayed != 0; }

    float mMs;
    int mTick;
    unsigned short mDurationMs;
    unsigned short mDurationTicks;
    unsigned int mSlots;

    unsigned char mPlayed : 1;
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

    // RGNoteTypes for each guitar string
    unsigned char mRGNoteTypeStr0 : 4;
    unsigned char mRGNoteTypeStr1 : 4;
    unsigned char mRGNoteTypeStr2 : 4;
    unsigned char mRGNoteTypeStr3 : 4;
    unsigned char mRGNoteTypeStr4 : 4;
    unsigned char mRGNoteTypeStr5 : 4;

    unsigned char mRootNote;
    unsigned char unk18; // mPlayers?
    char mFrets[6];
    int mRGChordID;
    const char* mChordNameOverride;
    unsigned char mImportantStrings;
};

#endif
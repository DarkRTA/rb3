#pragma once
#include "os/Debug.h"
#include "utl/PoolAlloc.h"
#include "beatmatch/GemInfo.h"
#include "utl/Symbol.h"

class TempoMap; // forward dec

class GameGem {
public:
    GameGem(const MultiGemInfo &);
    GameGem(const RGGemInfo &);
    ~GameGem();
    GameGem &operator=(const GameGem &);

    signed char GetFret(unsigned int) const;
    char GetHighestFret() const;
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
    int GetRGStrumType() const;
    Symbol GetChordNameOverride() const;
    void SetFret(unsigned int, signed char);
    bool PlayableBy(int) const;
    static int CountBitsInSlotType(unsigned int);
    int NumSlots() const;
    void Flip(const GameGem &);
    void RecalculateTimes(TempoMap *);
    bool IsMuted() const;
    int GetFret() const;
    int GetNumStrings() const;
    int GetNumFingers() const;
    void PackRealGuitarData();
    static int GetHighestSlot(unsigned int);
    bool IsRealGuitarChord() const;
    void CopyGem(GameGem *, int);

    NEW_POOL_OVERLOAD(GameGem);
    DELETE_POOL_OVERLOAD(GameGem);

    bool operator<(const GameGem &g) const { return mMs < g.mMs; }

    int GetTick() const { return mTick; }
    bool IgnoreDuration() const { return mIgnoreDuration; }
    unsigned int GetSlots() const { return mSlots; }
    bool GetForceStrum() const { return mForceStrum; }
    int GetDurationTicks() const { return mDurationTicks; }

    bool CompareTimes(const GameGem &g1, const GameGem &g2) { return g1.mMs < g2.mMs; }

    int GetSlot() const {
        for (unsigned int i = 0; i < 32; i++) {
            if (mSlots & 1 << i)
                return i;
        }
        MILO_FAIL("Bad slots %d\n", mSlots);
        return -1;
    }

    RGNoteType GetRGNoteTypeEntry(int string) const {
        switch (string) {
        case 0:
            return (RGNoteType)mRGNoteTypeStr0;
        case 1:
            return (RGNoteType)mRGNoteTypeStr1;
        case 2:
            return (RGNoteType)mRGNoteTypeStr2;
        case 3:
            return (RGNoteType)mRGNoteTypeStr3;
        case 4:
            return (RGNoteType)mRGNoteTypeStr4;
        case 5:
            return (RGNoteType)mRGNoteTypeStr5;
        default:
            MILO_ASSERT(0, 0xEE);
            return kRGNormal;
        }
    }

    void SetRGNoteTypeEntry(int x, RGNoteType ty) {
        switch (x) {
        case 0:
            mRGNoteTypeStr0 = ty;
            break;
        case 1:
            mRGNoteTypeStr1 = ty;
            break;
        case 2:
            mRGNoteTypeStr2 = ty;
            break;
        case 3:
            mRGNoteTypeStr3 = ty;
            break;
        case 4:
            mRGNoteTypeStr4 = ty;
            break;
        case 5:
            mRGNoteTypeStr5 = ty;
            break;
        default:
            MILO_ASSERT(0, 0xFC);
            break;
        }
    }

    bool GetPlayed() { return mPlayed != 0; }
    void SetPlayed(bool played) { mPlayed = played; }
    float DurationMs() { return mDurationMs; }
    bool Unk10B1() const { return unk10b1; }
    void SetUnk10B1(bool b) { unk10b1 = b; }
    bool IsCymbal() const { return mIsCymbal; }

    float mMs; // 0x0
    int mTick; // 0x4
    unsigned short mDurationMs; // 0x8
    unsigned short mDurationTicks; // 0xa
    unsigned int mSlots; // 0xc

    unsigned char mPlayed : 1;
    unsigned char mForceStrum : 1;
    unsigned char mIgnoreDuration : 1;
    unsigned char mIsCymbal : 1;
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

    unsigned char mRootNote : 8;
    unsigned char unk18 : 8; // mPlayers?
    char mFrets[6];
    int mRGChordID;
    Symbol mChordNameOverride;
    unsigned char mImportantStrings;
};

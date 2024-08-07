#ifndef BEATMATCH_VOCALNOTE_H
#define BEATMATCH_VOCALNOTE_H
#include "utl/Str.h"
#include "obj/Data.h"

class SongData;

class VocalNote {
public:
    VocalNote() : mPhrase(-1), mBeginPitch(0), mEndPitch(0), mMs(0), mTick(0), mDurationMs(0), mDurationTicks(0),
        mPhraseEnd(0), mUnpitchedPhrase(0), mUnpitchedNote(0), mUnpitchedEasy(0), mPitchRangeEnd(0), mPlayerMask(0),
        mBends(0), mLyricShift(0), mAllowCombine(1) {}

    int GetTick() const { return mTick; }
    void SetNoteTime(float ms, int tick){
        mMs = ms;
        mTick = tick;
    }
    void SetStartPitch(int pitch){ mBeginPitch = pitch; }
    void SetEndPitch(int pitch){ mEndPitch = pitch; }
    float GetDurationMs() const { return mDurationMs; }
    float GetMs() const { return mMs; }
    unsigned short GetDurationTicks() const { return mDurationTicks; }

    void SetDurationTime(float ms, int tick){
        mDurationMs = ms;
        mDurationTicks = tick;
    }
    void SetBends(bool bends){ mBends = bends; }
    void SetText(const char* text){ mText = text; }

    int StartPitch() const { return mBeginPitch; }
    int EndPitch() const { return mEndPitch; }

    int mPhrase; // 0x0
    int mBeginPitch; // 0x4
    int mEndPitch; // 0x8
    float mMs; // 0xc
    int mTick; // 0x10
    float mDurationMs; // 0x14
    unsigned short mDurationTicks; // 0x18
    String mText; // 0x1c
    bool mPhraseEnd; // 0x28
    bool mUnpitchedPhrase; // 0x29
    bool mUnpitchedNote; // 0x2a
    bool mUnpitchedEasy; // 0x2b
    bool mPitchRangeEnd; // 0x2c
    unsigned char mPlayerMask; // 0x2d
    bool mBends; // 0x2e
    bool mLyricShift; // 0x2f
    bool mAllowCombine; // 0x30
};

class VocalPhrase {
public:
    VocalPhrase();
    VocalPhrase(const VocalPhrase&);

    float unk0;
    float unk4;
    int unk8;
    int unkc;
    int unk10;
    int unk14;
    bool unk18;
    bool unk19;
    bool unk1a;
    int unk1c;
    float unk20;
    float unk24;
    float unk28;
    bool unk2c;
    bool unk2d;
    float unk30;
    float unk34;
};

class VocalNoteList {
public:
    VocalNoteList(SongData*);

    std::vector<int> mPhrases; // 0x0
    std::vector<int> mLyricPhrases; // 0x8
    std::vector<int> mNotes; // 0x10
    std::vector<int> mTambourineGems; // 0x18
    std::vector<int> mFreestyleSections; // 0x20
    Symbol mTrackName; // 0x28
    SongData* mSongData; // 0x2c
    DataArray* mFreestyleMinDuration; // 0x30
    DataArray* mFreestylePad; // 0x34
};

#endif
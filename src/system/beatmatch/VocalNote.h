#ifndef BEATMATCH_VOCALNOTE_H
#define BEATMATCH_VOCALNOTE_H
#include "utl/Str.h"
#include "obj/Data.h"
#include "utl/MBT.h"

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
    bool IsUnpitched() const { return mUnpitchedNote; }
    void SetPhraseEnd(bool b){ mPhraseEnd = b; }
    bool LyricShift() const { return mLyricShift; }

    void SetDurationTime(float ms, int tick){
        mDurationMs = ms;
        mDurationTicks = tick;
    }
    void SetBends(bool bends){ mBends = bends; }
    void SetText(const char* text){ mText = text; }

    int StartPitch() const { return mBeginPitch; }
    int EndPitch() const { return mEndPitch; }
    int EndTick() const { return mTick + mDurationTicks; }

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
    VocalPhrase(const VocalPhrase& phrase) : unk0(phrase.unk0), unk4(phrase.unk4), unk8(phrase.unk8), unkc(phrase.unkc), unk10(phrase.unk10), unk14(phrase.unk14), unk18(phrase.unk18),
        unk19(phrase.unk19), unk1a(phrase.unk1a), unk1c(phrase.unk1c), unk20(phrase.unk20), unk24(phrase.unk24), unk28(phrase.unk28), unk2c(phrase.unk2c), unk2d(phrase.unk2d),
        unk30(phrase.unk30), unk34(phrase.unk34) {}

    bool Diff() const { return (unk14 - unk10) == 0; }


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

#include "beatmatch/SongData.h"

class VocalNoteList {
public:
    VocalNoteList(SongData*);
    void Clear();
    void CopyPhrasesFrom(const VocalNoteList*);
    void CopyLyricPhrases();
    void AddNote(const VocalNote&);
    void NotesDone(const TempoMap&, bool);
    void AddTambourineGem(int);

    const char* PrintTick(int tick) const {
        return TickFormat(tick, *mSongData->GetMeasureMap());
    }

    std::vector<VocalPhrase> mPhrases; // 0x0
    std::vector<VocalPhrase> mLyricPhrases; // 0x8
    std::vector<VocalNote> mNotes; // 0x10
    std::vector<int> mTambourineGems; // 0x18
    std::vector<std::pair<float, float> > mFreestyleSections; // 0x20
    Symbol mTrackName; // 0x28
    SongData* mSongData; // 0x2c
    DataArray* mFreestyleMinDuration; // 0x30
    DataArray* mFreestylePad; // 0x34
};

#endif
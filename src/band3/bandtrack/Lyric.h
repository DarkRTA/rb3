#ifndef BANDTRACK_LYRIC_H
#define BANDTRACK_LYRIC_H

#include <vector>
#include <float.h>
#include "rndobj/Text.h"
#include "obj/Object.h"
#include "utl/Str.h"
#include "beatmatch/VocalNote.h"

class LyricPlate : public Hmx::Object {
public:
    LyricPlate(RndText *, const RndText *, const RndText *);

    void SetShowing(bool);

    float CurrentStartX(float) const;
    float CurrentEndX(float) const;

    // void Poll(float);

    float mWidthX; // 0x1c
    int mNumCharsUsed; // 0x20

    // TrackWidget
    void *mText; // 0x24

    // Need syllable type
    std::vector<void *> mSyllables; // 0x28

    Hmx::Color mPreviewColor; // 0x34
    Hmx::Color mActiveColor; // 0x44
    Hmx::Color mNowColor; // 0x54
    Hmx::Color mPastColor; // 0x64
    Hmx::Color mPreviewPhonemeColor; // 0x74
    Hmx::Color mActivePhonemeColor; // 0x84
    Hmx::Color mNowPhonemeColor; // 0x94
    Hmx::Color mPastPhonemeColor; // 0xa4

    RndText::Style mPitchedStyle; // 0xb4
    RndText::Style mUnpitchedStyle; // 0xe4

    float mInvalidateMs; // 0x114
    bool mBaked; // 0x118
    bool mNeedSync; // 0x119
    bool mPastNow; // 0x11a
};

class Lyric : public Hmx::Object {
public:
    Lyric(const VocalNote *, bool, String, bool);

    int StartTick() const;

    float Width() const;
    float EndPos() const;

    bool PitchNote() const;

    void SetChunkEnd(bool);
    void SetAfterDeploy(int);
    void SetAfterMidPhraseLyricShift(bool);

    bool UpdateColor(Hmx::Color);

    int mIdx; // 0x1c
    String mText; // 0x20
    bool mPitched; // 0x2c
    std::vector<const VocalNote *> mVocalNotes; // 0x30
    int mLead; // 0x38
    bool mWordEnd; // 0x3c
    bool mChunkEnd; // 0x3d
    int mDeployIdx; // 0x40

    bool mAfterMidPhraseShift; // 0x44

    float unk_0x48; // 0x48
    float unk_0x4c; // 0x4c
    float unk_0x50; // 0x50

    float mXWidth; // 0x54
    float mHighlightMs; // 0x58
    float mActiveMs; // 0x5c
    float mEndMs; // 0x60
    float mInvalidateMs; // 0x64

    bool mPhraseEnd; // 0x68

    Hmx::Color mLastColor; // 0x69
};

#endif // BANDTRACK_LYRIC_H
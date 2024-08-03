#ifndef BEATMATCH_VOCALNOTE_H
#define BEATMATCH_VOCALNOTE_H
#include "utl/Str.h"

class VocalNote {
public:
    VocalNote() : mPhrase(-1), mBeginPitch(0), mEndPitch(0), mMs(0), mTick(0), mDurationMs(0), mDurationTicks(0),
        mPhraseEnd(0), mUnpitchedPhrase(0), mUnpitchedNote(0), mUnpitchedEasy(0), mPitchRangeEnd(0), mPlayerMask(0),
        mBends(0), mLyricShift(0), mAllowCombine(1) {}

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

#endif
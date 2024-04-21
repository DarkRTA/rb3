#ifndef BEATMATCH_VOCALNOTE_H
#define BEATMATCH_VOCALNOTE_H
#include "utl/Str.h"

class VocalNote {
public:
    int mPhrase;
    int mBeginPitch;
    int mEndPitch;
    float mMs;
    int mTick;
    float mDurationMs;
    unsigned short mDurationTicks;
    String mText;
    bool mPhraseEnd;
    bool mUnpitchedPhrase;
    bool mUnpitchedNote;
    bool mUnpitchedEasy;
    bool mPitchRangeEnd;
    unsigned char mPlayerMask;
    bool mBends;
    bool mLyricShift;
    bool mAllowCombine;
};

#endif

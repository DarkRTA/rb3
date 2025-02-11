#pragma once
#include <vector>
#include <float.h>
#include "rndobj/Text.h"
#include "obj/Object.h"
#include "utl/Str.h"
#include "track/TrackWidget.h"
#include "beatmatch/VocalNote.h"

class Lyric : public Hmx::Object {
public:
    Lyric(const VocalNote *, bool, String, bool);
    virtual ~Lyric();

    int StartTick() const;
    float Width() const;
    float EndPos() const;
    bool PitchNote() const;
    void SetChunkEnd(bool);
    void SetAfterDeploy(int);
    void SetAfterMidPhraseLyricShift(bool);
    bool UpdateColor(Hmx::Color);
    bool GetChunkEnd() const { return mChunkEnd; }

    int mIdx; // 0x1c
    String mText; // 0x20
    bool mPitched; // 0x2c
    std::vector<const VocalNote *> mVocalNotes; // 0x30
    int mLead; // 0x38
    bool mWordEnd; // 0x3c
    bool mChunkEnd; // 0x3d
    int mDeployIdx; // 0x40
    bool mAfterMidPhraseShift; // 0x44
    Vector3 unk48; // 0x48
    float mXWidth; // 0x54
    float mHighlightMs; // 0x58
    float mActiveMs; // 0x5c
    float mEndMs; // 0x60
    float mInvalidateMs; // 0x64
    bool mPhraseEnd; // 0x68
    Hmx::Color mLastColor; // 0x6c
};

class LyricPlate : public Hmx::Object {
public:
    LyricPlate(RndText *, const RndText *, const RndText *);
    virtual ~LyricPlate();

    void SetShowing(bool);
    float CurrentStartX(float) const;
    float CurrentEndX(float) const;
    void CheckSync();
    void Reset();
    Lyric *LatestLyric();
    void AddLyric(Lyric *);
    void EstimateLyricWidth(const Lyric *);
    void HookUpParents(RndGroup *, RndTransformable *);
    bool Empty() const;
    void UpdateStaticTiming(float);
    float GetBeginMs() const;
    float GetLastLyricXBeforeMS(float) const;
    void Poll(float);
    void BakeLyric(Lyric *);
    bool Baked() const { return mBaked; }

    float mWidthX; // 0x1c
    int mNumCharsUsed; // 0x20
    RndText *mText; // 0x24
    std::vector<Lyric *> mSyllables; // 0x28
    Hmx::Color mPreviewColor; // 0x30
    Hmx::Color mActiveColor; // 0x40
    Hmx::Color mNowColor; // 0x50
    Hmx::Color mPastColor; // 0x60
    Hmx::Color mPreviewPhonemeColor; // 0x70
    Hmx::Color mActivePhonemeColor; // 0x80
    Hmx::Color mNowPhonemeColor; // 0x90
    Hmx::Color mPastPhonemeColor; // 0xa0
    RndText::Style mPitchedStyle; // 0xb0
    RndText::Style mUnpitchedStyle; // 0xc8
    float mInvalidateMs; // 0xe0
    bool mBaked; // 0xe4
    bool mNeedSync; // 0xe5
    bool mPastNow; // 0xe6
};

#include "Lyric.h"
#include "math/Color.h"
#include "rndobj/Group.h";

int kMaxLyricPlateChars = 0x64;
int kMaxLyricPlateLines = 0x1E;

LyricPlate::LyricPlate(RndText *t1, const RndText *t2, const RndText *t3)
    : mWidthX(0), mNumCharsUsed(0), mText(t1), mSyllables(), mPreviewColor(),
      mActiveColor(), mNowColor(), mPastColor(), mPreviewPhonemeColor(),
      mActivePhonemeColor(), mNowPhonemeColor(), mPastPhonemeColor(), mPitchedStyle(),
      mUnpitchedStyle(), mInvalidateMs(FLT_MAX), mBaked(0), mNeedSync(0), mPastNow(0) {
    mText->SetFixedLength(kMaxLyricPlateChars);
    mText->SetText("");
    mPitchedStyle = t2->mStyle;
    mUnpitchedStyle = t3->mStyle;
    mText->ReserveLines(kMaxLyricPlateLines);
}

LyricPlate::~LyricPlate() {
    RELEASE(mText);
    for (int i = 0; i < mSyllables.size(); i++) {
        RELEASE(mSyllables[i]);
    }
    mSyllables.clear();
}

void LyricPlate::SetShowing(bool show) { mText->SetShowing(show); }

float LyricPlate::CurrentStartX(float start) const {
    return start + mText->mLocalXfm.v.x;
}

float LyricPlate::CurrentEndX(float end) const {
    return end + mWidthX + mText->mLocalXfm.v.x;
}

void LyricPlate::Poll(float f) {
    bool b1 = false;
    for (int i = mSyllables.size() - 1; i >= 0; i--) {
        Lyric *curLyric = mSyllables[i];
        if (curLyric->mIdx >= 0) {
            if (curLyric->mWordEnd) {
                b1 |= (curLyric->mEndMs < f);
            }
            if (curLyric->mInvalidateMs < f || (mPastNow && b1)) {
                static Hmx::Color invis(0, 0, 0, 0);
                mText->UpdateLineColor(curLyric->mIdx, invis, &mNeedSync);
                curLyric->mIdx = -1;
            } else if (curLyric->mEndMs < f) {
                Hmx::Color &color = curLyric->mPitched ? mPastColor : mPastPhonemeColor;
                if (curLyric->UpdateColor(color)) {
                    mText->UpdateLineColor(curLyric->mIdx, color, &mNeedSync);
                }
            } else if (curLyric->mActiveMs < f) {
                Hmx::Color &color = curLyric->mPitched ? mNowColor : mNowPhonemeColor;
                if (curLyric->UpdateColor(color)) {
                    mText->UpdateLineColor(curLyric->mIdx, color, &mNeedSync);
                }
            } else if (curLyric->mHighlightMs < f) {
                Hmx::Color &color =
                    curLyric->mPitched ? mActiveColor : mActivePhonemeColor;
                curLyric->UpdateColor(color);
                mText->UpdateLineColor(curLyric->mIdx, color, &mNeedSync);
            } else {
                Hmx::Color &color =
                    curLyric->mPitched ? mPreviewColor : mPreviewPhonemeColor;
                if (curLyric->UpdateColor(color)) {
                    mText->UpdateLineColor(curLyric->mIdx, color, &mNeedSync);
                }
            }
        }
    }
    CheckSync();
}

void LyricPlate::CheckSync() {
    MILO_ASSERT(mText != 0, 0x76);
    if (mNeedSync) {
        mText->SyncMeshes();
        mNeedSync = false;
    }
}

void LyricPlate::Reset() {
    mText->SetText(0);
    mWidthX = 0;
    mNumCharsUsed = 0;
    mPitchedStyle.zOffset = FLT_MAX;
    mUnpitchedStyle.font = 0;

    mSyllables.clear();
    SetShowing(false);
}

Lyric *LyricPlate::LatestLyric() {
    int size = mSyllables.size();

    if (size != 0) {
        return mSyllables[size - 1];
    }

    return 0;
}

void LyricPlate::AddLyric(Lyric *lyric) {
    int size = mSyllables.size();

    mSyllables.push_back(lyric);

    float *end;

    float end100 = lyric->mEndMs + 100;

    if (mPitchedStyle.zOffset < end100) {
        end = &end100;
    } else {
        end = &mPitchedStyle.zOffset;
    }

    mPitchedStyle.zOffset = *end;
}

void LyricPlate::EstimateLyricWidth(const Lyric *lyric) {
    RndText::Style *style;

    if (!lyric->mPitched) {
        style = &mUnpitchedStyle;
    } else {
        style = &mPitchedStyle;
    }

    mText->GetStringWidthUTF8(mText->mText.c_str(), 0, false, style);
}

void LyricPlate::HookUpParents(RndGroup *group, RndTransformable *trans) {
    group->AddObject(mText, 0);
    trans->SetTransParent(mText->mParent, false);
}

bool LyricPlate::Empty() const { return mSyllables.empty(); }

void LyricPlate::UpdateStaticTiming(float time) {
    MILO_ASSERT(mSyllables.size() != 0, 0xcf);

    float f = 0;
    float fArr = 0;
    for (int i = 0; i < mSyllables.size(); i++) {
        Lyric *lyric = mSyllables[i];

        if (i == 0 || lyric->mDeployIdx != -1) {
            f = lyric->mActiveMs - time;
        } else if (lyric->mAfterMidPhraseShift) {
            f = lyric->mActiveMs;
        }

        lyric->mHighlightMs = f;
    }

    for (int i = 0; i < mSyllables.size(); i++) {
        Lyric *lyric = mSyllables[i];

        float validMs;
        if (lyric->mChunkEnd) {
            fArr = lyric->mEndMs + 100;

            if (fArr <= lyric->mInvalidateMs) {
                validMs = fArr;
            } else {
                validMs = lyric->mInvalidateMs;
            }
        }
        lyric->mInvalidateMs = validMs;
    }
}

float LyricPlate::GetBeginMs() const {
    if (mSyllables.size() != 0) {
        return mSyllables[0]->mActiveMs;
    } else {
        return FLT_MAX;
    }
}

float LyricPlate::GetLastLyricXBeforeMS(float ms) const {
    int size = mSyllables.size();

    float last = 0;
    Lyric *lyric;

    for (int i = 0; i < size; i++) {
        lyric = mSyllables[i];

        if (lyric->mActiveMs > ms) {
            last = ms;
        }

        float x = lyric->unk_0x48 + lyric->mXWidth;

        if (last < x) {
            last = x;
        }
    }
    return last;
}

Lyric::Lyric(const VocalNote *vocalNote, bool param2, String param3, bool param4)
    : mIdx(-1), mText(param3), mPitched(vocalNote->mUnpitchedNote), mLead(!param2),
      mWordEnd(param4), mChunkEnd(false), mDeployIdx(-1), mAfterMidPhraseShift(false),
      mXWidth(0), mHighlightMs(FLT_MAX), mInvalidateMs(FLT_MAX),
      mEndMs(vocalNote->mMs + vocalNote->mDurationMs), mPhraseEnd(false),
      mLastColor(0, 0, 0) {
    mVocalNotes.push_back(vocalNote);
}

int Lyric::StartTick() const { return mVocalNotes[0]->mTick; }

float Lyric::Width() const { return mXWidth; }

float Lyric::EndPos() const { return mXWidth + unk_0x48; }

bool Lyric::PitchNote() const { return !mVocalNotes[0]->mUnpitchedNote; }

void Lyric::SetChunkEnd(bool chunkEnd) { mChunkEnd = chunkEnd; }

void Lyric::SetAfterDeploy(int deploy) { mDeployIdx = deploy; }

void Lyric::SetAfterMidPhraseLyricShift(bool afterMidPhrase) {
    mAfterMidPhraseShift = afterMidPhrase;
}

bool Lyric::UpdateColor(Hmx::Color color) {
    if (color != mLastColor) {
        mLastColor = color;
        return true;
    } else
        return false;
}
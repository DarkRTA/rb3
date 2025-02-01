#include "Lyric.h"

#include "obj/ObjVersion.h"
#include "system/rndobj/Group.h";

int kMaxLyricPlateLines = 0x1E;

LyricPlate::LyricPlate(RndText *param1, const RndText *param2, const RndText *param3)
    : mWidthX(0), mNumCharsUsed(0), mText(param1), mSyllables(), mPreviewColor(),
      mActiveColor(), mNowColor(), mPastColor(), mPreviewPhonemeColor(),
      mActivePhonemeColor(), mNowPhonemeColor(), mPastPhonemeColor(),
      mPitchedStyle(0, 0, 0, 0, 0), mUnpitchedStyle(0, 0, 0, 0, 0) {
    // param1->SetFixedLength(kMaxLyricPlateLines);
    param1->ReserveLines(kMaxLyricPlateLines);
}

void LyricPlate::SetShowing(bool show) { mText->mShowing = show; }

float LyricPlate::CurrentStartX(float start) const {
    return start + mText->mLocalXfm.v.x;
}

float LyricPlate::CurrentEndX(float end) const {
    float order = end + mText->mOrder;

    float pos = order + mText->mLocalXfm.v.x;

    return pos;
}

void LyricPlate::CheckSync() {
    MILO_ASSERT(mText != 0, 0x76);

    if (mUnpitchedStyle.font != 0) {
        mText->SyncMeshes();
        mUnpitchedStyle.font = 0;
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
    bool same = false;

    if (color.red == mLastColor.red && color.green == mLastColor.green
        && color.blue == mLastColor.blue && color.alpha == mLastColor.alpha) {
        same = true;
    }

    if (!same) {
        mLastColor.red = color.red;
        mLastColor.green = color.green;
        mLastColor.blue = color.blue;
        mLastColor.alpha = color.alpha;

        return true;
    }

    return false;
}
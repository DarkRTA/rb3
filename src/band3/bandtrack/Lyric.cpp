#include "Lyric.h"

#include "obj/ObjVersion.h"
#include "system/rndobj/Group.h";

int kMaxLyricPlateLines = 0x1E;

LyricPlate::LyricPlate(RndText *param1, const RndText *param2, const RndText *param3)
    : mWidthX(0), mNumCharsUsed(0), mText(param1), mSyllables(), mPreviewColor(),
      mActiveColor(), mNowColor(), mPastColor(), mPreviewPhonemeColor(),
      mActivePhonemeColor(), mNowPhonemeColor(), mPastPhonemeColor(), mPitchedStyle() {
    // param1->SetFixedLength(kMaxLyricPlateLines);
    param1->ReserveLines(kMaxLyricPlateLines);
}

void LyricPlate::SetShowing(bool show) {
    mText->mShowing = show;
}

float LyricPlate::CurrentStartX(float start) const {
    // return start + mText->mWrapWidth;
}

float LyricPlate::CurrentEndX(float end) const {
    // return end + mText->mLocalXfm.v.x;
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
    mPitchedStyle.unk_2c = FLT_MAX;
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

    if (mPitchedStyle.unk_2c < end100) {
        end = &end100;
    } else {
        end = &mPitchedStyle.unk_2c;
    }

    mPitchedStyle.unk_2c = *end;
}

void LyricPlate::EstimateLyricWidth(const Lyric *lyric) {
    RndText::Style *style;

    if (!lyric->mPitched) {
        style = &mUnpitchedStyle;
    } else {
        style = &mPitchedStyle;
    }

    mText->GetStringWidthUTF8(mText->unk_cc.mStr, 0, false, style);
}

void LyricPlate::HookUpParents(RndGroup *group, RndTransformable *trans) {
    group->AddObject(mText, 0);
    trans->SetTransParent(mText, false);
}

bool LyricPlate::Empty() const {
    return mSyllables.empty();
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

    int i = 0;
    int j = 0;
    while (size != 0 && mSyllables[i]->mActiveMs <= ms) {
    }
}

Lyric::Lyric(const VocalNote *vocalNote, bool param2, String param3, bool param4)
    : mIdx(-1), mText(param3), mPitched(vocalNote->mUnpitchedNote), mLead(!param2),
      mWordEnd(param4), mChunkEnd(false), mDeployIdx(-1), mAfterMidPhraseShift(false),
      mXWidth(0), mHighlightMs(FLT_MAX), mInvalidateMs(FLT_MAX),
      mEndMs(vocalNote->mMs + vocalNote->mDurationMs), mPhraseEnd(false),
      mLastColor(0, 0, 0) {
    mVocalNotes.push_back(vocalNote);
}

int Lyric::StartTick() const {
    return mVocalNotes[0]->mTick;
}

float Lyric::Width() const {
    return mXWidth;
}

float Lyric::EndPos() const {
    return mXWidth + unk_0x48;
}

bool Lyric::PitchNote() const {
    return !mVocalNotes[0]->mUnpitchedNote;
}

void Lyric::SetChunkEnd(bool chunkEnd) {
    mChunkEnd = chunkEnd;
}

void Lyric::SetAfterDeploy(int deploy) {
    mDeployIdx = deploy;
}

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
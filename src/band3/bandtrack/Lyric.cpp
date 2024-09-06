#include "Lyric.h"

#include "obj/ObjVersion.h"

int kMaxLyricPlateLines = 0x1E;

LyricPlate::LyricPlate(RndText *param1, const RndText *param2, const RndText *param3)
    : mWidthX(0), mNumCharsUsed(0), mText(param1), mSyllables(), mPreviewColor(),
      mActiveColor(), mNowColor(), mPastColor(), mPreviewPhonemeColor(),
      mActivePhonemeColor(), mNowPhonemeColor(), mPastPhonemeColor(), mPitchedStyle() {
    // param1->SetFixedLength(kMaxLyricPlateLines);
    param1->ReserveLines(kMaxLyricPlateLines);
}

void LyricPlate::SetShowing(bool) {}

Lyric::Lyric(const VocalNote *vocalNote, bool param2, String param3, bool param4)
    : mIdx(-1), mText(param3), mPitched(vocalNote->mUnpitchedNote), mLead(!param2),
      mWordEnd(param4), mChunkEnd(false), mDeployIdx(-1), mAfterMidPhraseShift(false),
      mXWidth(0), mHighlightMs(FLT_MAX), mInvalidateMs(FLT_MAX),
      mEndMs(vocalNote->mMs + vocalNote->mDurationMs), mPhraseEnd(false), mLastColor(0) {
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
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
    MILO_ASSERT(mText, 0x76);
    if (mNeedSync) {
        mText->SyncMeshes();
        mNeedSync = false;
    }
}

void LyricPlate::Reset() {
    mText->SetText("");
    mWidthX = 0;
    mNumCharsUsed = 0;
    mInvalidateMs = FLT_MAX;
    mBaked = false;
    mPastNow = false;
    for (int i = 0; i < mSyllables.size(); i++) {
        RELEASE(mSyllables[i]);
    }
    mSyllables.clear();
    SetShowing(false);
}

Lyric *LyricPlate::LatestLyric() {
    if (mSyllables.size() != 0) {
        return mSyllables[mSyllables.size() - 1];
    }
    return nullptr;
}

void LyricPlate::AddLyric(Lyric *lyric) {
    mSyllables.push_back(lyric);
    mInvalidateMs = std::max(mInvalidateMs, lyric->mEndMs + 100.0f);
}

void LyricPlate::EstimateLyricWidth(const Lyric *lyric) {
    mText->GetStringWidthUTF8(
        lyric->mText.c_str(), 0, false, lyric->mPitched ? &mPitchedStyle : &mUnpitchedStyle
    );
}

void LyricPlate::HookUpParents(RndGroup *group, RndTransformable *trans) {
    group->AddObject(mText);
    mText->SetTransParent(trans, false);
}

void LyricPlate::BakeLyric(Lyric *lyric) {
    if (mWidthX < 0.01f) {
        mText->SetLocalPos(lyric->unk48);
    }
    float f7 = lyric->unk48.x - mText->mLocalXfm.v.x;
    float fsub = lyric->unk48.z - mText->mLocalXfm.v.z;
    lyric->mXWidth = 0;
    Transform tf68;
    tf68.Reset();
    tf68.v.Set(f7, 0, fsub);
    lyric->mIdx = mText->AddLineUTF8(
        lyric->mText,
        tf68,
        lyric->mPitched ? mPitchedStyle : mUnpitchedStyle,
        &lyric->mXWidth,
        &mNeedSync,
        -1
    );
    if (lyric->mIdx == -1) {
        MILO_WARN("Unable to add line for lyric %s", lyric->mText);
    }
    if (mText->NumLines() > kMaxLyricPlateLines) {
        MILO_WARN(
            "Lyric count %d exceeds max per plate %d; please alert Track/HUD coder",
            mText->NumLines(),
            kMaxLyricPlateLines
        );
    }
    mWidthX = std::max(mWidthX, f7 + lyric->mXWidth);
}

bool LyricPlate::Empty() const { return mSyllables.empty(); }

void LyricPlate::UpdateStaticTiming(float time) {
    MILO_ASSERT(mSyllables.size(), 0xcf);

    float f1 = 0;
    for (int i = 0; i < mSyllables.size(); i++) {
        Lyric *curLyric = mSyllables[i];
        if (i == 0 || curLyric->mDeployIdx != -1) {
            f1 = curLyric->mActiveMs - time;
        } else if (curLyric->mAfterMidPhraseShift) {
            f1 = curLyric->mActiveMs;
        }
        curLyric->mHighlightMs = f1;
    }

    float f2 = mInvalidateMs;
    for (int i = mSyllables.size() - 1; i >= 0; i--) {
        Lyric *curLyric = mSyllables[i];
        if (curLyric->GetChunkEnd()) {
            f2 = std::min(curLyric->mEndMs + 100.0f, curLyric->mInvalidateMs);
        }
        curLyric->mInvalidateMs = f2;
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
    float f24 = 0;
    for (int i = 0; i < mSyllables.size(); i++) {
        Lyric *curLyric = mSyllables[i];
        if (curLyric->mActiveMs > ms)
            break;
        MaxEq(f24, curLyric->unk48.x + curLyric->mXWidth);
    }
    return f24;
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

float Lyric::EndPos() const { return mXWidth + unk48.x; }

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
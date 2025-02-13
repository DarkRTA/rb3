#include "game/CrowdRating.h"
#include "bandobj/CrowdAudio.h"
#include "bandobj/CrowdMeterIcon.h"
#include "decomp.h"
#include "game/Scoring.h"
#include "math/Utl.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "os/Debug.h"

CrowdRating::CrowdRating(BandUser *user, Difficulty diff) : mRunningMin(1) {
    Configure(user, diff);
    Reset();
}

void CrowdRating::Configure(BandUser *user, Difficulty diff) {
    DataArray *cfg = TheScoring->GetCrowdConfig(diff, user);
    mLoseLevel = cfg->FindFloat("lose_level");
    kMin = cfg->FindArray("range", true)->Float(1);
    kMax = cfg->FindArray("range", true)->Float(2);
    kNoteWeight = cfg->FindFloat("note_weight");
    kGreatLevel = cfg->FindFloat("great_level");
    kOkayLevel = cfg->FindFloat("okay_level");
    kBadLevel = cfg->FindFloat("bad_level");
    kWarningLevel = cfg->FindFloat("warning_level");
    kFreeRide = cfg->FindFloat("free_ride");
    kPhraseWeight = cfg->FindFloat("phrase_weight");
    kInitialDisplayLevel = cfg->FindFloat("initial_display_level");
    MILO_ASSERT_RANGE_EQ(kNoteWeight, 0, 1, 0x29);
    MILO_ASSERT_RANGE_EQ(kGreatLevel, 0, 1, 0x2A);
    MILO_ASSERT_RANGE_EQ(kOkayLevel, 0, 1, 0x2B);
    MILO_ASSERT_RANGE_EQ(kBadLevel, 0, 1, 0x2C);
    MILO_ASSERT_RANGE_EQ(kWarningLevel, 0, 1, 0x2D);
    MILO_ASSERT_RANGE_EQ(kPhraseWeight, 0, 1, 0x2E);
    MILO_ASSERT_RANGE_EQ(mLoseLevel, 0, 1, 0x2F);
    MILO_ASSERT_RANGE(kMin, 0, 1, 0x30);
    MILO_ASSERT_RANGE_EQ(kMax, 0, 1, 0x31);
}

void CrowdRating::ChangeDifficulty(BandUser *user, Difficulty diff) {
    Configure(user, diff);
    SetValue(mValue);
}

void CrowdRating::Reset() {
    mActive = true;
    SetDisplayValue(kInitialDisplayLevel);
    mSongFraction = 0;
    mRunningMin = 1;
}

void CrowdRating::Poll(float f) { mSongFraction = f; }
void CrowdRating::SetActive(bool active) { mActive = active; }

void CrowdRating::Update(float noteScore, float f2) {
    MetaPerformer::Current();
    MILO_ASSERT(noteScore >= 0 && noteScore <= 1, 0x53);
    float noteWeight = kNoteWeight * f2;
    mRawValue = (1.0f - noteWeight) * mRawValue + noteWeight * noteScore;
    ClampEq<float>(mRawValue, 0, 1);
    CalculateValue();
}

void CrowdRating::UpdatePhrase(float phraseHit, float f2) {
    MetaPerformer::Current();
    MILO_ASSERT_RANGE_EQ(phraseHit, 0, 1, 0x61);
    float phraseWeight = kPhraseWeight * f2;
    mRawValue = (1.0f - phraseWeight) * mRawValue + phraseWeight * phraseHit;
    ClampEq<float>(mRawValue, 0, 1);
    CalculateValue();
}

float CrowdRating::GetThreshold(ExcitementLevel e) const {
    switch (e) {
    case kExcitementBoot:
        return kWarningLevel;
    case kExcitementBad:
        return kBadLevel;
    case kExcitementOkay:
        return kOkayLevel;
    case kExcitementGreat:
        return kGreatLevel;
    case kExcitementPeak:
        return 1;
    default:
        return 1;
    }
}

ExcitementLevel CrowdRating::GetExcitement() const {
    float f3 = (mValue - mLoseLevel) / (1.0f - mLoseLevel);
    if (f3 < GetThreshold(kExcitementBoot))
        return kExcitementBoot;
    else if (f3 < GetThreshold(kExcitementBad))
        return kExcitementBad;
    else if (f3 < GetThreshold(kExcitementOkay))
        return kExcitementOkay;
    else if (f3 < GetThreshold(kExcitementGreat))
        return kExcitementGreat;
    else
        return kExcitementPeak;
}

void CrowdRating::CalculateValue() {
    if (mActive) {
        float val = mRawValue >= kMax ? 1.0f : (mRawValue - kMin) / (kMax - kMin);
        if (CantFailYet() && val < kWarningLevel) {
            val = kWarningLevel;
        }
        SetValue(val);
    }
}

bool CrowdRating::IsInWarning() const { return mValue < kWarningLevel; }
bool CrowdRating::IsBelowLoseLevel() const { return mValue < mLoseLevel; }

void CrowdRating::SetValue(float val) {
    mValue = val;
    if (mRunningMin > mValue)
        mRunningMin = mValue;
    mRawValue = (kMax - kMin) * mValue + kMin;
}

void CrowdRating::SetDisplayValue(float val) {
    SetValue(val * (1.0f - mLoseLevel) + mLoseLevel);
}

float CrowdRating::GetDisplayValue() const {
    return (mValue - mLoseLevel) / (1.0f - mLoseLevel);
}

FORCE_LOCAL_INLINE
bool CrowdRating::CantFailYet() const {
    return mSongFraction <= kFreeRide ? true : false;
}
END_FORCE_LOCAL_INLINE
#include "synth/VoiceBeat.h"

VoiceBeat::VoiceBeat() {
    mEnabled = true;
    Reset();
}

void VoiceBeat::SetEnable(bool enable) {
    if (enable && !mEnabled)
        Reset();
    mEnabled = enable;
}

void VoiceBeat::Analyze(float *, int, bool, bool, float) {}

void VoiceBeat::Reset() {
    memset(mXVVoice, 0, sizeof(mXVVoice));
    memset(mYVVoice, 0, sizeof(mYVVoice));
    memset(mXVEnvAntiAlias, 0, sizeof(mXVEnvAntiAlias));
    memset(mYVEnvAntiAlias, 0, sizeof(mYVEnvAntiAlias));
    memset(mXVSyllables, 0, sizeof(mXVSyllables));
    memset(mYVSyllables, 0, sizeof(mYVSyllables));
    memset(mXVSpamSyllables, 0, sizeof(mXVSpamSyllables));
    memset(mYVSpamSyllables, 0, sizeof(mYVSpamSyllables));
    unk0 = false;
    unk1 = false;
    unk4 = 0;
    mSpamAvg = 0;
    mSylDeltaPrev = 0;
    mSylEnvSigma = 0;
    mFloorSigma = 0;
    mCount = 0;
    mRate = 1;
    mPeaks.clear();
    mTimes.clear();
    mTriggered = false;
}

void VoiceBeat::ClearTrigger() { mTriggered = false; }

void VoiceBeat::ClearEventList() {
    mPeaks.clear();
    mTimes.clear();
}

EventTracker::EventTracker() : mSelFrom(-1), mSelTo(-1), mAvgHitTime(0) {}

TalkyMatcher::TalkyMatcher() { memset(mBuffer, 0, sizeof(mBuffer)); }

void TalkyMatcher::updateScoring(float f) {
    if (mVoiceBeat.mTriggered) {
        mRefEvents.Hit(f - 180.0f, f + 180.0f, f);
        mVoiceBeat.ClearEventList();
    }
    mRefEvents.Miss(f - 120.0f, f - 60.0f);
    mVoiceBeat.ClearTrigger();
}

void TalkyMatcher::LoadEvents(
    const std::vector<float> &times, const std::vector<float> &peaks
) {
    mRefEvents.mTimes = times;
    mRefEvents.mPeaks = peaks;
    mRefEvents.Reset();
}

void TalkyMatcher::Reset() { mVoiceBeat.Reset(); }

void TalkyMatcher::SetEnableTalkyMatcher(bool enable) { mVoiceBeat.SetEnable(enable); }
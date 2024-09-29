#include "EnvelopeWii.h"

EnvelopeWii::EnvelopeWii() {
    mAttackDuration = 5.0f;
    mReleaseDuration = 5.0f;
    mInRelease = false;
    mIsPaused = false;
    mReleaseStart = 0.0f;
}

float EnvelopeWii::GetValueAtOffset(float timeOffset) {
    MILO_ASSERT(!(timeOffset < 0.0f), 0x44);

    if (0 <= mTimer.mRunning) {
        mTimer.Split();
    }

    float elapsedTimeMs = timeOffset + mTimer.CyclesToMs(mTimer.mCycles);

    if (mInRelease) {
        if (elapsedTimeMs < mReleaseDuration) {
            float t = elapsedTimeMs / mReleaseDuration;
            return mReleaseStart * (1.0f - t);
        } else {
            return 0.0f;
        }
    } else {
        if (elapsedTimeMs < mAttackDuration) {
            return elapsedTimeMs / mAttackDuration;
        } else {
            return 1.0f;
        }
    }
}

bool EnvelopeWii::IsDone() {
    if (mInRelease != false) {
        if (0 < mTimer.mRunning) {
            mTimer.Split();
        }
        float elapsedTimeMs = mTimer.CyclesToMs(mTimer.mCycles);
        if (elapsedTimeMs > mReleaseDuration) {
            return true;
        }
    }
    return false;
}

void EnvelopeWii::Pause() {
    if (0 <= mTimer.mRunning) {
        mTimer.Pause();
    }
    mIsPaused = true;
}

void EnvelopeWii::Resume() {
    if (mTimer.mRunning < 0) {
        mTimer.Resume();
    }
    mIsPaused = false;
}

void EnvelopeWii::StartAttack() {
    mInRelease = false;
    mTimer.Restart();
}

void EnvelopeWii::StartRelease() {
    float value = GetValueAtOffset(0.0f);
    mReleaseStart = value;
    mInRelease = true;
    mTimer.Restart();
}

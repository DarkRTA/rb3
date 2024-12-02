#include "game/CrowdRating.h"

CrowdRating::CrowdRating(BandUser *user, Difficulty diff) : mRunningMin(1) {
    Configure(user, diff);
    Reset();
}

void CrowdRating::ChangeDifficulty(BandUser *user, Difficulty diff) {
    Configure(user, diff);
    SetValue(mValue);
}

void CrowdRating::Reset() {
    mActive = true;
    SetDisplayValue(unk2c);
    mSongFraction = 0;
    mRunningMin = 1;
}

void CrowdRating::SetActive(bool active) { mActive = active; }
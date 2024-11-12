#include "game/CrowdRating.h"

CrowdRating::CrowdRating(BandUser *user, Difficulty diff) : unk10(1) {
    Configure(user, diff);
    Reset();
}

void CrowdRating::ChangeDifficulty(BandUser *user, Difficulty diff) {
    Configure(user, diff);
    SetValue(unkc);
}

void CrowdRating::Reset() {
    mActive = true;
    SetDisplayValue(unk2c);
    unk14 = 0;
    unk10 = 1;
}

void CrowdRating::SetActive(bool active) { mActive = active; }
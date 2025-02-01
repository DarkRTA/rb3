#include "game/HitTracker.h"
#include "beatmatch/HitSink.h"
#include "os/Debug.h"
#include <algorithm>

const char *sHitTypeNames[] = { "Green pad",       "Red pad",          "Yellow pad",
                                "Blue pad",        "Green fret",       "Red fret",
                                "Yellow fret",     "Blue fret",        "Orange fret",
                                "High Green fret", "High Red fret",    "High Yellow fret",
                                "High Blue fret",  "High Orange fret", "Kick",
                                "Yellow Cymbal",   "Blue Cymbal",      "Green Cymbal",
                                "Upstrum",         "Downstrum",        "Start",
                                "Select" };

HitTracker::HitTracker() {
    mHits.reserve(kNumHitTypes);
    mHits.resize(kNumHitTypes);
    Reset();
}

void HitTracker::Reset() {
    std::fill(mHits.begin(), mHits.end(), 0);
    for (int i = 0; i < 128; i++)
        mKeys[i] = 0;
    for (int i = 0; i < 6; i++) {
        mRGStrums[i] = 0;
        for (int j = 0; j < 20; j++) {
            mRGFrets[i][j] = 0;
        }
    }
}

void HitTracker::Hit(HitType ty) { mHits[ty]++; }

void HitTracker::Key(int key) { mKeys[key]++; }

void HitTracker::RGFret(int str, int fret) { mRGFrets[str][fret]++; }

void HitTracker::RGStrum(int str) { mRGStrums[str]++; }

void HitTracker::PrintStats() const {
    for (int i = 0; i < kNumHitTypes; i++) {
        if (mHits[i] != 0) {
            MILO_LOG("%20s: %6d\n", sHitTypeNames[i], mHits[i]);
        }
    }
    for (int i = 0; i < 128U; i++) {
        if (mKeys[i] != 0) {
            MILO_LOG("             Key %3d: %6d\n", i, mKeys[i]);
        }
    }
    for (int i = 0; i < 6; i++) {
        if (mRGStrums[i] != 0) {
            MILO_LOG("     Guitar string %d: %6d\n", i, mRGStrums[i]);
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 20; j++) {
            if (mRGFrets[i][j] != 0) {
                MILO_LOG("Guitar string %d fret %2d: %6d\n", i, j, mRGFrets[i][j]);
            }
        }
    }
}
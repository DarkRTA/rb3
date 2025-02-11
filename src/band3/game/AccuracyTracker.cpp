#include "game/AccuracyTracker.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

AccuracyTracker::AccuracyTracker(
    TrackerSource *src, TrackerBandDisplay &banddisp, TrackerBroadcastDisplay &bcdisp
)
    : Tracker(src, banddisp, bcdisp), mCurrentAccuracy(-1.0f) {}

AccuracyTracker::~AccuracyTracker() {}

void AccuracyTracker::FirstFrame_(float) { mBandDisplay.Initialize(mDesc.mName); }

void AccuracyTracker::Poll_(float) {
    if (!mSource->IsFinished()) {
        MILO_ASSERT(mTargets.front() > 0.0f, 0x33);
        float f6 = 0;
        int i2 = 0;
        for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
             id = mSource->GetNextPlayer(id)) {
            Player *p = mSource->GetPlayer(id);
            bool b68 = false;
            float f5 = p->GetNotesHitFraction(&b68);
            if (b68) {
                f6 += f5;
                i2++;
            }
        }
        float f1 = -2.0f;
        if (i2 > 0) {
            f1 = f6 / (float)i2;
        }
        if (f1 != mCurrentAccuracy) {
            ReachedAnyTarget();
            mCurrentAccuracy = f1;
            ReachedAnyTarget();
            if (mCurrentAccuracy == -2.0f) {
                mBandDisplay.SetPercentageProgress(TrackerDisplay::kMissingPercentage);
            } else {
                mBandDisplay.SetPercentageProgress(mCurrentAccuracy);
            }
        }
    }
}

DataArrayPtr AccuracyTracker::GetTargetDescription(int idx) const {
    return TrackerDisplay::MakePercentTargetDescription(mTargets[idx]);
}

void AccuracyTracker::UpdateGoalValueLabel(UILabel &label) const {
    label.SetTokenFmt(tour_goal_accuracy_goal_format, (int)(mTargets.front() * 100.0f));
}

void AccuracyTracker::UpdateCurrentValueLabel(UILabel &label) const {
    label.SetTokenFmt(tour_goal_accuracy_result_format, (int)(mCurrentAccuracy * 100.0f));
}

String AccuracyTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    int i4 = 0;
    if (pid.NotNull()) {
        Player *pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x89);
        i4 = pPlayer->mStats.unk1c0;
    }
    const char *str = i4 >= 0 ? "+" : "";
    return MakeString(Localize(tour_goal_accuracy_player_contribution_format, 0), str, i4);
}

void AccuracyTracker::SavePlayerStats() const {
    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        Player *pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x9D);
        float first = mTargets.front() * 100.0f;
        float floored = std::floor(pPlayer->GetNotesHitFraction(0) * 100.0f);
        pPlayer->mStats.unk1c0 = floored - first;
    }
}
#include "game/OverdriveTimeTracker.h"
#include "game/Game.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "os/Debug.h"
#include "ui/UILabel.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

OverdriveTimeTracker::OverdriveTimeTracker(
    TrackerSource *src, TrackerBandDisplay &banddisp, TrackerBroadcastDisplay &bcdisp
)
    : Tracker(src, banddisp, bcdisp), unk58(0), unk5c(0), unk60(0), unk64(-1.0f),
      unk68(1), unk6c(0) {}

OverdriveTimeTracker::~OverdriveTimeTracker() {}

void OverdriveTimeTracker::FirstFrame_(float) {
    unk58 = 0;
    unk5c = 0;
    unk60 = 0;
    unk64 = -1.0f;
    unk68 = 1;
    unk6c = false;
    mBandDisplay.Initialize(mDesc.mName);
    UpdateTimeRemainingDisplay();
}

void OverdriveTimeTracker::Poll_(float f) {
    MILO_ASSERT(TheGame, 0x3E);
    if (TheGame->unk_0xdc != -1 || mSource->IsFinished())
        return;
    else {
        bool o2 = false;
        for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
             id = mSource->GetNextPlayer(id)) {
            Player *player = mSource->GetPlayer(id);
            MILO_ASSERT(player, 0x48);
            if (player->IsDeployingBandEnergy()) {
                o2 = true;
                break;
            }
        }
        if (o2) {
            if (unk64 == -1.0f) {
                unk64 = f;
            } else {
                unk5c = f - unk64;
                if (unk60 < unk5c) {
                    unk60 = unk5c;
                }
            }
            UpdateTimeRemainingDisplay();
        } else if (unk64 != -1.0f) {
            unk58 += unk5c;
            if (unk60 < unk5c) {
                unk60 = unk5c;
            }
            unk5c = 0;
            unk64 = -1.0f;
        }
        unk6c = o2;
    }
}

void OverdriveTimeTracker::UpdateGoalValueLabel(UILabel &label) const {
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(mTargets.front(), min, sec);
    label.SetTokenFmt(tour_goal_od_timer_goal_format, min, sec);
}

void OverdriveTimeTracker::UpdateCurrentValueLabel(UILabel &label) const {
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(unk60, min, sec);
    label.SetTokenFmt(tour_goal_od_timer_result_format, min, sec);
}

String OverdriveTimeTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    float f1 = 0;
    if (pid.NotNull()) {
        Player *pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x8E);
        f1 = pPlayer->mStats.unk1c0;
    }
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(f1, min, sec);
    return MakeString(Localize(tour_goal_od_timer_result_format, 0), min, sec);
}

void OverdriveTimeTracker::SavePlayerStats() const {
    for (TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull();
         id = mSource->GetNextPlayer(id)) {
        Player *pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0xA6);
        pPlayer->mStats.unk1c0 = pPlayer->mStats.mTotalOverdriveDurationMs;
    }
}

void OverdriveTimeTracker::UpdateTimeRemainingDisplay() {
    float f60 = unk60;
    int floored = std::floor(f60 / 1000.0f);
    if (floored != unk68) {
        unk68 = floored;
        mBandDisplay.SetTimeProgress(f60);
    }
}
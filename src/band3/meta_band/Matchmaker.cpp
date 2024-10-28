#include "meta_band/Matchmaker.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/System.h"

MatchmakerPoolStats::MatchmakerPoolStats(){
    DataArray* cfg = SystemConfig("net", "matchmaker", "pool_min_thresholds");
    for(int i = 0; i < 3; i++){
        mRatingThresholds[i] = cfg->Int(i + 1);
    }
    ClearStats();
}

Matchmaker::Matchmaker() : unk1c(0), unk20(0) {
    SetName("matchmaker", ObjectDir::Main());
    mQuickFindingMode = new QuickFinding();
    mBandFindingMode = new BandFinding();
    mPoolStats = new MatchmakerPoolStats();
}
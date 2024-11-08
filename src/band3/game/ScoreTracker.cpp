#include "game/ScoreTracker.h"
#include "obj/Data.h"
#include "os/Debug.h"

ScoreTracker::ScoreTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp) {

}

ScoreTracker::~ScoreTracker(){

}

void ScoreTracker::FirstFrame_(float){
    mBandDisplay.Initialize(mDesc.mName);
    mBandDisplay.SetIntegerProgress(mTargets.front());
    unk58 = 0;
}

void ScoreTracker::Poll_(float){
    unk58 = 0;
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* p = mSource->GetPlayer(id);
        unk58 += p->GetScore();
    }
}

DataArrayPtr ScoreTracker::GetTargetDescription(int) const { return DataArrayPtr(); }

void ScoreTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x49);
        pPlayer->mStats.unk1c0 = unk58;
    }
}
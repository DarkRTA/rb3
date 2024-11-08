#include "game/StatMemberTracker.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "obj/Data.h"
#include "utl/Locale.h"

StatMemberTracker::StatMemberTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp), unk58(-2.0f) {

}

StatMemberTracker::~StatMemberTracker(){

}

void StatMemberTracker::FirstFrame_(float){
    mBandDisplay.Initialize(mDesc.mName);
    unk58 = -2.0f;
    if(IsPercentageStat()){
        mBandDisplay.SetPercentageProgress(0);
    }
    else {
        mBandDisplay.SetIntegerProgress(0);
    }
}

void StatMemberTracker::Poll_(float f){
    if(!mSource->IsFinished()){
        float f = unk44 + CalcCurrentStat();
        if(f != unk58){
            if(IsPercentageStat()){
                mBandDisplay.SetPercentageProgress(f * 0.01f);
            }
            else {
                mBandDisplay.SetIntegerProgress(f);
            }
            unk58 = f;
        }
    }
}

float StatMemberTracker::CalcCurrentStat() const {
    float ret;
    if(IsBandWideCummulative()){
        ret = 0;
        for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
            Player* p = mSource->GetPlayer(id);
            ret += GetStatValue(p->mStats);
        }
    }
    else {
        TrackerPlayerID pid = mSource->GetFirstPlayer();
        Player* p = mSource->GetPlayer(pid);
        ret = GetStatValue(p->mStats);
    }
    return ret;
}

void StatMemberTracker::UpdateGoalValueLabel(UILabel& label) const {
    int val = mTargets.front();
    label.SetTokenFmt(DataArrayPtr(GetGoalValueSymbol(), val));
}

void StatMemberTracker::UpdateCurrentValueLabel(UILabel& label) const {
    int val = CalcCurrentStat();
    label.SetTokenFmt(DataArrayPtr(GetCurrentValueSymbol(), val));
}

void StatMemberTracker::SavePlayerStats() const {}

DataArrayPtr StatMemberTracker::GetTargetDescription(int idx) const {
    return TrackerDisplay::MakeIntegerTargetDescription(mTargets[idx]);
}

String StatMemberTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    if(pid.NotNull()){
        Player* player = mSource->GetPlayer(pid);
        float val = GetStatValue(player->mStats);
        Symbol loc = (int)val == 1 ? GetSingularContributionSymbol() : GetContributionSymbol();
        return MakeString(Localize(loc, 0), val);
    }
    else return "";
}

Symbol StatMemberTracker::GetSingularContributionSymbol() const { return GetContributionSymbol(); }
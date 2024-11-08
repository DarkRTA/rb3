#include "game/StreakTracker.h"
#include "beatmatch/TrackType.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "game/TrackerUtils.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

StreakTracker::StreakTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp),
    unk58(0), unk5c(0) {

}

StreakTracker::~StreakTracker(){

}

void StreakTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    unk7c.InitFromDataArray(arr->FindArray(chain_multipliers, false));
    arr->FindData(streak_length_multiplier, unk60, true);
}

void StreakTracker::TranslateRelativeTargets(){
    mStreakDataMap.clear();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x3A);
        int count;
        if(pPlayer->GetTrackType() == kTrackVocals){
            count = TrackerUtils::CountVocalPhrasesInSong(pPlayer->GetTrackNum());
        }
        else {
            count = TrackerUtils::CountGemsInSong(pPlayer->GetTrackNum(), pPlayer->GetTrackType());
        }
        int val = (float)count * unk60;
        // val = Min(val, 1);
        MinEq(val, 1);
        PlayerStreakData data;
        data.unk0 = val;
        mStreakDataMap[id] = data;    
    }

    for(int i = 0; i < mTargets.size(); i++){
        mTargets[i] = std::floor((1.0f / unk60) * (mTargets[i]));
    }
}

void StreakTracker::HandlePlayerSaved_(const TrackerPlayerID& pid){
    const TrackerPlayerDisplay& disp = GetPlayerDisplay(pid);
    PlayerStreakData& data = mStreakDataMap[pid];
    data.unk4 = 0;
    data.unk8 = 0;
    data.unkc = 0;
    data.unk18 = 0;
    disp.GainFocus(false);
}

void StreakTracker::FirstFrame_(float){
    unk58 = 0;
    unk5c = 0;
    mBandDisplay.Initialize(mDesc.mName);
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        const TrackerPlayerDisplay& disp = GetPlayerDisplay(id);
        PlayerStreakData& data = mStreakDataMap[id];
        data.unk4 = 0;
        data.unk8 = 0;
        data.unkc = 0;
        data.unk18 = 0;
        disp.GainFocus(true);
    }
}

void StreakTracker::Poll_(float){

}

void StreakTracker::RemoteEndStreak_(Player* p, float f, int){
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if(pid.NotNull()){
        LocalEndStreak(pid, f);
    }
}

void StreakTracker::LocalEndStreak(const TrackerPlayerID& pid, float f){
    unk5c++;
    unk58 += f;
    GetPlayerDisplay(pid).Pulse(true);
    Symbol sym = unk5c == 1 ? streak_tracker_progress_1 : streak_tracker_progress;
    mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(sym, unk5c));
}

void StreakTracker::UpdateGoalValueLabel(UILabel& label) const {
    int ceiled = std::ceil(mTargets.front() / 1000.0f);
    label.SetTokenFmt(tour_goal_band_streak_goal_format, ceiled / 60, ceiled % 60);
}

void StreakTracker::UpdateCurrentValueLabel(UILabel& label) const {}

String StreakTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    int i4 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 299);
        i4 = pPlayer->mStats.unk1c0;
    }
    Symbol sym = i4 == 1 ? tour_goal_band_streak_player_contribution_format_1 : tour_goal_band_streak_player_contribution_format;
    return MakeString(Localize(sym, 0), i4);
}

void StreakTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x141);
        std::map<TrackerPlayerID, PlayerStreakData>::const_iterator cData = mStreakDataMap.find(id);
        MILO_ASSERT(cData != mStreakDataMap.end(), 0x146);
        pPlayer->mStats.unk1c0 = cData->second.unk1c;
    }
}

void StreakTracker::TargetSuccess(int) const {}

DataArrayPtr StreakTracker::GetBroadcastDescription() const {
    return DataArrayPtr(streak_tracker_explanation);
}

DataArrayPtr StreakTracker::GetTargetDescription(int idx) const {
    return TrackerDisplay::MakeTimeTargetDescription(mTargets[idx]);
}
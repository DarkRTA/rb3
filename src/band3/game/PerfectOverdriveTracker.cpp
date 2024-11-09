#include "game/PerfectOverdriveTracker.h"
#include "beatmatch/TrackType.h"
#include "game/TrackerSource.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

PerfectOverdriveTracker::PerfectOverdriveTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp) {

}

PerfectOverdriveTracker::~PerfectOverdriveTracker(){

}

void PerfectOverdriveTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    unk8c.InitFromDataArray(arr->FindArray(chain_multipliers, false));
}

void PerfectOverdriveTracker::TranslateRelativeTargets(){
    DataArray* cfg = SystemConfig("scoring", "band_energy");
}

void PerfectOverdriveTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0xBE);
        std::map<TrackType, PlayerStreakData>::const_iterator it = unk70.find(pPlayer->GetTrackType());
        if(it != unk70.end()){
            pPlayer->mStats.unk1c0 = it->second.unk1c;
        }
    }
}

void PerfectOverdriveTracker::HandlePlayerSaved_(const TrackerPlayerID& pid){
    GetPlayerDisplay(pid).Enable();
}

void PerfectOverdriveTracker::FirstFrame_(float){
    mBandDisplay.Initialize(gNullStr);
    unk70.clear();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* player = mSource->GetPlayer(id);
        MILO_ASSERT(player, 0xF1);
        PlayerStreakData& data = unk70[player->GetTrackType()];
        data.unk0 = -1.0f;
        data.unk4 = 0;
        data.unk5 = 0;
        data.unk6 = 0;
        data.unk8 = 0;
        data.unkc = 0;
        data.unk10 = 0;
        data.unk14 = -1;
        data.unk18 = -1.0f;
        data.unk1c = 0;
        GetPlayerDisplay(id).Enable();
    }
    unk88 = 0;
}

void PerfectOverdriveTracker::Poll_(float){
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        
    }
}

void PerfectOverdriveTracker::RemoteEndStreak_(Player* p, float f, int i){
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if(pid.NotNull()){
        LocalEndStreak(pid, f, i);
    }
}

void PerfectOverdriveTracker::LocalEndStreak(const TrackerPlayerID& pid, float f, int i){
    unk88 += f;
    GetPlayerDisplay(pid).LoseFocus(true);
    Player* player = mSource->GetPlayer(pid);
    Symbol sym = player->GetTrackType() == kTrackVocals ? perfect_overdrive_tracker_vocal_progress : perfect_overdrive_tracker_gem_progress;
    const char* fontchar = GetFontCharFromTrackType(player->GetTrackType(), 0);
    mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(sym, i, fontchar));
}

void PerfectOverdriveTracker::UpdateGoalValueLabel(UILabel&) const {}
void PerfectOverdriveTracker::UpdateCurrentValueLabel(UILabel&) const {}

String PerfectOverdriveTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    int i4 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x1EE);
        i4 = pPlayer->mStats.unk1c0;
    }
    if(s == vocals){
        Symbol sym = i4 == 1 ? perfect_overdrive_tracker_contrib_format_vox_1 : perfect_overdrive_tracker_contrib_format_vox;
        return MakeString(Localize(sym, 0), i4);
    }
    else {
        Symbol sym = i4 == 1 ? perfect_overdrive_tracker_contribution_format_1 : perfect_overdrive_tracker_contribution_format;
        return MakeString(Localize(sym, 0), i4);
    }
}
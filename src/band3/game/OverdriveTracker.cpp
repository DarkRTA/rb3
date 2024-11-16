#include "game/OverdriveTracker.h"
#include "game/Game.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "game/TrackerDisplay.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

OverdriveTracker::OverdriveTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp), unkb0(0) {

}

OverdriveTracker::~OverdriveTracker(){

}

void OverdriveTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    unk70.InitFromDataArray(arr->FindArray(chain_multipliers, false));
}

void OverdriveTracker::TranslateRelativeTargets(){
    int i8 = 0;
    int phrasecount = TheSongDB->NumCommonPhrases();
    for(int i = 0; i < phrasecount; i++){
        i8 += CountBits(TheSongDB->GetCommonPhraseTracks(i));
    }
    int playercount = mSource->GetPlayerCount();
    int u9;
    if(playercount == 0){
        u9 = 0;
    }
    else {
        u9 = i8 / playercount;
    }
    float mult = unk70.GetMultiplier(playercount);
    DataArray* cfg = SystemConfig("scoring", "band_energy");
    float deploybeats = cfg->FindFloat("deploy_beats");
    cfg->FindFloat("spotlight_phrase");

    unk8c = deploybeats;
    for(int i = 0; i < mTargets.size(); i++){
        mTargets[i] *= mult * ((float)playercount * (float)i8 * deploybeats);
    }
}

void OverdriveTracker::FirstFrame_(float){
    unkb0 = false;
    unk90 = -1.0f;
    unk94 = -1.0f;
    unk98 = 0;
    unk9c = 0;
    unka0 = 0;
    unka4 = 1.0f;
    unka8 = -1;
    unkac = 0;
    mBandDisplay.Initialize(overdrive_tracker_description);
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        DeployData data;
        unk58[id] = data;
    }
    mBroadcastDisplay.SetType((TrackerBroadcastDisplay::BroadcastDisplayType)1);
    mBroadcastDisplay.SetSecondaryStateLevel(0);
    mBroadcastDisplay.Hide();
    UpdateTimeRemainingDisplay();
}

void OverdriveTracker::Poll_(float ms){
    MILO_ASSERT(TheGame, 0x81);
    if(mSource->IsFinished()){
        float f98 = unk98;
        if(f98 > 0){
            unk98 = 0;
            unka0 = f98 * unka4 + unka0;
        }
    }
    else {
        bool b4 = false;
        Player* pLocalPlayer = nullptr;
        bool t5 = false;
        for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
            Player* player = mSource->GetPlayer(id);
            MILO_ASSERT(player, 0x9E);
            const TrackerPlayerDisplay& disp = GetPlayerDisplay(id);
            bool candeploy = player->CanDeployOverdrive();
            bool c1 = unk58[id].unk0;
            bool isdeploying = player->IsDeployingBandEnergy();
            DeployData& data = unk58[id];
            bool d1 = data.unk1;
            if(isdeploying){
                if(c1){
                    disp.LoseFocus(true);
                }
                t5 = true;
            }
            else if(candeploy && !c1){
                disp.GainFocus(false);
            }
            else if(d1 && player->IsLocal()){
                b4 = true;
                pLocalPlayer = player;
            }
            unk58[id].unk0 = candeploy;
            unk58[id].unk1 = isdeploying;
        }
        float beat = MsToBeat(ms);
        if(t5){
            if(unk90 == -1.0f){
                unk90 = beat;
                unk94 = ms;
                unk98 = 0;
            }
            else {
                unk98 = beat - unk90;
                unk9c = ms - unk94;
            }
        }
        if(unk98 > 0){
            int multidx = unk70.GetMultiplierIndex(unk98 / unk8c);
            if(multidx != unka8){
                mBroadcastDisplay.SetSecondaryStateLevel(multidx);
                unka8 = multidx;
            }
        }
        if(!t5 && unkb0){
            if(b4){
                MILO_ASSERT(pLocalPlayer, 0xE9);
                float prod = unk98 * unka4;
                LocalEndDeployStreak(prod);
                static Message endStreakMsg("send_tracker_end_deploy_streak", 0.0f);
                endStreakMsg[0] = (int)(prod * 10000.0f);
                pLocalPlayer->HandleType(endStreakMsg);
            }
        }
        else if(t5 && !unkb0){
            mBroadcastDisplay.Show();
        }
        UpdateTimeRemainingDisplay();
        unkb0 = t5;
    }
}

void OverdriveTracker::RemoteEndDeployStreak(Player*, int i){
    LocalEndDeployStreak((float)i / 10000.0f);
}

void OverdriveTracker::LocalEndDeployStreak(float f){
    unka0 += f;
    unk98 = 0;
    unk90 = -1.0f;
    unka4 = 1.0f;
    mBroadcastDisplay.SetSecondaryStateLevel(0);
    unka8 = 0;
    mBroadcastDisplay.Hide();
}

void OverdriveTracker::UpdateGoalValueLabel(UILabel& label) const {
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(mTargets.front(), min, sec);
    label.SetTokenFmt(tour_goal_od_timer_goal_format, min, sec);
}

void OverdriveTracker::UpdateCurrentValueLabel(UILabel& label) const {
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(0.0f, min, sec);
    label.SetTokenFmt(tour_goal_od_timer_result_format, min, sec);
}

String OverdriveTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    float f1 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x13F);
        f1 = pPlayer->mStats.unk1c0;
    }
    int min, sec;
    TrackerDisplay::MsToMinutesSeconds(f1, min, sec);
    return MakeString(Localize(tour_goal_od_timer_result_format, 0), min, sec);
}

void OverdriveTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x157);
        pPlayer->mStats.unk1c0 = pPlayer->mStats.mTotalOverdriveDurationMs;
    }
}

void OverdriveTracker::TargetSuccess(int) const {}

DataArrayPtr OverdriveTracker::GetBroadcastDescription() const {
    return DataArrayPtr(overdrive_tracker_explanation);
}

void OverdriveTracker::UpdateTimeRemainingDisplay(){
    if(unk9c != unkac){
        int min, sec;
        TrackerDisplay::MsToMinutesSeconds(unk9c, min, sec);
        mBroadcastDisplay.SetBandMessage(DataArrayPtr(overdrive_deploy_tracker_progress, min, sec));
        unkac = unk9c;
    }
}
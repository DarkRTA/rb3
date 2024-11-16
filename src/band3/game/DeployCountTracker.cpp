#include "game/DeployCountTracker.h"
#include "game/SongDB.h"
#include "game/TrackerSource.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Locale.h"
#include "utl/Messages3.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

DeployCountTracker::DeployCountTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp),
    mDeployCount(0), mRequireFullEnergy(0), mRequireMaxMultiplier(0) {

}

DeployCountTracker::~DeployCountTracker(){

}

void DeployCountTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    arr->FindData(require_full_energy, mRequireFullEnergy, false);
    arr->FindData(require_max_multiplier, mRequireMaxMultiplier, false);
}

void DeployCountTracker::TranslateRelativeTargets(){
    int bitcount = 0;
    int phrasecount = TheSongDB->NumCommonPhrases();
    for(int i = 0; i < phrasecount; i++){
        bitcount += CountBits(TheSongDB->GetCommonPhraseTracks(i));
    }
    float f1 = 2.0f;
    if(mRequireFullEnergy){
        f1 = 4.0f;
    }

    for(int i = 0; i < mTargets.size(); i++){
        mTargets[i] = std::max(std::floor(((float)bitcount / f1) * mTargets[i]), 1.0f);
    }
}

void DeployCountTracker::UpdateGoalValueLabel(UILabel&) const {}
void DeployCountTracker::UpdateCurrentValueLabel(UILabel&) const {}

String DeployCountTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    float f1 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x62);
        f1 = pPlayer->mStats.unk1c0;
    }
    Symbol sym = (int)f1 == 1 ? deploy_stat_tracker_contribution_1 : deploy_stat_tracker_contribution;
    return MakeString(Localize(sym, 0), f1);
}

void DeployCountTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x77);
        std::map<TrackerPlayerID, PlayerDeployData>::const_iterator cData = mDeployDataMap.find(id);
        MILO_ASSERT(cData != mDeployDataMap.end(), 0x7C);
        pPlayer->mStats.unk1c0 = cData->second.unk4;
    }
}

void DeployCountTracker::FirstFrame_(float){
    mDeployCount = 0;
    PlayerDeployData data;
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        mDeployDataMap[id] = data;
    }
    mBandDisplay.Initialize(gNullStr);
}

void DeployCountTracker::Poll_(float){
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        if(mSource->IsPlayerLocal(id)){
            Player* pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0xA5);
            PlayerDeployData& data = mDeployDataMap[id];
            bool energy = pPlayer->GetBandEnergy() >= 1.0f;
            bool ismaxmult = pPlayer->GetIndividualMultiplier() == pPlayer->GetMaxIndividualMultipler();
            bool b8 = pPlayer->CanDeployOverdrive();
            // bool u12 = false;
            // if(!mRequireFullEnergy || energy) u12 = true;
            // bool b5 = false;
            // if(!mRequireMaxMultiplier || ismaxmult) b5 = true;
            bool b4 = (b8 && (!mRequireFullEnergy || energy)) && (!mRequireMaxMultiplier || ismaxmult);
            bool c1 = data.unk2;
            bool deploying = pPlayer->IsDeployingBandEnergy();
            if(deploying && !data.unk3){
                bool b2 = true;
                if(mRequireFullEnergy && !data.unk0) b2 = false;
                bool b3 = true;
                if(mRequireMaxMultiplier && !data.unk1) b3 = false;
                if(b2 && b3){
                    LocalDeploy(id);
                    pPlayer->HandleType(send_tracker_deploy_msg);
                }
            }
            else if(!deploying){
                data.unk0 = energy;
                data.unk1 = ismaxmult;
                if(b4 && !c1){
                    GetPlayerDisplay(id).GainFocus(false);
                }
            }
            if(!b4 && c1){
                GetPlayerDisplay(id).LoseFocus(deploying);
            }
            data.unk2 = b4;
            data.unk3 = deploying;
        }
    }
}

void DeployCountTracker::RemoteDeploy(Player* p){
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if(pid.NotNull()){
        LocalDeploy(pid);
    }
}

void DeployCountTracker::LocalDeploy(const TrackerPlayerID& pid){
    mDeployDataMap[pid].unk4++;
    mDeployCount++;
    Symbol sym = mDeployCount == 1 ? deploy_count_tracker_progress_1 : deploy_count_tracker_progress;
    mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(sym, mDeployCount));
}

DataArrayPtr DeployCountTracker::GetTargetDescription(int idx) const {
    return TrackerDisplay::MakeIntegerTargetDescription(mTargets[idx]);
}
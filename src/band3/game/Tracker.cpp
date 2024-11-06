#include "game/Tracker.h"
#include "bandtrack/Track.h"
#include "bandtrack/TrackPanel.h"
#include "meta_band/ModifierMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

Tracker::Tracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : mFirstPoll(1), mBandDisplay(banddisp), mBroadcastDisplay(bcdisp), unk18(0), unk1c(0), unk20(gNullStr),
    unk24(1), unk28(0), unk29(0), unk2a(0), unk2c(0), unk38(0), unk3c(0), mSource(src), unk44(0), unk48(gNullStr), unk4c(gNullStr) {

}

Tracker::~Tracker(){
    RELEASE(mSource);
}

void Tracker::UpdateSource(TrackerSource* src){
    delete mSource;
    mSource = src;
}

void Tracker::Restart(){
    mPlayerDisplays.resize(5);

    int idx = 0;
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); !id.mGuid.Null(); id = mSource->GetNextPlayer(id)){
        Player* p = mSource->GetPlayer(id);
        mPlayerDisplays[idx++].mPlayer = p;
    }
    mFirstPoll = true;
    unk50 = unk30;
    if(unk38) TranslateRelativeTargets();

    for(TrackerPlayerID id = mSource->GetFirstPlayer(); !id.mGuid.Null(); id = mSource->GetNextPlayer(id)){
//     this_00 = (TrackerPlayerDisplay *)GetPlayerDisplay(this,(TrackerPlayerID *)&local_40);
//     TrackerPlayerDisplay::Disable(this_00);
    }
    Restart_();
}

void Tracker::HandleAddPlayer(Player* iPlayer){
    MILO_ASSERT(GetPlayerDisplayIndex( iPlayer ) == -1, 0x60);
    for(int i = 0; i < mPlayerDisplays.size(); i++){
        if(!mPlayerDisplays[i].mPlayer){
            mPlayerDisplays[i].mPlayer = iPlayer;
            break;
        }
    }
    GetTrackPanel()->SetSuppressUnisonDisplay(unk28);
    GetTrackPanel()->SetSuppressPlayerFeedback(unk2a);
    mSource->HandleAddPlayer(iPlayer);
    HandleAddPlayer_(iPlayer);
}

void Tracker::HandleRemovePlayer(Player* player){
    HandleRemovePlayer_(player);
    mSource->HandleRemovePlayer(player);
    int idx = GetPlayerDisplayIndex(player);
    if(idx != -1){
        mPlayerDisplays[idx].Disable();
        mPlayerDisplays[idx].mPlayer = nullptr;
    }
    if(mSource->GetPlayerCount() == 0){
        Restart();
    }
}

void Tracker::HandlePlayerSaved(Player* player){
    TrackerPlayerID pid = mSource->FindPlayerID(player);
    if(!pid.mGuid.Null() && mSource->IsPlayerEligible(pid)){
        HandlePlayerSaved_(pid);
    }
}

void Tracker::HandleGameOver(float f){
    HandleGameOver_(f);
    mBroadcastDisplay.Hide();
    SavePlayerStats();
    float pct = CalcProgressPercentage();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); !id.mGuid.Null(); id = mSource->GetNextPlayer(id)){
        if(mSource->IsPlayerLocal(id)){
            Player* pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0xAD);
            pPlayer->mStats.unk1c4 = pct;
        }
    }
}

void Tracker::StartIntro(){
    if(!TheModifierMgr->IsModifierActive(mod_nohud)){
        DataArrayPtr desc = GetBroadcastDescription();
        if(unk4c != gNullStr){
            mBroadcastDisplay.Broadcast(DataArrayPtr(unk4c), unk48);
        }
        else if(desc->Size() != 0){
            mBroadcastDisplay.Broadcast(desc, unk4c);
        }
    }
}

void Tracker::Poll(float f){
    if(mFirstPoll){
        ReachedTargetLevel(-1);
        FirstFrame_(f);
        mFirstPoll = false;
        GetTrackPanel()->SetSuppressTambourineDisplay(unk29);
        GetTrackPanel()->SetSuppressPlayerFeedback(unk2a);
        SetupDisplays();
    }
    Poll_(f);
}

void Tracker::Configure(const TrackerDesc& desc){

}

// void __thiscall Tracker::Configure(Tracker *this,TrackerDesc *param_1)

// {
//   *(undefined4 *)(this + 0x18) = *(undefined4 *)param_1;
//   *(undefined4 *)(this + 0x1c) = *(undefined4 *)(param_1 + 4);
//   *(undefined4 *)(this + 0x20) = *(undefined4 *)(param_1 + 8);
//   *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 0xc);
//   this[0x28] = *(Tracker *)(param_1 + 0x10);
//   this[0x29] = *(Tracker *)(param_1 + 0x11);
//   this[0x2a] = *(Tracker *)(param_1 + 0x12);
//   *(undefined4 *)(this + 0x2c) = *(undefined4 *)(param_1 + 0x14);
//   stlpmtx_std::_Vector_impl<><>::operator_=
//             ((_Vector_impl<><> *)(this + 0x30),(_Vector_impl<> *)(param_1 + 0x18));
//   this[0x38] = *(Tracker *)(param_1 + 0x20);
//   *(undefined4 *)(this + 0x3c) = *(undefined4 *)(param_1 + 0x24);
//   *(undefined4 *)(this + 0x44) = *(undefined4 *)(param_1 + 0x14);
//   stlpmtx_std::_Vector_impl<><>::operator_=
//             ((_Vector_impl<><> *)(this + 0x50),(_Vector_impl<> *)(param_1 + 0x18));
//   if (*(int *)(param_1 + 0x24) != 0) {
//     (**(code **)(*(int *)this + 0x20))(this);
//   }
//   return;
// }
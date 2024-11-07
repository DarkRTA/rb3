#include "game/FocusTracker.h"
#include "game/TrackerSource.h"
#include "os/Debug.h"
#include "utl/HxGuid.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

FocusTracker::FocusTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp),
    mFocusDelayMs(5000.0f), unk5c(0), unk60(0), unk74(0), unk78(0), unk7c(0), unk80(0), unk84(0), unk88(0), unk8c(0), unkc8(0) {

}

FocusTracker::~FocusTracker(){

}

void FocusTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    arr->FindData(focus_delay_ms, mFocusDelayMs, false);
    unka8.InitFromDataArray(arr->FindArray(chain_multipliers, false));
}

void FocusTracker::HandleRemovePlayer_(Player* p){
    if(mFocusPlayer.NotNull()){
        if(mSource->GetPlayerCount() == 0){
            mFocusPlayer = gNullUserGuid;
        }
        else {
            TrackerPlayerID focus = mFocusPlayer;
            if(!mSource->HasPlayer(mFocusPlayer)){
                bool b48;
                focus = GetNextFocusPlayer(mFocusPlayer, unk7c, b48);
                int flags = 1;
                if(b48) flags |= 8;
                SetFocusPlayer(focus, unk7c, (FocusFlags)flags);
            }
            mFocusPlayer = focus;

        }
    }
}

void FocusTracker::HandleGameOver_(float){}

void FocusTracker::Restart_(){
    unk74 = false;
    unk78 = 0;
    unk7c = 0;
    unk80 = 0;
    unk84 = 0;
    unk88 = 0;
    unk8c = 0;
    unkc8 = false;
}

void FocusTracker::HandlePlayerSaved_(const TrackerPlayerID& pid){
    if(mSource->IsPlayerLocal(pid)){
        GetPlayerDisplay(pid).Enable();
    }
}

void FocusTracker::FirstFrame_(float f){
    unk90.clear();
    mFocusPlayer = TrackerPlayerID();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        unk90[id] = 0;
        if(mSource->IsPlayerLocal(id)){
            GetPlayerDisplay(id).Enable();
        }
    }
    if(mSource->GetPlayerCount() > 0){
        bool b98;
        TrackerPlayerID cFirst = GetFirstFocusPlayer(b98);
        MILO_ASSERT(cFirst.NotNull(), 0x9E);
        if(mSource->IsPlayerLocal(cFirst)){
            int flags = 5;
            if(b98) flags |= 8;
            SetFocusPlayer(cFirst, f, (FocusFlags)flags);
        }
        mFocusPlayer = cFirst;
    }
    mBandDisplay.Initialize(gNullStr);
    unkc4 = -1;
}

void FocusTracker::Poll_(float f){
    if(!unkc8 && mFocusPlayer.NotNull()){
        if(mSource->IsPlayerLocal(mFocusPlayer) && !PlayerCanHaveFocus(mFocusPlayer)){
            bool b75;
            TrackerPlayerID next = GetNextFocusPlayer(mFocusPlayer, f, b75);
            int flags = 1;
            if(b75) flags |= 8;
            SetFocusPlayer(next, f, (FocusFlags)flags);
        }
        if(unk5c){
            if(f > unk78) ActivateFocus(f);
            else return;
        }
        bool b76 = false;
        bool b77 = false;
        CheckCondition(f, mSource->IsFinished(), b76, b77);
        if(mSource->IsPlayerLocal(mFocusPlayer)){
            if(b76){
                if(b77 && !unk74){
                    float mult = unka8.GetMultiplier(++unk8c);
                    unk88++;
                    unk84 += mult;
                    unk90[mFocusPlayer]++;
                }
                bool b78;
                TrackerPlayerID next = GetNextFocusPlayer(mFocusPlayer, f, b78);
                int flags = 0;
                if(b77) flags = 2;
                if(b78) flags |= 8;
                if(next.mGuid == mFocusPlayer.mGuid && b78 == unk74) flags |= 0x10;
                SetFocusPlayer(next, f, (FocusFlags)flags);
            }
            int idx = unka8.GetMultiplierIndex(unk8c);
            if(unkc4 != idx){
                if(mFocusPlayer.NotNull()){
                    GetPlayerDisplay(mFocusPlayer).SetSecondaryStateLevel(idx);
                }
                unkc4 = idx;
            }
        }
        if(f - unk80 > 1000.0f){
            unk80 = f;
        }
        unk7c = f;
        if(mSource->IsFinished() && b76){
            unkc8 = true;
        }
    }
}
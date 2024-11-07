#include "game/FocusTracker.h"
#include "Player.h"
#include "game/TrackerDisplay.h"
#include "game/TrackerSource.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/HxGuid.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

FocusTracker::FocusTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp),
    mFocusDelayMs(5000.0f), unk5c(0), unk60((FocusFlags)0), unk74(0), unk78(0), unk7c(0), unk80(0), unk84(0), unk88(0), unk8c(0), unkc8(0) {

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
    mFocusCountMap.clear();
    mFocusPlayer = TrackerPlayerID();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        mFocusCountMap[id] = 0;
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
                    mFocusCountMap[mFocusPlayer]++;
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

void FocusTracker::TargetSuccess(int) const {}

DataArrayPtr FocusTracker::GetTargetDescription(int i) const {
    return TrackerDisplay::MakeIntegerTargetDescription(unk50[i]);
}

void FocusTracker::UpdateGoalValueLabel(UILabel& label) const {
    label.SetTokenFmt(tour_goal_focus_goal_format, (int)unk50.front());
}

void FocusTracker::UpdateCurrentValueLabel(UILabel& label) const {
    label.SetTokenFmt(tour_goal_focus_result_format, (int)unk84);
}

String FocusTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    int i3 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x169);
        i3 = pPlayer->mStats.unk1c0;
    }
    return MakeString(Localize(GetContributionToken(i3), 0), i3);
}

Symbol FocusTracker::GetContributionToken(int) const {
    return tour_goal_focus_player_contribution_format;
}

void FocusTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x17C);
        std::map<TrackerPlayerID, int>::const_iterator cData = mFocusCountMap.find(id);
        MILO_ASSERT(cData != mFocusCountMap.end(), 0x181);
        pPlayer->mStats.unk1c0 = cData->second;
    }
}

TrackerPlayerID FocusTracker::GetNextFocusPlayer(const TrackerPlayerID& pid, float f, bool& b) const {
    TrackerPlayerID empty;
    TrackerPlayerID ret(pid);
    bool b1;
    do {
        TrackerPlayerID filler(ret);
        ret = mSource->GetNextPlayer(ret);
        if(!ret.NotNull()){
            ret = mSource->GetFirstPlayer();
        }
        bool wantsfocus = PlayerWantsFocus(ret, f);
        b = !wantsfocus;
        if(ret.mGuid == pid.mGuid) break;
        if(!empty.NotNull()){
            empty = ret;
        }
        else if(ret.mGuid == empty.mGuid){
            break;
        }
        bool canfocus = PlayerCanHaveFocus(ret);
        b1 = false;
        if(canfocus && wantsfocus) b1 = true;
    } while(!b1);
    return ret;
}

bool FocusTracker::PlayerCanHaveFocus(const TrackerPlayerID& pid) const {
    return mSource->GetPlayer(pid)->mEnabledState == kPlayerEnabled;
}

void FocusTracker::SetFocusPlayer(const TrackerPlayerID& pid, float f, FocusFlags flags){
    LocalSetFocusPlayer(pid, f, unk88, unk84, flags);
    Player* pPlayer = mSource->GetPlayer(pid);
    MILO_ASSERT(pPlayer, 0x1D6);
    static Message focusMsg("send_tracker_focus", 0, 0, 0);
    focusMsg[0] = unk88;
    focusMsg[1] = (int)(unk84 * 1000.0f);
    focusMsg[2] = flags;
    pPlayer->HandleType(focusMsg);
}

void FocusTracker::LocalSetFocusPlayer(const TrackerPlayerID& pid, float f1, int i, float f2, FocusFlags flags){
    if(mFocusPlayer.NotNull()){
        SetTrackFocus(mFocusPlayer, false, flags);
    }
    FocusLeaving(flags);
    float ff = 0;
    unk74 = flags & 8;
    if(!(flags & 1)){
        ff = mFocusDelayMs;
    }
    unk84 = f2;
    unk78 = f1 + ff;
    unk88 = i;
    mBandDisplay.HandleIncrement();
    unk60 = flags;
    unk5c = true;
    if(flags & 2){
        BroadcastFocusSuccess();
    }
    mFocusPlayer = pid;
}

void FocusTracker::ActivateFocus(float f){
    HandleFocusSwitch(f);
    SetTrackFocus(mFocusPlayer, true, unk60);
    unk5c = false;
}

void FocusTracker::RemoteSetFocusPlayer(Player* p, int i1, int i2, FocusFlags flags){
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if(pid.NotNull()){
        LocalSetFocusPlayer(pid, unk7c, i1, (float)i2 / 10000.0f, flags);
    }
}

TrackerPlayerID FocusTracker::GetFirstFocusPlayer(bool& b) const {
    return GetNextFocusPlayer(mSource->GetFirstPlayer(), 0, b);
}

void FocusTracker::SetTrackFocus(const TrackerPlayerID& pid, bool b, FocusFlags flags){
    if(mSource->IsPlayerLocal(pid)){
        if(b){
            if(!(flags & 8) && !(flags & 0x10)){
                GetPlayerDisplay(pid).GainFocus(flags & 4);
                int idx = unka8.GetMultiplierIndex(unk8c);
                if(mFocusPlayer.NotNull()){
                    GetPlayerDisplay(pid).SetSecondaryStateLevel(idx);
                }
                unkc4 = idx;
            }
        }
        else if(!unk74){
            bool flag2 = flags & 2;
            if(flags & 0x10){
                GetPlayerDisplay(pid).Pulse(flag2);
            }
            else {
                GetPlayerDisplay(pid).LoseFocus(flag2);
            }
        }
    }
}
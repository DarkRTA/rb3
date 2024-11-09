#include "game/PerfectSectionTracker.h"
#include "beatmatch/TrackType.h"
#include "game/TrackerSource.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

PerfectSectionTracker::PerfectSectionTracker(TrackerSource* src, TrackerBandDisplay& banddisp, TrackerBroadcastDisplay& bcdisp) : Tracker(src, banddisp, bcdisp),
    unk58("chorus"), unkb0(1.0f), unkb4(-1.0f), unkb8(0), unkc0(0), unkc4(0), unkc8(-1), unke4(0), unke5(0) {

}

PerfectSectionTracker::~PerfectSectionTracker(){

}

void PerfectSectionTracker::ConfigureTrackerSpecificData(const DataArray* arr){
    arr->FindData(required_accuracy, unkb0, false);
    arr->FindData(section_name, unk58, false);
    arr->FindData(require_all_players, unke5, false);
    unke8.InitFromDataArray(arr->FindArray(chain_multipliers, false));
}

void PerfectSectionTracker::HandlePlayerSaved_(const TrackerPlayerID& pid){
    Player* pPlayer = mSource->GetPlayer(pid);
    MILO_ASSERT(pPlayer, 0x46);
    std::map<TrackType, PlayerStreakData>::iterator it = unk5c.find(pPlayer->GetTrackType());
    if(it != unk5c.end()){
        it->second.unk1c = 0;
    }
    GetPlayerDisplay(pid).GainFocus(false);
}

void PerfectSectionTracker::FirstFrame_(float){
    mBandDisplay.Initialize(perfect_section_tracker_description);
    mSectionData.clear();
    mSectionData.resize(unk104.GetSectionCount());
    unkac = 0;
    unkb4 = -1.0f;
    unkb8 = 0;
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    unkc8 = -1;
    unke4 = 0;
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x6D);
        std::map<TrackType, PlayerStreakData>::iterator it = unk5c.find(pPlayer->GetTrackType());
        if(it != unk5c.end()){
            it->second.unk1c = 0;
            if(pPlayer->IsLocal()){
                GetPlayerDisplay(id).Enable();
            }
        }
    }
}

void PerfectSectionTracker::Poll_(float){
    
}

void PerfectSectionTracker::RemoteSectionComplete(Player* p, int iExtentIndex, int flags, int i){
    MILO_ASSERT_RANGE(iExtentIndex, 0, mSectionData.size(), 0xFC);
    TrackerPlayerID pid = mSource->FindPlayerID(p);
    if(pid.NotNull()){
        LocalSectionComplete(pid, iExtentIndex, (SectionFlags)flags, (float)i / 10000.0f);
    }
}

void PerfectSectionTracker::CheckForCompletedSections(){
    if(unkac < mSectionData.size()){
        int playercount = mSource->GetPlayerCount();
        if(playercount == 0) return;
        while(unkac < mSectionData.size() && mSectionData[unkac].unk0 >= playercount){
            SectionData& cur = mSectionData[unkac];
            float curc = cur.unkc;
            int cur8 = cur.unk8;

            if(cur.unk4 > 0){
                if(unke5){
                    if(cur8 == cur.unk4){
                        curc = unke8.GetMultiplier(++unkb8);
                        mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(perfect_section_band_tracker_success));
                    }
                    else {
                        unkb8 = 0;
                        curc = 0;
                        Symbol sym = cur8 == 1 ? perfect_section_tracker_progress_1 : perfect_section_tracker_progress;
                        mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(sym, cur8));
                    }
                }
                else {
                    if(cur8 == cur.unk4){
                        mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(perfect_section_band_tracker_success));
                    }
                    else {
                        Symbol sym = cur8 == 1 ? perfect_section_tracker_progress_1 : perfect_section_tracker_progress;
                        mBroadcastDisplay.ShowBriefBandMessage(DataArrayPtr(sym, cur8));
                    }
                }
            }
            unkac++;
            unkb4 += curc;
        }
    }
}

void PerfectSectionTracker::LocalSectionComplete(const TrackerPlayerID& pid, int iExtentIndex, SectionFlags flags, float f){
    MILO_ASSERT_RANGE(iExtentIndex, 0, mSectionData.size(), 0x16B);
    SectionData& cur = mSectionData[iExtentIndex];
    cur.unk0++;
    if(flags & 2){
        cur.unk4++;
        if(flags & 1){
            cur.unk8++;
            cur.unkc += f;
        }
    }
}

void PerfectSectionTracker::HandleEnterExtent(float f, int i, bool b){
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        if(mSource->IsPlayerLocal(id)){
            Player* pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0x191);
            TrackType key = pPlayer->GetTrackType();
            std::map<TrackType, PlayerStreakData>::iterator it = unk5c.find(key);
            if(it != unk5c.end()){
                if(!b){
                    int iac = 0;
                    int ib0 = 0;
                    int i5 = unk104.GetSectionEndTick(i);
                    unk104.GetGemStatsInRange(pPlayer, i5, MsToTick(f), iac, ib0);
                    it->second.unk0 = pPlayer->mStats.mMissCount;
                    it->second.unk4 = pPlayer->mStats.mHitCount - iac;
                    it->second.unk8 = pPlayer->mStats.m0x0c - ib0;
                    it->second.unkc = unk104.CountGemsInSection(pPlayer, i);
                    it->second.unk10 = -1.0f;
                    it->second.unk14 = -1;
                    it->second.unk18 = false;
                }
                unk74[key] = false;
                if(it->second.unkc > 0){
                    SetPlayerProgress(id, 0);
                    int multidx = unke8.GetMultiplierIndex(it->second.unk1c);
                    if(it->second.unk14 != multidx){
                        GetPlayerDisplay(id).SetSecondaryStateLevel(multidx);
                        it->second.unk14 = multidx;
                    }
                    if(!it->second.unk19){
                        GetPlayerDisplay(id).GainFocus(false);
                        it->second.unk19 = true;
                    }
                }
            }
        }
    }
}

void PerfectSectionTracker::HandleInExtent(float f, int i){
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        if(mSource->IsPlayerLocal(id)){
            Player* pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0x1DA);
            TrackType key = pPlayer->GetTrackType();
            std::map<TrackType, PlayerStreakData>::iterator it = unk5c.find(key);
            if(it != unk5c.end()){
                if(it->second.unkc){
            //         local_88 = 0x43300000;
            //         iVar5 = *(int *)(pPVar9 + 0x20) - (*(int *)(iVar8 + 0x1c) - *(int *)(pPVar9 + 0x1c));
            //         uStack_84 = iVar5 ^ 0x80000000;
            //         iVar8 = *(int *)(iVar8 + 0x10) - *(int *)(pPVar9 + 0x18);
            //         fVar2 = (float)iVar5;
            //         fVar1 = 0.0;
            //         if (fVar2 != 0.0) {
            //           uStack_7c = iVar8 ^ 0x80000000;
            //           local_80 = 0x43300000;
            //           fVar1 = (float)iVar8 / fVar2;
            //         }
            //         if (fVar1 != *(float *)(pPVar9 + 0x24)) {
            //           fVar3 = fVar1 / *(float *)(this + 0xb0);
            //           fVar2 = 1.0;
            //           if ((fVar3 <= 1.0) && (fVar2 = fVar3, fVar3 < 0.0)) {
            //             fVar2 = 0.0;
            //           }
            //           Tracker::SetPlayerProgress((Tracker *)this,(TrackerPlayerID *)&local_98,fVar2);
            //           if ((*(float *)(this + 0xb0) <= fVar1) && (pPVar9[0x2c] == (PerfectSectionTracker)0x0)) {
            //             this_00 = (TrackerPlayerDisplay *)
            //                       Tracker::GetPlayerDisplay((Tracker *)this,(TrackerPlayerID *)&local_98);
            //             TrackerPlayerDisplay::SetSuccessState(this_00,true);
            //             pPVar9[0x2c] = (PerfectSectionTracker)0x1;
            //           }
            //           *(float *)(pPVar9 + 0x24) = fVar1;
            //         }
                }
            }
        }
    }
}

void PerfectSectionTracker::HandleExitExtent(float f, int i, bool b){
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        if(mSource->IsPlayerLocal(id)){
            Player* pPlayer = mSource->GetPlayer(id);
            MILO_ASSERT(pPlayer, 0x218);
            TrackType key = pPlayer->GetTrackType();
            std::map<TrackType, PlayerStreakData>::iterator it = unk5c.find(key);
            if(it != unk5c.end()){
                int i118 = 0;
                int i11c = 0;
                int tick = unk104.GetSectionEndTick(unkc4);
                unk104.GetGemStatsInRange(pPlayer, tick, MsToTick(f), i118, i11c);
                float f17 = 0;
                int i15 = 0;
                bool b1 = false;
                bool b14 = false;
                if(it->second.unkc != 0){
                    i15 |= 2;
                    b1 = true;
                    int i6 = it->second.unkc - (pPlayer->mStats.m0x0c - it->second.unk8) - i11c;
                    int i12 = it->second.unk8 - (pPlayer->mStats.mHitCount - it->second.unk4) - i118;
                    if((float)i12 / (float)i6 >= unkb0){
                        i15 |= 3;
                        b14 = true;
                        unk8c[key]++;
                        f17 = unke8.GetMultiplier(it->second.unk1c++);
                    }
                    else {
                        it->second.unk1c = 0;
                    }             
                }
                if(b){
                    it->second.unk0 = pPlayer->mStats.mMissCount;
                    it->second.unk4 = pPlayer->mStats.mHitCount - i118;
                    it->second.unk8 = pPlayer->mStats.m0x0c - i11c;
                    it->second.unkc = unk104.CountGemsInSection(pPlayer, unkc4 + 1);
                    it->second.unk10 = -1.0f;
                    it->second.unk14 = -1;
                    it->second.unk18 = false;
                }
                LocalSectionComplete(id, unkc4, (SectionFlags)i15, f17);
                static Message sectionMsg("send_tracker_section_complete", 0, 0, 0);
                sectionMsg[0] = unkc4;
                sectionMsg[1] = i15;
                sectionMsg[2] = (int)(f17 * 10000.0f);
                pPlayer->HandleType(sectionMsg);
                if(b1){
                    if(b && it->second.unkc > 0){
                        GetPlayerDisplay(id).Pulse(b14);
                    }
                    else {
                        GetPlayerDisplay(id).LoseFocus(b14);
                        it->second.unk19 = false;
                    }
                }
            }
        }
    }
}

void PerfectSectionTracker::TranslateRelativeTargets(){
    unk104.Init();
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* player = mSource->GetPlayer(id);
        MILO_ASSERT(player, 0x2A5);
    }
}

void PerfectSectionTracker::UpdateGoalValueLabel(UILabel& label) const {
    label.SetTokenFmt(tour_goal_band_perfect_section_goal_format, (int)mTargets.front());
}

void PerfectSectionTracker::UpdateCurrentValueLabel(UILabel& label) const {
    label.SetTokenFmt(tour_goal_band_perfect_section_result_format, unkb4);
}

String PerfectSectionTracker::GetPlayerContributionString(Symbol s) const {
    TrackerPlayerID pid = mSource->GetIDFromInstrument(s);
    int f1 = 0;
    if(pid.NotNull()){
        Player* pPlayer = mSource->GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x2D9);
        f1 = pPlayer->mStats.unk1c0;
    }
    Symbol sym = (int)f1 == 1 ? tour_goal_band_perfect_section_result_format_1 : tour_goal_band_perfect_section_result_format;
    return MakeString(Localize(sym, 0), f1);
}

void PerfectSectionTracker::SavePlayerStats() const {
    for(TrackerPlayerID id = mSource->GetFirstPlayer(); id.NotNull(); id = mSource->GetNextPlayer(id)){
        Player* pPlayer = mSource->GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x2EF);
        std::map<TrackType, int>::const_iterator it = unk8c.find(pPlayer->GetTrackType());
        if(it != unk8c.end()){
            pPlayer->mStats.unk1c0 = it->second;
        }
    }
}

DataArrayPtr PerfectSectionTracker::GetBroadcastDescription() const {
    return DataArrayPtr(perfect_section_tracker_explanation);
}
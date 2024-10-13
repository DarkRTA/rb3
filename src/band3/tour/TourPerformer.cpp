#include "tour/TourPerformer.h"
#include "QuestManager.h"
#include "TourDesc.h"
#include "TourProgress.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "ui/UILabel.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

TourPerformerImpl::TourPerformerImpl(BandUserMgr& mgr) : mUserMgr(mgr), mQuestFilter(""), mFilterType(kTourSetlist_Invalid) {
    mMetaPerformer = MetaPerformer::Current();
}

DECOMP_FORCEACTIVE(TourPerformer, __FILE__, "!members.empty()")

TourPerformerImpl::~TourPerformerImpl(){

}

bool TourPerformerImpl::HasWritePermission() const {
    return HasSyncPermission();
}

bool TourPerformerImpl::IsRandomSetList() const {
    return mFilterType == kTourSetlist_Random;
}

Symbol TourPerformerImpl::GetCurrentQuest() const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x73);
    return pProgress->mCurrentQuest;
}

int TourPerformerImpl::GetTotalQuestStars() const { return 5; }

Symbol TourPerformerImpl::GetCurrentQuestDisplayName() const {
    Symbol quest = GetCurrentQuest();
    Quest* pQuest = TheQuestMgr.GetQuest(quest);
    if(!pQuest) return quest;
    MILO_ASSERT(pQuest, 0x8C);
    return pQuest->GetDisplayName();
}

Symbol TourPerformerImpl::GetCurrentQuestDescription() const {
    Symbol quest = GetCurrentQuest();
    Quest* pQuest = TheQuestMgr.GetQuest(quest);
    if(!pQuest) return quest;
    MILO_ASSERT(pQuest, 0x9F);
    return pQuest->GetDescription();
}

Symbol TourPerformerImpl::GetCurrentQuestLongDescription() const {
    Symbol quest = GetCurrentQuest();
    Quest* pQuest = TheQuestMgr.GetQuest(quest);
    if(!pQuest) return quest;
    MILO_ASSERT(pQuest, 0xB2);
    return pQuest->GetLongDescription();
}

Symbol TourPerformerImpl::GetCurrentQuestFilter() const { return mQuestFilter; }

int TourPerformerImpl::GetGigSongCount() const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0xC2);
    return pProgress->GetNumSongsForCurrentGig();
}

bool TourPerformerImpl::GetCurrentQuestFilterIsCustom() const {
    return mFilterType == kTourSetlist_Custom;
}

void TourPerformerImpl::CleanupGigData(){
    mGigData.clear();
}

void TourPerformerImpl::CompleteQuest(){}

void TourPerformerImpl::UpdateCompleteTourStats(TourProgress* i_pProgress){
    MILO_ASSERT(i_pProgress, 0x10B);
    BandProfile* pf = TheProfileMgr.FindTourProgressOwner(i_pProgress);
    if(pf){
        AccomplishmentProgress* prog = pf->AccessAccomplishmentProgress();
        int numstars = i_pProgress->GetNumStars();
        Symbol desc = i_pProgress->GetTourDesc();
        int toursplayed = prog->GetToursPlayed(desc);
        TheAccomplishmentMgr->UpdateTourPlayedForAllParticipants(desc);
        if(numstars >= i_pProgress->GetTotalStarsForTour()){
            int tourstars = prog->GetToursGotAllStars(desc) + 1;
            prog->SetToursGotAllStars(desc, tourstars);
        }
        TheTour->UpdateProgressWithCareerData();
    }
}

void TourPerformerImpl::UpdateTourStats(TourProgress* i_pProgress){
    MILO_ASSERT(i_pProgress, 0x125);
    if(!mGigData.empty()){
        const GigData& data = GetMostRecentGigData();
        BandProfile* pf = TheProfileMgr.FindTourProgressOwner(i_pProgress);
        if(pf){
            AccomplishmentProgress* prog = pf->AccessAccomplishmentProgress();
            Quest* curquest = TheQuestMgr.GetQuest(GetCurrentQuest());
            if(curquest){
                TourGameType ty = curquest->GetGameRules()->GetGameType();
                if(data.unk8 > 0){
                    int qcount = prog->GetQuestCompletedCount(ty) + 1;
                    prog->SetQuestCompletedCount(ty, qcount);
                }
            }
        }
    }
}

void TourPerformerImpl::HandleSongCompleted(const BandStatsInfo* stats){
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x147);
    if(mMetaPerformer->IsFirstSong()){
        CleanupGigData();
        pProgress->ClearNewStars();
    }
    if(stats){
        const PerformerStatsInfo& info = stats->GetBandStats();
        UpdateGigDataForSong(mMetaPerformer->Song(), info.mStars);
    }
    else {
        GigData data;
        data.unk0 = mMetaPerformer->Song();
        mGigData.push_back(data);
    }
    pProgress->EarnStars(GetMostRecentGigData().unkc);
}

void TourPerformerImpl::RestartLastSong(){
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x172);
    pProgress->RemoveStars(GetMostRecentGigData().unkc);
    mGigData.pop_back();
}

void TourPerformerImpl::CompleteSong(std::vector<BandUser*>& vec, const BandStatsInfo* stats, bool b){
    MILO_ASSERT(stats, 0x180);
    HandleSongCompleted(stats);
}

const GigData& TourPerformerImpl::GetMostRecentGigData() const {
    int iMostRecentSong = mGigData.size() - 1;
    MILO_ASSERT(iMostRecentSong >= 0, 0x188);
    return mGigData[iMostRecentSong];
}

int TourPerformerImpl::GetSongQuestStars() const {
    return GetMostRecentGigData().unk8;
}

int TourPerformerImpl::GetQuestSuccessfulSongCount() const {
    int num = mMetaPerformer->NumSongs();
    int successes = 0;
    for(int i = 0; i < num; i++){
        if(mGigData[i].unk8 >= 5) successes++;
    }
    return successes;
}

bool TourPerformerImpl::IsQuestWon(Symbol s) const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x1B2);
    TourDesc* pTourDesc = TheTour->GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x1B6);
    int curgignum = pProgress->GetCurrentGigNum();
    int success = GetQuestSuccessfulSongCount();
    int num = pTourDesc->GetNumSongsForGigNum(curgignum);
    return num <= success;
}

int TourPerformerImpl::GetBaseSongStars() const {
    return GetMostRecentGigData().unk4;
}

int TourPerformerImpl::GetTotalSongStars() const {
    return GetMostRecentGigData().unkc;
}

Symbol TourPerformerImpl::GetCurrentQuestSuccessMessage() const {
    Quest* pQuest = TheQuestMgr.GetQuest(GetCurrentQuest());
    MILO_ASSERT(pQuest, 0x1E1);
    return pQuest->GetSuccessSymbol();
}

int TourPerformerImpl::GetTotalStarsPossibleForCurrentGig(){
    Quest* pQuest = TheQuestMgr.GetQuest(GetCurrentQuest());
    MILO_ASSERT(pQuest, 0x20F);
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x213);
    return pProgress->GetNumSongsForCurrentGig() * 10;
}

bool TourPerformerImpl::IsWinning() const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x22A);
    TourDesc* pTourDesc = TheTour->GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x22F);
    int gignum = pProgress->GetCurrentGigNum();
    if(gignum < pTourDesc->GetNumGigs() - 1){
        return false;
    }
    else {
        MetaPerformer* pMetaPerformer = MetaPerformer::Current();
        MILO_ASSERT(pMetaPerformer, 0x23B);
        if(!pMetaPerformer->IsLastSong()) return false;
        else return true;
    }
}

void TourPerformerImpl::HandleSongCompleteWithInvalidScore(){
    HandleSongCompleted(0);
}

void TourPerformerImpl::HandleCheatWinQuest(Symbol s){
    mGigData.clear();
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x256);
    TourDesc* pTourDesc = TheTour->GetTourDesc(pProgress->GetTourDesc());
    MILO_ASSERT(pTourDesc, 0x25A);
    
    int songcount = pTourDesc->GetNumSongsForGigNum(pProgress->GetCurrentGigNum());
    for(int i = 0; i < songcount; i++) pProgress->EarnStars(10);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(TourPerformerImpl)
    HANDLE_EXPR(is_local, IsLocal())
    HANDLE_EXPR(has_write_permission, HasWritePermission())
    HANDLE_EXPR(is_current_quest_custom, GetCurrentQuestFilterIsCustom())
    HANDLE_EXPR(current_quest, GetCurrentQuest())
    HANDLE_ACTION(complete_quest, CompleteQuest())
    HANDLE_EXPR(get_gig_songcount, GetGigSongCount())
    HANDLE_EXPR(current_quest_filter, GetCurrentQuestFilter())
    HANDLE_EXPR(current_quest_display_name, GetCurrentQuestDisplayName())
    HANDLE_EXPR(current_quest_description, GetCurrentQuestDescription())
    HANDLE_EXPR(current_quest_long_description, GetCurrentQuestLongDescription())
    HANDLE_EXPR(get_total_quest_stars, GetTotalQuestStars())
    HANDLE_EXPR(get_gig_stars, GetTotalGigStars())
    HANDLE_EXPR(get_total_stars_possible_for_current_gig, GetTotalStarsPossibleForCurrentGig())
    HANDLE_EXPR(get_base_song_stars, GetBaseSongStars())
    HANDLE_EXPR(get_song_quest_stars, GetSongQuestStars())
    HANDLE_EXPR(get_total_song_stars, GetTotalSongStars())
    HANDLE_EXPR(get_current_quest_success_msg, GetCurrentQuestSuccessMessage())
    HANDLE_ACTION(update_quest_goal_label, UpdateQuestGoalLabel(_msg->Obj<UILabel>(2)))
    HANDLE_ACTION(update_quest_result_label, UpdateQuestResultLabel(_msg->Obj<UILabel>(2)))
    HANDLE_ACTION(update_tour_player_contribution_label, UpdateTourPlayerContributionLabel(_msg->Obj<UILabel>(2), _msg->Obj<BandUser>(3)))
    HANDLE_ACTION(handle_song_completion_with_invalid_score, HandleSongCompleteWithInvalidScore())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2A4)
END_HANDLERS
#pragma pop
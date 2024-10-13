#include "tour/TourChallengeResultsPanel.h"
#include "TourPerformer.h"
#include "meta_band/AppLabel.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourProgress.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

TourChallengeResultsPanel::TourChallengeResultsPanel(){

}

void TourChallengeResultsPanel::Enter(){ UIPanel::Enter(); }

int TourChallengeResultsPanel::GetPreGigTotalStars() const {
    int iTotalTourStars = GetTotalTourStars();
    int iGigTotal = GetGigTotalStars();
    MILO_ASSERT(iTotalTourStars >= iGigTotal, 0x34);
    return iTotalTourStars - iGigTotal;
}

int TourChallengeResultsPanel::GetTotalTourStars() const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x3F);
    return pProgress->GetNumStars();
}

int TourChallengeResultsPanel::GetGigTotalStars() const {
    MILO_ASSERT(TheTour, 0x47);
    TourPerformerImpl* pPerformer = TheTour->unk24;
    MILO_ASSERT(pPerformer, 0x4A);
    return pPerformer->GetTotalGigStars();
}

int TourChallengeResultsPanel::GetGigMaxStars() const {
    MILO_ASSERT(TheTour, 0x52);
    TourPerformerImpl* pPerformer = TheTour->unk24;
    MILO_ASSERT(pPerformer, 0x55);
    return pPerformer->GetTotalStarsPossibleForCurrentGig();
}

Symbol TourChallengeResultsPanel::GetChallengeName() const {
    MILO_ASSERT(TheTour, 0x5D);
    Quest* pQuest = TheTour->GetQuest();
    MILO_ASSERT(pQuest, 0x60);
    return pQuest->GetDisplayName();
}

void TourChallengeResultsPanel::UpdateSetlistLabel(UILabel* i_pLabel){
    MILO_ASSERT(i_pLabel, 0x68);
    TourPerformerImpl* pPerformer = TheTour->unk24;
    MILO_ASSERT(pPerformer, 0x6B);
    i_pLabel->SetTextToken(pPerformer->GetCurrentQuestFilter());
}

void TourChallengeResultsPanel::UpdateSongName(int ii, UILabel* i_pLabel){
    MILO_ASSERT(i_pLabel, 0x74);
    TourPerformerImpl* pTourPerformer = TheTour->unk24;
    MILO_ASSERT(pTourPerformer, 0x76);
    if(ii < pTourPerformer->mGigData.size()){
        AppLabel* pLabel = dynamic_cast<AppLabel*>(i_pLabel);
        MILO_ASSERT(pLabel, 0x7C);
        pLabel->SetSongName(pTourPerformer->mGigData[ii].unk0, true);
    }
    else i_pLabel->SetTextToken(gNullStr);
}

int TourChallengeResultsPanel::GetSongTotalStars(int i){
    TourPerformerImpl* pTourPerformer = TheTour->unk24;
    MILO_ASSERT(pTourPerformer, 0x8B);
    int stars = 0;
    if(i < pTourPerformer->mGigData.size()){
        stars = pTourPerformer->mGigData[i].unkc;
    }
    return stars;
}

int TourChallengeResultsPanel::GetSongStars(int i){
    TourPerformerImpl* pTourPerformer = TheTour->unk24;
    MILO_ASSERT(pTourPerformer, 0x9B);
    int stars = 0;
    if(i < pTourPerformer->mGigData.size()){
        stars = pTourPerformer->mGigData[i].unk4;
    }
    return stars;
}

int TourChallengeResultsPanel::GetChallengeStars(int i){
    TourPerformerImpl* pTourPerformer = TheTour->unk24;
    MILO_ASSERT(pTourPerformer, 0xAB);
    int stars = 0;
    if(i < pTourPerformer->mGigData.size()){
        stars = pTourPerformer->mGigData[i].unk8;
    }
    return stars;
}

int TourChallengeResultsPanel::GetSongCount(){
    TourPerformerImpl* pTourPerformer = TheTour->unk24;
    MILO_ASSERT(pTourPerformer, 0xBB);
    return pTourPerformer->mGigData.size();
}

BEGIN_HANDLERS(TourChallengeResultsPanel)
    HANDLE_EXPR(get_pregig_total_stars, GetPreGigTotalStars())
    HANDLE_EXPR(get_tour_total_stars, GetTotalTourStars())
    HANDLE_EXPR(get_gig_total_stars, GetGigTotalStars())
    HANDLE_EXPR(get_gig_max_stars, GetGigMaxStars())
    HANDLE_EXPR(get_challenge_name, GetChallengeName())
    HANDLE_ACTION(update_setlist_label, UpdateSetlistLabel(_msg->Obj<UILabel>(2)))
    HANDLE_EXPR(get_song_total_stars, GetSongTotalStars(_msg->Int(2)))
    HANDLE_ACTION(update_songname, UpdateSongName(_msg->Int(2), _msg->Obj<UILabel>(3)))
    HANDLE_EXPR(get_songstars, GetSongStars(_msg->Int(2)))
    HANDLE_EXPR(get_challengestars, GetChallengeStars(_msg->Int(2)))
    HANDLE_EXPR(get_songcount, GetSongCount())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xE0)
END_HANDLERS
#include "tour/TourPerformerLocal.h"
#include "game/BandUserMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "os/Debug.h"
#include "tour/QuestManager.h"
#include "tour/Tour.h"
#include "tour/TourPerformer.h"
#include "tour/TourProgress.h"
#include "utl/Symbol.h"
#include "utl/Symbols4.h"

TourPerformerLocal::TourPerformerLocal(BandUserMgr& mgr) : TourPerformerImpl(mgr) {

}

TourPerformerLocal::~TourPerformerLocal(){

}

void TourPerformerLocal::SyncSave(BinStream& bs, unsigned int) const {
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x37);
    pProgress->SyncSave(bs);
    bs << mQuestFilter;
    bs << mFilterType;
    int numgigs = mGigData.size();
    bs << numgigs;
    for(int i = 0; i < numgigs; i++){

    }
}

void TourPerformerLocal::MakeDirty(){
    MetaPerformer* pPerformer = MetaPerformer::Current();
    MILO_ASSERT(pPerformer, 0x4E);
    pPerformer->SetSyncDirty(-1, true);
}

void TourPerformerLocal::SelectVenue(){
    MILO_ASSERT(mMetaPerformer, 0x57);
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x5B);
    bool autovocalson = TheModifierMgr->IsModifierActive(mod_auto_vocals);
    Symbol curvenue = pProgress->GetVenueForCurrentGig();
    if(curvenue != gNullStr && !autovocalson){
        mMetaPerformer->SetVenue(curvenue);
    }
    else mMetaPerformer->SelectRandomVenue();
}

void TourPerformerLocal::ClearCurrentQuest(){
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x6E);
    pProgress->SetCurrentQuest("");
    MakeDirty();
}

void TourPerformerLocal::ClearCurrentQuestFilter(){
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x78);
    pProgress->ClearQuestFilters();
    mQuestFilter = "";
    mFilterType = kTourSetlist_Invalid;
    MakeDirty();
}

void TourPerformerLocal::SetCurrentQuest(Symbol i_symQuest){
    MILO_ASSERT(TheQuestMgr.HasQuest( i_symQuest ), 0x9C);
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x87);
    pProgress->SetCurrentQuest(i_symQuest);
    MakeDirty();
}

void TourPerformerLocal::SetCurrentQuestFilter(Symbol quest, TourSetlistType ty){
    mQuestFilter = quest;
    mFilterType = ty;
    MakeDirty();
}

void TourPerformerLocal::CompleteQuest(){
    TourPerformerImpl::CompleteQuest();
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x9B);
    TheQuestMgr.CompleteQuest(pProgress, GetCurrentQuest());
    MakeDirty();
}
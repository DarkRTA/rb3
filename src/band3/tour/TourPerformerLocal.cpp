#include "tour/TourPerformerLocal.h"
#include "game/BandUserMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/QuestManager.h"
#include "tour/Tour.h"
#include "tour/TourPerformer.h"
#include "tour/TourProgress.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

TourPerformerLocal::TourPerformerLocal(BandUserMgr &mgr) : TourPerformerImpl(mgr) {}

TourPerformerLocal::~TourPerformerLocal() {}

void TourPerformerLocal::SyncSave(BinStream &bs, unsigned int) const {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x37);
    pProgress->SyncSave(bs);
    bs << mQuestFilter;
    bs << mFilterType;
    int numgigs = mGigData.size();
    bs << numgigs;
    for (int i = 0; i < numgigs; i++) {
        const GigData &gd = mGigData[i];
        bs << gd.unk0;
        bs << gd.unk4;
        bs << gd.unk8;
        bs << gd.unkc;
    }
}

void TourPerformerLocal::MakeDirty() {
    MetaPerformer *pPerformer = MetaPerformer::Current();
    MILO_ASSERT(pPerformer, 0x4E);
    pPerformer->SetSyncDirty(-1, true);
}

void TourPerformerLocal::SelectVenue() {
    MILO_ASSERT(mMetaPerformer, 0x57);
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x5B);
    bool autovocalson = TheModifierMgr->IsModifierActive(mod_auto_vocals);
    Symbol curvenue = pProgress->GetVenueForCurrentGig();
    if (curvenue != gNullStr && !autovocalson) {
        mMetaPerformer->SetVenue(curvenue);
    } else
        mMetaPerformer->SelectRandomVenue();
}

void TourPerformerLocal::ClearCurrentQuest() {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x6E);
    pProgress->SetCurrentQuest("");
    MakeDirty();
}

void TourPerformerLocal::ClearCurrentQuestFilter() {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x78);
    pProgress->ClearQuestFilters();
    mQuestFilter = "";
    mFilterType = kTourSetlist_Invalid;
    MakeDirty();
}

void TourPerformerLocal::SetCurrentQuest(Symbol i_symQuest) {
    MILO_ASSERT(TheQuestMgr.HasQuest( i_symQuest ), 132);
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 135);
    pProgress->SetCurrentQuest(i_symQuest);
    MakeDirty();
}

void TourPerformerLocal::SetCurrentQuestFilter(Symbol quest, TourSetlistType ty) {
    mQuestFilter = quest;
    mFilterType = ty;
    MakeDirty();
}

void TourPerformerLocal::CompleteQuest() {
    TourPerformerImpl::CompleteQuest();
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x9B);
    TheQuestMgr.CompleteQuest(pProgress, GetCurrentQuest());
    MakeDirty();
}

void TourPerformerLocal::ChooseRandomQuestForGroupAndTier(Symbol, int) {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 166);
}

void TourPerformerLocal::
    InqSongsInFilterData(Symbol, std::map<Symbol, int> &, std::map<Symbol, int> &) {}

void TourPerformerLocal::GetRandomArtistFromMap(const std::map<Symbol, int> &, int) {}

void TourPerformerLocal::
    GetRandomQuestFilter(TourProgress *, int, const std::map<Symbol, int> &, const std::map<Symbol, int> &) {
}

void TourPerformerLocal::GetRandomFixedSetlist(TourProgress *, int, Symbol) {}

void TourPerformerLocal::ChooseQuestFilters() {}

bool TourPerformerLocal::SanityCheckFilterAgainstType(Symbol s1, Symbol s2) {
    if (TheQuestMgr.HasFixedSetlist(s1)) {
        if (s2 == random || s2 == custom)
            return 0;
    } else {
        if (s2 != random && s2 != custom)
            return 0;
    }
    return 1;
}

void TourPerformerLocal::SanityCheckQuestFilters() {
    TourProgress *pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 561);
    MILO_ASSERT(!pProgress->AreQuestFiltersEmpty(), 563);
    Symbol filt = pProgress->GetFilterForCurrentGig();
    int songct = pProgress->GetNumSongsForCurrentGig();
    GigFilter *pSecondaryFilter = nullptr;
    if (filt != gNullStr) {
        pSecondaryFilter = TheQuestMgr.GetQuestFilter(filt);
        MILO_ASSERT(pSecondaryFilter, 578);
    }
    std::vector<int> a, b;
    TheSongMgr.GetValidSongs(a, *TheBandUserMgr, b, -1, -1, true, true);
}

void TourPerformerLocal::InitializeNextGig() {}

void TourPerformerLocal::CheatCycleChallenge() {}

void TourPerformerLocal::CheatCycleSetlist() {}

BEGIN_HANDLERS(TourPerformerLocal)
    HANDLE_ACTION(select_venue, SelectVenue())
    HANDLE_ACTION(initialize_next_gig, InitializeNextGig())
    HANDLE_SUPERCLASS(TourPerformerImpl)
    HANDLE_CHECK(889)
END_HANDLERS

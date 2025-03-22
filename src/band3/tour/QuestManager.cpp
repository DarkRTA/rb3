#include "QuestManager.h"
#include "TourPerformer.h"
#include "decomp.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "tour/GigFilter.h"
#include "tour/Tour.h"
#include "tour/TourReward.h"

QuestManager TheQuestMgr;

QuestManager::QuestManager() {}

QuestManager::~QuestManager() { Cleanup(); }

void QuestManager::Cleanup() {
    for (std::map<Symbol, Quest *>::iterator it = mMapQuests.begin();
         it != mMapQuests.end();
         it++) {
        Quest *pQuest = it->second;
        MILO_ASSERT(pQuest, 39);
        delete pQuest;
    }
    mMapQuests.clear();
    for (std::map<Symbol, GigFilter *>::iterator it = mMapQuestFilters.begin();
         it != mMapQuestFilters.end();
         it++) {
        GigFilter *pQuestFilter = it->second;
        MILO_ASSERT(pQuestFilter, 49);
        delete pQuestFilter;
    }
    mMapQuestFilters.clear();
    for (std::map<Symbol, FixedSetlist *>::iterator it = mMapFixedSetlists.begin();
         it != mMapFixedSetlists.end();
         it++) {
        FixedSetlist *pFixedSetlist = it->second;
        MILO_ASSERT(pFixedSetlist, 59);
        delete pFixedSetlist;
    }
    mMapFixedSetlists.clear();
}

void QuestManager::Init(DataArray *da) {
    ConfigureQuestData(da->FindArray("quests"));
    ConfigureQuestFilterData(da->FindArray("quest_filters"));
    ConfigureFixedSetlistData(da->FindArray("tour_fixed_sets"));
}

void QuestManager::ConfigureQuestFilterData(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        GigFilter *filt = new GigFilter();
        filt->Init(da->Array(i));
        Symbol name = filt->GetName();
        if (HasQuestFilter(name)) {
            MILO_WARN("%s quest filter already exists, skipping", name);
            delete filt;
        } else
            mMapQuestFilters[name] = filt;
    }
}

#pragma push
#pragma force_active on
inline bool QuestManager::HasQuestFilter(Symbol s) const { return GetQuestFilter(s); }
#pragma pop

GigFilter *QuestManager::GetQuestFilter(Symbol s) const {
    std::map<Symbol, GigFilter *>::const_iterator it = mMapQuestFilters.find(s);
    if (it != mMapQuestFilters.end())
        return it->second;
    else
        return nullptr;
}

void QuestManager::ConfigureFixedSetlistData(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        FixedSetlist *filt = new FixedSetlist();
        filt->Init(da->Array(i));
        Symbol name = filt->GetName();
        if (HasFixedSetlist(name)) {
            MILO_WARN("%s fixed setlist already exists, skipping", name);
            delete filt;
        } else
            mMapFixedSetlists[name] = filt;
    }
}

#pragma push
#pragma force_active on
inline bool QuestManager::HasFixedSetlist(Symbol s) const { return GetFixedSetlist(s); }
#pragma pop

FixedSetlist *QuestManager::GetFixedSetlist(Symbol s) const {
    std::map<Symbol, FixedSetlist *>::const_iterator it = mMapFixedSetlists.find(s);
    if (it != mMapFixedSetlists.end())
        return it->second;
    else
        return nullptr;
}

void QuestManager::ConfigureQuestData(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        Quest *filt = new Quest(da->Array(i));
        Symbol name = filt->GetName();
        if (HasQuest(name)) {
            MILO_WARN("%s quest already exists, skipping", name);
            delete filt;
        } else
            mMapQuests[name] = filt;
    }
}

#pragma push
#pragma force_active on
inline bool QuestManager::HasQuest(Symbol s) const { return GetQuest(s); }
#pragma pop

Quest *QuestManager::GetQuest(Symbol s) const {
    std::map<Symbol, Quest *>::const_iterator it = mMapQuests.find(s);
    if (it != mMapQuests.end())
        return it->second;
    else
        return nullptr;
}

bool QuestManager::IsQuestAvailable(
    const TourProgress &progress, Symbol s1, Symbol s2, int i
) {
    Quest *pQuest = GetQuest(s1);
    MILO_ASSERT(pQuest, 0xBD);
    if (i != -1) {
        int tier = pQuest->GetTier();
        if (tier != -1 && tier != i) {
            return false;
        }
    }
    if (s2 != "") {
        if (pQuest->GetGroup() != s2) {
            return false;
        }
    }
    if (!pQuest->GetPrereqs()->IsMet(progress)) {
        return false;
    }
    return true;
}

void QuestManager::CompleteQuest(TourProgress *i_pProgress, Symbol s) {
    MILO_ASSERT(i_pProgress, 230);
    QuestJournal *pJournal = &i_pProgress->mQuests;
    MILO_ASSERT(pJournal, 234);
    pJournal->CompleteQuest(s);
    TourPerformerImpl *pTourPerformer = TheTour->m_pTourPerformer;
    MILO_ASSERT(pTourPerformer, 239);
    bool won = false;
    Quest *quest = GetQuest(s);
    if (quest) {
        won = pTourPerformer->IsQuestWon(s);
        const TourReward *reward =
            won ? quest->GetSuccessReward() : quest->GetFailureReward();
        reward->Apply(i_pProgress);
        i_pProgress->SetNumCompletedGigs(i_pProgress->GetNumCompletedGigs() + 1);
    }
    i_pProgress->SetWonQuest(won);
    i_pProgress->FinalizeNewStars();
    BandProfile *pProfile = TheProfileMgr.FindTourProgressOwner(i_pProgress);
    MILO_ASSERT(pProfile, 0x103);
    pTourPerformer->UpdateTourStats(i_pProgress);
    if (i_pProgress->IsTourComplete())
        pTourPerformer->UpdateCompleteTourStats(i_pProgress);
    TheTour->UpdateProgressWithCareerData();
    pProfile->MakeDirty();
}
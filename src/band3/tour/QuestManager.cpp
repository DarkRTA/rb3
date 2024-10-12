#include "QuestManager.h"
#include "decomp.h"
#include "os/Debug.h"
#include "tour/GigFilter.h"
#include "tour/Tour.h"

QuestManager TheQuestMgr;

QuestManager::QuestManager() { }

QuestManager::~QuestManager() { Cleanup(); }

void QuestManager::Cleanup() {
    for (std::map<Symbol, Quest*>::iterator it = mMapQuests.begin(); it != mMapQuests.end(); it++) {
        Quest* pQuest = it->second;
        MILO_ASSERT(pQuest, 39);
        delete pQuest;
    }
    mMapQuests.clear();
    for (std::map<Symbol, GigFilter*>::iterator it = mMapQuestFilters.begin(); it != mMapQuestFilters.end(); it++) {
        GigFilter* pQuestFilter = it->second;
        MILO_ASSERT(pQuestFilter, 49);
        delete pQuestFilter;
    }
    mMapQuestFilters.clear();
    for (std::map<Symbol, FixedSetlist*>::iterator it = mMapFixedSetlists.begin(); it != mMapFixedSetlists.end(); it++) {
        FixedSetlist* pFixedSetlist = it->second;
        MILO_ASSERT(pFixedSetlist, 59);
        delete pFixedSetlist;
    }
    mMapFixedSetlists.clear();
}

void QuestManager::Init(DataArray* da) {
    ConfigureQuestData(da->FindArray("quests", true));
    ConfigureQuestFilterData(da->FindArray("quest_filters", true));
    ConfigureFixedSetlistData(da->FindArray("tour_fixed_sets", true));
}

void QuestManager::ConfigureQuestFilterData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        GigFilter* filt = new GigFilter();
        filt->Init(da->Array(i));
        Symbol name = filt->GetName();
        if(HasQuestFilter(name)){
            MILO_WARN("%s quest filter already exists, skipping", name);
            delete filt;
        }
        else mMapQuestFilters[name] = filt;
    }
}

#pragma push
#pragma dont_inline on
bool hasquestfilterlol(QuestManager* q, Symbol s){
    return q->HasQuestFilter(s);
}
#pragma pop

GigFilter* QuestManager::GetQuestFilter(Symbol s) const {
    std::map<Symbol, GigFilter*>::const_iterator it = mMapQuestFilters.find(s);
    if(it != mMapQuestFilters.end()) return it->second;
    else return 0;
}

void QuestManager::ConfigureFixedSetlistData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        FixedSetlist* filt = new FixedSetlist();
        filt->Init(da->Array(i));
        Symbol name = filt->GetName();
        if(HasFixedSetlist(name)){
            MILO_WARN("%s fixed setlist already exists, skipping", name);
            delete filt;
        }
        else mMapFixedSetlists[name] = filt;
    }
}

#pragma push
#pragma dont_inline on
bool hasfixedsetlistlol(QuestManager* q, Symbol s){
    return q->HasFixedSetlist(s);
}
#pragma pop

FixedSetlist* QuestManager::GetFixedSetlist(Symbol s) const {
    std::map<Symbol, FixedSetlist*>::const_iterator it = mMapFixedSetlists.find(s);
    if(it != mMapFixedSetlists.end()) return it->second;
    else return 0;
}

void QuestManager::ConfigureQuestData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        Quest* filt = new Quest(da->Array(i));
        Symbol name = filt->GetName();
        if(HasQuest(name)){
            MILO_WARN("%s quest already exists, skipping", name);
            delete filt;
        }
        else mMapQuests[name] = filt;
    }
}

#pragma push
#pragma dont_inline on
bool hasquestlol(QuestManager* q, Symbol s){
    return q->HasQuest(s);
}
#pragma pop

Quest* QuestManager::GetQuest(Symbol s) const {
    std::map<Symbol, Quest*>::const_iterator it = mMapQuests.find(s);
    if(it != mMapQuests.end()) return it->second;
    else return 0;
}

bool QuestManager::IsQuestAvailable(const TourProgress& progress, Symbol s1, Symbol s2, int i){
    Quest* pQuest = GetQuest(s1);
    MILO_ASSERT(pQuest, 0xBD);
    if(i != -1){
        int tier = pQuest->GetTier();
        if(tier != -1 && tier != i){
            return false;
        }
    }
    else {
        if(s2 == "" || pQuest->GetGroup() == s2){
            return pQuest->GetPrereqs()->IsMet(progress);
            // if(!pQuest->GetPrereqs()->IsMet(progress)) return false;
            // else return true;
        }
        else return false;
    }
}

void QuestManager::CompleteQuest(TourProgress* i_pProgress, Symbol s) {
    MILO_ASSERT(i_pProgress, 230);
    QuestJournal* pJournal = &i_pProgress->mQuests;
    MILO_ASSERT(pJournal, 234);
    pJournal->CompleteQuest(s);
    void* pTourPerformer; // = TheTour->unk_0x24;
    MILO_ASSERT(pTourPerformer, 239);
}

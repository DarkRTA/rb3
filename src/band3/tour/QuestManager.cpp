#include "QuestManager.h"
#include "os/Debug.h"
#include "tour/GigFilter.h"
#include "tour/Tour.h"

QuestManager TheQuestMgr;

QuestManager::QuestManager() { }

QuestManager::~QuestManager() { Cleanup(); }

void QuestManager::Cleanup() {
    for (std::map<Symbol, Quest*>::iterator it = unk_0x4.begin(); it != unk_0x4.end(); it++) {
        Quest* pQuest = it->second;
        MILO_ASSERT(pQuest, 39);
        delete pQuest;
    }
    unk_0x4.clear();
    for (std::map<Symbol, GigFilter*>::iterator it = unk_0x1C.begin(); it != unk_0x1C.end(); it++) {
        GigFilter* pQuestFilter = it->second;
        MILO_ASSERT(pQuestFilter, 49);
        delete pQuestFilter;
    }
    unk_0x1C.clear();
    for (std::map<Symbol, FixedSetlist*>::iterator it = unk_0x34.begin(); it != unk_0x34.end(); it++) {
        FixedSetlist* pFixedSetlist = it->second;
        MILO_ASSERT(pFixedSetlist, 59);
        delete pFixedSetlist;
    }
    unk_0x34.clear();
}

void QuestManager::Init(DataArray* da) {
    ConfigureQuestData(da->FindArray("quests", true));
    ConfigureQuestFilterData(da->FindArray("quest_filters", true));
    ConfigureFixedSetlistData(da->FindArray("tour_fixed_sets", true));
}

void QuestManager::ConfigureQuestFilterData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        GigFilter* gf = new GigFilter;
    }
}

bool QuestManager::HasQuestFilter(Symbol s) const { return GetQuestFilter(s); }
GigFilter* QuestManager::GetQuestFilter(Symbol) const {}

void QuestManager::ConfigureFixedSetlistData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        
    }
}

bool QuestManager::HasFixedSetlist(Symbol s) const { return GetFixedSetlist(s);}
FixedSetlist* QuestManager::GetFixedSetlist(Symbol) const {}

void QuestManager::ConfigureQuestData(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        
    }
}

bool QuestManager::HasQuest(Symbol s) const { return GetQuest(s);}
Quest* QuestManager::GetQuest(Symbol) const {}

void QuestManager::CompleteQuest(TourProgress* i_pProgress, Symbol s) {
    MILO_ASSERT(i_pProgress, 230);
    QuestJournal* pJournal = &i_pProgress->mQuests;
    MILO_ASSERT(pJournal, 234);
    pJournal->CompleteQuest(s);
    void* pTourPerformer; // = TheTour->unk_0x24;
    MILO_ASSERT(pTourPerformer, 239);
}

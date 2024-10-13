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
    else return nullptr;
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
    else return nullptr;
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
    else return nullptr;
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
    if(s2 != ""){
        if (pQuest->GetGroup() != s2) {
            return false;
        }
    }
    if (!pQuest->GetPrereqs()->IsMet(progress)) {
        return false;
    }
    return true;
}

void QuestManager::CompleteQuest(TourProgress* i_pProgress, Symbol s) {
    MILO_ASSERT(i_pProgress, 230);
    QuestJournal* pJournal = &i_pProgress->mQuests;
    MILO_ASSERT(pJournal, 234);
    pJournal->CompleteQuest(s);
    void* pTourPerformer; // = TheTour->unk_0x24;
    MILO_ASSERT(pTourPerformer, 239);
}

// void __thiscall QuestManager::CompleteQuest(QuestManager *this,TourProgress *param_1,Symbol param _2)

// {
  
//   if (param_1 == (TourProgress *)0x0) {
//     pcVar1 = ::MakeString(kAssertStr,::@stringBase0,0xe6,s_i_pProgress_80ba9e36);
//     Debug::Fail((Debug *)TheDebug,pcVar1);
//   }
//   if ((QuestJournal *)(param_1 + 0x1c) == (QuestJournal *)0x0) {
//     pcVar1 = ::MakeString(kAssertStr,::@stringBase0,0xea,s_pJournal_80ba9e42);
//     Debug::Fail((Debug *)TheDebug,pcVar1);
//   }
//   local_20[0] = *(undefined4 *)param_2.mStr;
//   QuestJournal::CompleteQuest((QuestJournal *)(param_1 + 0x1c),(Symbol)local_20);
//   this_03 = *(TourPerformerImpl **)(TheTour + 0x24); - TourPerformerImpl*
//   if (this_03 == (TourPerformerImpl *)0x0) {
//     pcVar1 = ::MakeString(kAssertStr,::@stringBase0,0xef,s_pTourPerformer_80ba9e4b);
//     Debug::Fail((Debug *)TheDebug,pcVar1);
//   }
//   local_24 = *(undefined4 *)param_2.mStr;
//   iVar3 = 0;
//   this_00 = (Quest *)GetQuest(this,(Symbol)&local_24);
//   if (this_00 != (Quest *)0x0) {
//     local_28 = *(undefined4 *)param_2.mStr;
//     iVar3 = TourPerformerImpl::IsQuestWon(this_03,(Symbol)&local_28);
//     if (iVar3 == 0) {
//       this_01 = (TourReward *)Quest::GetFailureReward(this_00);
//     }
//     else {
//       this_01 = (TourReward *)Quest::GetSuccessReward(this_00);
//     }
//     TourReward::Apply(this_01,param_1);
//     iVar2 = TourProgress::GetNumCompletedGigs(param_1);
//     TourProgress::SetNumCompletedGigs(param_1,iVar2 + 1);
//   }
//   TourProgress::SetWonQuest(param_1,SUB41(iVar3,0));
//   TourProgress::FinalizeNewStars(param_1);
//   this_02 = (Profile *)ProfileMgr::FindTourProgressOwner((ProfileMgr *)TheProfileMgr,param_1);
//   if (this_02 == (Profile *)0x0) {
//     pcVar1 = ::MakeString(kAssertStr,::@stringBase0,0x103,s_pProfile_80ba9e5a);
//     Debug::Fail((Debug *)TheDebug,pcVar1);
//   }
//   TourPerformerImpl::UpdateTourStats(this_03,param_1);
//   iVar3 = TourProgress::IsTourComplete(param_1);
//   if (iVar3 != 0) {
//     TourPerformerImpl::UpdateCompleteTourStats(this_03,param_1);
//   }
//   Tour::UpdateProgressWithCareerData(TheTour);
//   Profile::MakeDirty(this_02);
//   return;
// }
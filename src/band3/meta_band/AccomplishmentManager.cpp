#include "AccomplishmentManager.h"
#include "BandProfile.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMode.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentOneShot.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/AccomplishmentTrainerCategoryConditional.h"
#include "meta_band/Award.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "stl/_algo.h"
#include "stl/_pair.h"
#include "tour/Tour.h"
#include "utl/Locale.h"
#include "utl/MakeString.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <vector>

AccomplishmentManager* TheAccomplishmentMgr;

GoalAlpaCmp::GoalAlpaCmp(){}
bool GoalAlpaCmp::operator()(Symbol s1, Symbol s2) const { return strcmp(s1.mStr, s2.mStr) >= 0; }

SongDifficultyCmp::SongDifficultyCmp(Symbol s) : mInst(s) {
    if(mInst == gNullStr) mInst = band;
}

bool SongDifficultyCmp::operator()(Symbol s1, Symbol s2) const {
    int id1 = TheSongMgr->GetSongIDFromShortName(s1, true);
    int id2 = TheSongMgr->GetSongIDFromShortName(s2, true);
    BandSongMetadata* pDataLHS = (BandSongMetadata*)TheSongMgr->Data(id1);
    MILO_ASSERT(pDataLHS, 0x4E);
    BandSongMetadata* pDataRHS = (BandSongMetadata*)TheSongMgr->Data(id2);
    MILO_ASSERT(pDataRHS, 0x50);
    float rank1 = pDataLHS->Rank(mInst);
    float rank2 = pDataRHS->Rank(mInst);
    if(rank1 == rank2) return true; // fix this line
    else return rank1 < rank2;
}

AccomplishmentManager::AccomplishmentManager() {
    MILO_ASSERT(!TheAccomplishmentMgr, 0x60);
    TheAccomplishmentMgr = this;
    SetName("acc_mgr", ObjectDir::Main());
}

AccomplishmentManager::~AccomplishmentManager(){
    Cleanup();
}

void AccomplishmentManager::Cleanup(){
    for(std::map<Symbol, Accomplishment*>::iterator it = mAccomplishments.begin(); it != mAccomplishments.end(); ++it){
        RELEASE(it->second);
    }
    mAccomplishments.clear();
    for(std::map<Symbol, AccomplishmentCategory*>::iterator it = mAccomplishmentCategory.begin(); it != mAccomplishmentCategory.end(); ++it){
        RELEASE(it->second);
    }
    mAccomplishmentCategory.clear();
    for(std::map<Symbol, std::set<Symbol>*>::iterator it = m_mapCategoryToAccomplishmentSet.begin(); it != m_mapCategoryToAccomplishmentSet.end(); ++it){
        RELEASE(it->second);
    }
    m_mapCategoryToAccomplishmentSet.clear();
    for(std::map<Symbol, std::list<Symbol>*>::iterator it = m_mapGroupToCategories.begin(); it != m_mapGroupToCategories.end(); ++it){
        RELEASE(it->second);
    }
    m_mapGroupToCategories.clear();
    for(std::map<Symbol, AccomplishmentGroup*>::iterator it = mAccomplishmentGroups.begin(); it != mAccomplishmentGroups.end(); ++it){
        RELEASE(it->second);
    }
    mAccomplishmentGroups.clear();
    for(std::map<Symbol, Award*>::iterator it = mAwards.begin(); it != mAwards.end(); ++it){
        RELEASE(it->second);
    }
    mAwards.clear();
    for(std::map<Symbol, std::vector<Symbol>*>::iterator it = unkb0.begin(); it != unkb0.end(); ++it){
        RELEASE(it->second);
    }
    unkb0.clear();
    unk80.clear();
    unk98.clear();
    unk148.clear();
    unk150.clear();
    unkc8.clear();
    m_vFanScalingData.clear();
    for(std::map<Symbol, SongSortMgr::SongFilter*>::iterator it = unk158.begin(); it != unk158.end(); ++it){
        RELEASE(it->second);
    }
    unk158.clear();
    unk170.clear();
    TheContentMgr->UnregisterCallback(this, true);
}

void AccomplishmentManager::InitializePrecachedFilters(){
    unk170.clear();
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int songid = *it;
        BandSongMetadata* pSongData = (BandSongMetadata*)TheSongMgr->Data(songid);
        MILO_ASSERT(pSongData, 200);
        for(std::map<Symbol, SongSortMgr::SongFilter*>::iterator it = unk158.begin(); it != unk158.end(); ++it){
            SongSortMgr::SongFilter* pFilter = it->second;
            Symbol key = it->first;
            MILO_ASSERT(pFilter, 0xD1);
            if(TheSongSortMgr->DoesSongMatchFilter(songid, pFilter, gNullStr)){
                int count = GetPrecachedFilterCount(key);
                SetPrecachedFilterCount(key, count + 1);
            }
        }
    }
}

void AccomplishmentManager::InitializeDiscSongs(){
    unk148.clear();
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int songid = *it;
        BandSongMetadata* pSongData = (BandSongMetadata*)TheSongMgr->Data(songid);
        MILO_ASSERT(pSongData, 0xEB);
        if(!pSongData->IsDownload()){
            unk148.push_back(TheSongMgr->GetShortNameFromSongID(songid, true));
        }
    }
    std::stable_sort(unk148.begin(), unk148.end(), SongDifficultyCmp(gNullStr));
}

void AccomplishmentManager::InitializeTourSafeDiscSongs(){
    unk150.clear();
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int songid = *it;
        BandSongMetadata* pSongData = (BandSongMetadata*)TheSongMgr->Data(songid);
        MILO_ASSERT(pSongData, 0x107);
        if(pSongData->IsDownload()) continue;
        if(!pSongData->HasPart(drum, false)) continue;
        if(!pSongData->HasPart(vocals, false)) continue;
        if(!pSongData->HasPart(bass, false)) continue;
        if(!pSongData->HasPart(guitar, false)) continue;
        if(!pSongData->HasPart(real_guitar, false)) continue;
        if(!pSongData->HasPart(real_bass, false)) continue;
        if(!pSongData->HasPart(keys, false)) continue;
        if(!pSongData->HasPart(real_keys, false)) continue;
        Symbol shortname = TheSongMgr->GetShortNameFromSongID(songid, true);
        unk150.push_back(shortname);
    }
    std::stable_sort(unk150.begin(), unk150.end(), SongDifficultyCmp(gNullStr));
}


void AccomplishmentManager::ContentDone() {
    InitializeDiscSongs();
    InitializeTourSafeDiscSongs();
    InitializePrecachedFilters();
}


void AccomplishmentManager::Init(DataArray* configure) {
    ConfigureFanValueData(configure->FindArray("fan_values", true));
    ConfigureFanScalingData(configure->FindArray("fan_scaling", true));
    ConfigureAwardData(configure->FindArray("awards", true));
    ConfigurePrecachedFilterData(configure->FindArray("precached_filters", true));
    ConfigureAccomplishmentGroupData(configure->FindArray("accomplishment_groups", true));
    ConfigureAccomplishmentCategoryData(configure->FindArray("accomplishment_categories", true));
    ConfigureAccomplishmentData(configure->FindArray("accomplishments", true));
    ConfigureAccomplishmentCategoryGroupingData();
    ConfigureAccomplishmentGroupToCategoriesData();
    ConfigureAccomplishmentRewardData(configure->FindArray("accomplishment_rewards", true));
    TheContentMgr->RegisterCallback(this, false);
}

void AccomplishmentManager::SanityCheckAwards() {
    for(std::map<Symbol, Award*>::iterator it = mAwards.begin(); it != mAwards.end(); ++it){
        Symbol key = it->first;
        Award* pAward = GetAward(key);
        MILO_ASSERT(pAward, 0x153);
        if(!pAward->IsBonus()){
            Symbol source = GetAwardSource(key);
            if(source == gNullStr){
                MILO_WARN("AWARD: %s has no source!", key.Str());
            }
        }
    }
}

void AccomplishmentManager::Poll() {
    std::vector<BandProfile*> profiles = TheProfileMgr.GetSignedInProfiles();
    for(std::vector<BandProfile*>::iterator it = profiles.begin(); it != profiles.end(); ++it){
        BandProfile* pProfile = *it;
        MILO_ASSERT(pProfile, 0x16B);
        pProfile->AccessAccomplishmentProgress()->Poll();
    }
}

Accomplishment* AccomplishmentManager::FactoryCreateAccomplishment(DataArray* arr, int idx) {
    int acctype;
    arr->FindData(accomplishment_type, acctype, true);
    Accomplishment* ret = 0;
    switch(acctype){
        case kAccomplishmentTypeUnique:
            ret = new Accomplishment(arr, idx);
            break;
        case kAccomplishmentTypeSongListConditional:
            // ret = new AccomplishmentSongListConditional(arr, idx);
            break;
        case kAccomplishmentTypeSongFilterConditional:
            // ret = new AccomplishmentSongFilterConditional(arr, idx);
            break;
        case kAccomplishmentTypeLessonSongListConditional:
            // ret = new AccomplishmentLessonSongListConditional(arr, idx);
            break;
        case kAccomplishmentTypeLessonDiscSongConditional:
            // ret = new AccomplishmentLessonDiscSongConditional(arr, idx);
            break;
        case kAccomplishmentTypePlayerConditional:
            // ret = new AccomplishmentPlayerConditional(arr, idx);
            break;
        case kAccomplishmentTypeTourConditional:
            // ret = new AccomplishmentTourConditional(arr, idx);
            break;
        case kAccomplishmentTypeTrainerListConditional:
            // ret = AccomplishmentTrainerListConditional(arr, idx);
            break;
        case kAccomplishmentTypeTrainerCategoryConditional:
            // ret = new AccomplishmentTrainerCategoryConditional(arr, idx);
            break;
        case kAccomplishmentTypeOneShot:
            // ret = new AccomplishmentOneShot(arr, idx);
            break;
        case kAccomplishmentTypeSetlist:
            // ret = new AccomplishmentSetlist(arr, idx);
            break;
        case kAccomplishmentTypeDiscSongConditional:
            // ret = new AccomplishmentDiscSongConditional(arr, idx);
            break;
        default:
            MILO_ASSERT(false, 0x1BB);
            break;
    }
    return ret;
}

void AccomplishmentManager::ConfigureFanValueData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        DataArray* pEntry = arr->Array(i);
        MILO_ASSERT(pEntry, 0x1C9);
        MILO_ASSERT(pEntry->Size() == 2, 0x1CB);
        Symbol key = pEntry->Sym(0);
        int val = pEntry->Int(1);
        if(HasFanValue(key)){
            MILO_WARN("Fan Value: %s already exists, skipping", key.Str());
        }
        else unkc8[key] = val;
    }
}

void AccomplishmentManager::ConfigureFanScalingData(DataArray* arr){
    int i8 = 0;
    int i9 = 0;
    for(int i = 1; i < arr->Size(); i++){
        DataArray* pEntry = arr->Array(i);
        MILO_ASSERT(pEntry, 0x1E0);
        MILO_ASSERT(pEntry->Size() == 2, 0x1E2);
        int i3 = pEntry->Int(0);
        int i4 = pEntry->Int(1);
        if(i3 < i9){
            MILO_WARN("Fan Scaling data point values are not in sequence: %i index.", i);
            // i4 = i8;
            // i3 = i9;
        }
        else if(i4 < i8){
            MILO_WARN("Fan Scaling data fan values are not in sequence: %i index.", i);
            // i4 = i8;
            // i3 = i9;
        }
        else {
            m_vFanScalingData.push_back(std::make_pair(i3, i4));
            i8 = i4;
            i9 = i3;
        }
        // i8 = i4;
        // i9 = i3;
    }
}
 
void AccomplishmentManager::ConfigureAccomplishmentCategoryData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        AccomplishmentCategory* pAccomplishmentCategory = new AccomplishmentCategory(arr->Array(i), i);
        MILO_ASSERT(pAccomplishmentCategory, 0x200);
        Symbol name = pAccomplishmentCategory->GetName();
        if(HasAccomplishmentCategory(name)){
            MILO_WARN("%s accomplishment category already exists, skipping", name.Str());
            delete pAccomplishmentCategory;
        }
        else {
            Symbol group = pAccomplishmentCategory->GetGroup();
            if(!HasAccomplishmentGroup(group)){
                MILO_WARN("%s accomplishment category has invalid group: %s, skipping", name.Str(), group.Str());
                delete pAccomplishmentCategory;
            }
            else {
                if(pAccomplishmentCategory->HasAward()){
                    Symbol award = pAccomplishmentCategory->GetAward();
                    if(!HasAward(award)){
                        MILO_WARN("%s accomplishment category is using unknown award: %s!", name.Str(), award.Str());
                        delete pAccomplishmentCategory;
                        continue;
                    }
                    AddAwardSource(pAccomplishmentCategory->GetAward(), pAccomplishmentCategory->GetName());
                }
                mAccomplishmentCategory[name] = pAccomplishmentCategory;
            }
        }
    }
}

void AccomplishmentManager::ConfigureAccomplishmentGroupData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        AccomplishmentGroup* pAccomplishmentGroup = new AccomplishmentGroup(arr->Array(i), i);
        MILO_ASSERT(pAccomplishmentGroup, 0x22A);
        Symbol name = pAccomplishmentGroup->GetName();
        if(HasAccomplishmentGroup(name)){
            MILO_WARN("%s accomplishment category already exists, skipping", name.Str());
            delete pAccomplishmentGroup;
        }
        else {
            if(pAccomplishmentGroup->HasAward()){
                Symbol award = pAccomplishmentGroup->GetAward();
                if(!HasAward(award)){
                    MILO_WARN("%s accomplishment group is using unknown award: %s!", name.Str(), award.Str());
                    delete pAccomplishmentGroup;
                    continue;
                }
                AddAwardSource(pAccomplishmentGroup->GetAward(), pAccomplishmentGroup->GetName());
            }
            mAccomplishmentGroups[name] = pAccomplishmentGroup;
        }
    }
}

void AccomplishmentManager::ConfigureAwardData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        Award* pAward = new Award(arr->Array(i), i);
        MILO_ASSERT(pAward, 0x24C);
        Symbol name = pAward->GetName();
        if(HasAward(name)){
            MILO_WARN("%s award already exists, skipping", name.Str());
            delete pAward;
        }
        else {
            mAwards[name] = pAward;
        }
    }
}

void AccomplishmentManager::ConfigureAccomplishmentData(DataArray* arr){
    for(int i = 1; i < arr->Size(); i++){
        Accomplishment* pAccomplishment = FactoryCreateAccomplishment(arr->Array(i), i);
        MILO_ASSERT(pAccomplishment, 0x261);
        Symbol name = pAccomplishment->GetName();
        if(HasAccomplishment(name)){
            MILO_WARN("%s accomplishment already exists, skipping", name.Str());
            delete pAccomplishment;
        }
        else {
            Symbol cat = pAccomplishment->GetCategory();
            if(!HasAccomplishmentCategory(cat)){
                MILO_WARN("%s accomplishment is using unknown category: %s", name.Str(), cat.Str());
                delete pAccomplishment;
            }
            else {
                if(pAccomplishment->GetDynamicPrereqsFilter() != gNullStr && pAccomplishment->GetDynamicPrereqsNumSongs() < 0){
                    MILO_WARN("%s accomplishment is using using dynamic prereq filter but has no song count!", name.Str());
                    delete pAccomplishment;
                }
                else {
                    if(pAccomplishment->HasAward()){
                        Symbol award = pAccomplishment->GetAward();
                        if(!HasAward(award)){
                            MILO_WARN("%s accomplishment is using unknown award: %s!", name.Str(), award.Str());
                            delete pAccomplishment;
                            continue;
                        }
                        AddAwardSource(pAccomplishment->GetAward(), pAccomplishment->GetName());
                    }
                    mAccomplishments[name] = pAccomplishment;
                }
            }
        }
    }
}

void AccomplishmentManager::ConfigureAccomplishmentCategoryGroupingData(){
    MILO_ASSERT(m_mapCategoryToAccomplishmentSet.empty(), 0x28F);
    for(std::map<Symbol, Accomplishment*>::iterator it = mAccomplishments.begin(); it != mAccomplishments.end(); ++it){
        Accomplishment* pAccomplishment = it->second;
        MILO_ASSERT(pAccomplishment, 0x297);
        Symbol cat = pAccomplishment->GetCategory();
        Symbol name = pAccomplishment->GetName();
        std::set<Symbol>* symset = GetAccomplishmentSetForCategory(cat);
        if(!symset){
            symset = new std::set<Symbol>();
            m_mapCategoryToAccomplishmentSet[name] = symset;
        }
        symset->insert(cat);
    }
}

void AccomplishmentManager::ConfigureAccomplishmentGroupToCategoriesData(){
    MILO_ASSERT(m_mapGroupToCategories.empty(), 0x2AB);
    for(std::map<Symbol, AccomplishmentCategory*>::iterator it = mAccomplishmentCategory.begin(); it != mAccomplishmentCategory.end(); ++it){
        AccomplishmentCategory* pCategory = it->second;
        MILO_ASSERT(pCategory, 0x2B3);
        Symbol name = pCategory->GetName();
        Symbol group = pCategory->GetGroup();
        std::list<Symbol>* symlist = GetCategoryListForGroup(group);
        if(!symlist){
            symlist = new std::list<Symbol>();
            m_mapGroupToCategories[name] = symlist;
        }
        symlist->push_back(group);
    }
}

void AccomplishmentManager::ConfigurePrecachedFilterData(DataArray* arr){

}

void AccomplishmentManager::ConfigureAccomplishmentRewardData(DataArray* arr){
    DataArray* pLeaderboardThresholds = arr->Array(1);
    for(int i = 0; i < 4; i++){
        MILO_ASSERT(pLeaderboardThresholds->Array(i+1)->Int(0) == i, 0x2EF);
        unk118[i] = pLeaderboardThresholds->Array(i+1)->Int(1);
    }
    DataArray* pIconThresholds = arr->Array(2);
    for(int i = 0; i < 4; i++){
        MILO_ASSERT(pIconThresholds->Array( i + 1 )->Int( 0 ) == i, 0x2F6);
        unk128[i] = pIconThresholds->Array(i+1)->Int(1);
    }
}

std::list<Symbol>* AccomplishmentManager::GetCategoryListForGroup(Symbol s) const {
    std::map<Symbol, std::list<Symbol>*>::const_iterator it = m_mapGroupToCategories.find(s);
    if(it != m_mapGroupToCategories.end()) return it->second;
    else return nullptr;
}

std::set<Symbol>* AccomplishmentManager::GetAccomplishmentSetForCategory(Symbol s) const {
    std::map<Symbol, std::set<Symbol>*>::const_iterator it = m_mapCategoryToAccomplishmentSet.find(s);
    if(it != m_mapCategoryToAccomplishmentSet.end()) return it->second;
    else return nullptr;
}

int AccomplishmentManager::GetNumAccomplishmentsInCategory(Symbol s) const {
    int num = 0;
    std::set<Symbol>* symset = GetAccomplishmentSetForCategory(s);
    if(symset){
        for(std::set<Symbol>::const_iterator it = symset->begin(); it != symset->end(); ++it){
            if(IsAvailableToView(*it)) num++;
        }
    }
    return num;
}

int AccomplishmentManager::GetNumAccomplishmentsInGroup(Symbol i_symGroup) const {
    MILO_ASSERT(i_symGroup != gNullStr, 0x32C);
    std::list<Symbol>* pCategoryList = GetCategoryListForGroup(i_symGroup);
    MILO_ASSERT(pCategoryList, 0x32F);
    int num = 0;
    for(std::list<Symbol>::const_iterator it = pCategoryList->begin(); it != pCategoryList->end(); ++it){
        num += GetNumAccomplishmentsInCategory(*it);
    }
    return num;
}

bool AccomplishmentManager::HasFanValue(Symbol s){
    return unkc8.find(s) != unkc8.end();
}

int AccomplishmentManager::GetMetaScoreValue(Symbol s){
    std::map<Symbol, int>::iterator it = unkc8.find(s);
    if(it != unkc8.end()) return it->second;
    else return 0;
}

bool AccomplishmentManager::HasAccomplishmentCategory(Symbol s) const {
    return mAccomplishmentCategory.find(s) != mAccomplishmentCategory.end();
}

AccomplishmentCategory* AccomplishmentManager::GetAccomplishmentCategory(Symbol s) const {
    std::map<Symbol, AccomplishmentCategory*>::const_iterator it = mAccomplishmentCategory.find(s);
    if(it != mAccomplishmentCategory.end()) return it->second;
    else return nullptr;
}

bool AccomplishmentManager::HasAccomplishmentGroup(Symbol s) const {
    return mAccomplishmentGroups.find(s) != mAccomplishmentGroups.end();
}

AccomplishmentGroup* AccomplishmentManager::GetAccomplishmentGroup(Symbol s) const {
    std::map<Symbol, AccomplishmentGroup*>::const_iterator it = mAccomplishmentGroups.find(s);
    if(it != mAccomplishmentGroups.end()) return it->second;
    else return nullptr;
}

int AccomplishmentManager::GetPrecachedFilterCount(Symbol s) const {
    std::map<Symbol, int>::const_iterator it = unk170.find(s);
    if(it != unk170.end()) return it->second;
    else return 0;
}

void AccomplishmentManager::SetPrecachedFilterCount(Symbol s, int i){
    unk170[s] = i;
}

SongSortMgr::SongFilter* AccomplishmentManager::GetPrecachedFilter(Symbol s) const {
    std::map<Symbol, SongSortMgr::SongFilter*>::const_iterator it = unk158.find(s);
    if(it != unk158.end()) return it->second;
    else return nullptr;
}

bool AccomplishmentManager::HasAward(Symbol s) const {
    return mAwards.find(s) != mAwards.end();
}

Award* AccomplishmentManager::GetAward(Symbol s) const {
    std::map<Symbol, Award*>::const_iterator it = mAwards.find(s);
    if(it != mAwards.end()) return it->second;
    else return nullptr;
}

Symbol AccomplishmentManager::GetAwardSource(Symbol s) const {
    std::map<Symbol, Symbol>::const_iterator it = unk98.find(s);
    if(it != unk98.end()) return it->second;
    else return gNullStr;
}

std::vector<Symbol>* AccomplishmentManager::GetAwardSourceList(Symbol s) const {
    std::map<Symbol, std::vector<Symbol>*>::const_iterator it = unkb0.find(s);
    if(it != unkb0.end()) return it->second;
    else return nullptr;
}

void AccomplishmentManager::AddAwardSource(Symbol s1, Symbol s2){
    Symbol src = GetAwardSource(s1);
    if(src != gNullStr){
        std::vector<Symbol>* srclist = GetAwardSourceList(s1);
        if(!srclist){
            srclist = new std::vector<Symbol>();
            srclist->push_back(src);
            unkb0[s1] = srclist;
        }
        srclist->push_back(s2);
        unk98[s1] = awardsource_multiple;
    }
    else unk98[s1] = s2;
}

bool AccomplishmentManager::DoesAssetHaveSource(Symbol s) const {
    std::vector<Symbol> srclist;
    return InqAssetSourceList(s, srclist);
}

bool AccomplishmentManager::InqAssetSourceList(Symbol s, std::vector<Symbol>& o_rSourceList) const {
    MILO_ASSERT(o_rSourceList.empty(), 0x41C);
    Symbol award = GetAssetAward(s);
    if(award == gNullStr) return false;
    else {
        Symbol src = GetAwardSource(award);
        if(src == awardsource_multiple){
            std::vector<Symbol>* pSourceList = GetAwardSourceList(award);
            MILO_ASSERT(pSourceList, 0x42B);
            o_rSourceList = *pSourceList;
        }
        else if(src != gNullStr) o_rSourceList.push_back(src);
        else o_rSourceList.push_back(award);
        return !o_rSourceList.empty();
    }
}

Symbol AccomplishmentManager::GetAssetAward(Symbol s) const {
    std::map<Symbol, Symbol>::const_iterator it = unk80.find(s);
    if(it != unk80.end()) return it->second;
    else return gNullStr;
}

void AccomplishmentManager::AddAssetAward(Symbol s1, Symbol s2){
    if(GetAssetAward(s1) != gNullStr) MILO_WARN("Asset:%s is earned by multiple sources!", s1.Str());
    else unk80[s1] = s2;
}

String AccomplishmentManager::GetHintStringForSource(Symbol s) const {
    String ret;
    if(HasAccomplishment(s)){
        ret = MakeString(Localize(asset_hint_goal, 0), Localize(s, 0));
    }
    else if(HasAccomplishmentCategory(s)){
        ret = MakeString(Localize(asset_hint_goalcategory, 0), Localize(s, 0));
    }
    else if(HasAccomplishmentGroup(s)){
        ret = MakeString(Localize(asset_hint_goalgroup, 0), Localize(s, 0)); 
    }
    else if(TheCampaign->HasCampaignLevel(s)){
        ret = MakeString(Localize(asset_hint_campaignlevel, 0), Localize(s, 0));
    }
    else if(TheAccomplishmentMgr->HasAward(s)){
        Award* pAward = TheAccomplishmentMgr->GetAward(s);
        MILO_ASSERT(pAward, 0x473);
        ret = MakeString(Localize(asset_hint_award, 0), Localize(pAward->GetDisplayName(), 0));
    }
    else MILO_ASSERT(false, 0x479);
    return ret;
}

void AccomplishmentManager::UpdateAssetHintLabel(Symbol s, UILabel* i_pLabel){
    MILO_ASSERT(TheCampaign, 0x482);
    MILO_ASSERT(i_pLabel, 0x483);
    std::vector<Symbol> srclist;
    bool hasSource = InqAssetSourceList(s, srclist);
    MILO_ASSERT(hasSource, 0x487);
    String str;
    for(std::vector<Symbol>::iterator it = srclist.begin(); it != srclist.end(); ++it){
        String srcstr = GetHintStringForSource(*it);
        if(str.empty()) str = srcstr;
        else str = MakeString(Localize(career_asset_or, 0), str.c_str(), srcstr.c_str());
    }
    i_pLabel->SetTokenFmt(career_asset_hint, str);
}

bool AccomplishmentManager::HasAccomplishment(Symbol s) const {
    return mAccomplishments.find(s) != mAccomplishments.end();
}

Accomplishment* AccomplishmentManager::GetAccomplishment(Symbol s) const {
    std::map<Symbol, Accomplishment*>::const_iterator it = mAccomplishments.find(s);
    if(it != mAccomplishments.end()) return it->second;
    else return nullptr;
}

DataNode AccomplishmentManager::OnEarnAccomplishment(const DataArray* arr){
    Hmx::Object* o = arr->GetObj(2);
    Symbol sym = arr->Sym(3);
    LocalBandUser* user = dynamic_cast<LocalBandUser*>(o);
    if(user) EarnAccomplishment(user, sym);
    else {
        BandProfile* pf = dynamic_cast<BandProfile*>(o);
        EarnAccomplishment(pf, sym);
    }
    return 0;
}

void AccomplishmentManager::EarnAccomplishment(LocalBandUser* u, Symbol s){
    BandProfile* pf = TheProfileMgr.GetProfileForUser(u);
    EarnAccomplishment(pf, s);
}

void AccomplishmentManager::EarnAccomplishment(BandProfile* p, Symbol s){
    if(!HasAccomplishment(s)){
        MILO_WARN("Accomplishment: %s does not exist.", s.Str());
    }
    else {
        Accomplishment* pAccomplishment = GetAccomplishment(s);
        MILO_ASSERT(pAccomplishment, 0x4E0);
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x4E4);
        if(!IsAvailableToEarn(s)) return;
        if(pPerformer->IsNoFailActive() && !pAccomplishment->CanBeEarnedWithNoFail()) return;
        EarnAccomplishmentForProfile(p, s);
    }
}

void AccomplishmentManager::EarnAccomplishmentForProfile(BandProfile* p, Symbol s){
    if(p){
        p->EarnAccomplishment(s);
        LocalBandUser* pProfileUser = p->GetLocalBandUser();
        MILO_ASSERT(pProfileUser, 0x50D);
        Accomplishment* pAccomplishment = GetAccomplishment(s);
        MILO_ASSERT(pAccomplishment, 0x510);
        int id = pAccomplishment->GetContextID();
        if(id != -1){
            // TheAchievements->Submit(pProfileUser, s, id);
        }
    }
}

void AccomplishmentManager::UpdateTourPlayedForAllParticipants(Symbol s){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalBandUsers(&users, 0x88A);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x526);
            BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
            if(p){
                AccomplishmentProgress* prog = p->AccessAccomplishmentProgress();
                prog->UpdateTourPlayed(s);
            }
        }
        BandProfile* p = TheTour->GetProfile();
        if(p){
            AccomplishmentProgress* prog = p->AccessAccomplishmentProgress();
            prog->UpdateTourPlayed(s);
        }
        if(IsLeaderLocal()){
            UpdatePlayedTourForAllRemoteParticipants(s);
        }
    }
}

void AccomplishmentManager::UpdateMostStarsForAllParticipants(Symbol s, int i){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalBandUsers(&users, 0x88A);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x54C);
            BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
            if(p){
                AccomplishmentProgress* prog = p->AccessAccomplishmentProgress();
                prog->UpdateMostStars(s, i);
            }
        }
        BandProfile* p = TheTour->GetProfile();
        if(p){
            AccomplishmentProgress* prog = p->AccessAccomplishmentProgress();
            prog->UpdateMostStars(s, i);
        }
        if(IsLeaderLocal()){
            UpdateMostStarsForAllRemoteParticipants(s, i);
        }
    }
}

void AccomplishmentManager::EarnAccomplishmentForAllParticipants(Symbol s){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalBandUsers(&users, 0x88A);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x586);
            BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
            EarnAccomplishmentForProfile(p, s);
        }
        if(IsLeaderLocal()){
            EarnAccomplishmentForAllRemoteParticipants(s);
        }
    }
}

void AccomplishmentManager::CheckForIncrementalProgressForUserGoal(Symbol s1, Symbol s2, LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x5CF);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s1);
    MILO_ASSERT(pAccomplishment, 0x5D3);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0x5D6);
    AccomplishmentProgress* pProgress = pProfile->AccessAccomplishmentProgress();
    int i24 = 0;
    int i28 = 0;
    pAccomplishment->InqProgressValues(pProfile, i24, i28);
    int val = pProgress->GetCurrentValue(s1);
    if(i24 > val){
        TheAccomplishmentMgr->AddGoalProgressionInfo(s1, i_pUser->ProfileName(), s2, i28 - i24);
    }
}

void AccomplishmentManager::CheckForFinishedTourAccomplishments(){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalBandUsers(&users, 0x88A);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x639);
            BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
            if(p) CheckForFinishedTourAccomplishmentsForProfile(p);
        }
        BandProfile* p = TheTour->GetProfile();
        if(p) CheckForFinishedTourAccomplishmentsForProfile(p);
    }
}

void AccomplishmentManager::CheckForFinishedTourAccomplishmentsForUser(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x679);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0x67B);
    CheckForFinishedTourAccomplishmentsForProfile(pProfile);
}

void AccomplishmentManager::CheckForFinishedAccomplishmentsForUser(Symbol s, LocalBandUser* u){
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(u);
    MILO_ASSERT(pProfile, 0x684);
    AccomplishmentProgress* pProgress = pProfile->AccessAccomplishmentProgress();
    for(std::map<Symbol, Accomplishment*>::iterator it = mAccomplishments.begin(); it != mAccomplishments.end(); ++it){
        Symbol key = it->first;
        if(!pProgress->IsAccomplished(key)){
            Accomplishment* pAccomplishment = it->second;
            MILO_ASSERT(pAccomplishment, 0x694);
            if(pAccomplishment->GetType() == kAccomplishmentTypeTrainerListConditional) continue;
            if(pAccomplishment->GetType() == kAccomplishmentTypeTrainerCategoryConditional) continue;
            if(pAccomplishment->GetType() == kAccomplishmentTypeLessonDiscSongConditional) continue;
            if(pAccomplishment->GetType() == kAccomplishmentTypeLessonSongListConditional) continue;
            if(pAccomplishment->GetType() == kAccomplishmentTypeTourConditional) continue;
            if(pAccomplishment->GetType() == kAccomplishmentTypeUnique) continue;
            if(IsAvailableToEarn(key)){
                if(!pAccomplishment->IsRelevantForSong(s)) continue;
                if(!pAccomplishment->IsUserOnValidScoreType(u)) continue;
                if(!pAccomplishment->IsFulfilled(pProfile)) continue;
                EarnAccomplishment(u, key);
            }
        }
    }
}

int AccomplishmentManager::GetLeaderboardHardcoreStatus(int n) const {
    int ret = 0;
    for(int i = 0; i < 4; i++){
        if(n < unk118[i]) break;
        else ret = i;
    }
    return ret;
}

int AccomplishmentManager::GetIconHardCoreStatus(int n) const {
    int ret = 0;
    for(int i = 0; i < 4; i++){
        if(n < unk128[i]) break;
        else ret = i;
    }
    return ret;
}

void AccomplishmentManager::HandlePreSongCompleted(Symbol s){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalParticipants(users);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            if(pUser->CanSaveData()){
                HandlePreSongCompletedForUser(s, pUser);
            }
        }
    }
}

void AccomplishmentManager::HandleSetlistCompleted(Symbol s, bool b, Difficulty diff, int i){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalParticipants(users);
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            if(pUser->CanSaveData()){
                HandleSetlistCompletedForUser(s, b, pUser, diff, i);
            }
        }
    }
}

void AccomplishmentManager::HandleSongCompleted(Symbol s, Difficulty diff){
    if(TheBandUserMgr){
        std::vector<LocalBandUser*> users;
        TheBandUserMgr->GetLocalParticipants(users);
        bool multiplayer = users.size() > 1;
        for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            LocalBandUser* pUser = *it;
            if(pUser->CanSaveData()){
                if(multiplayer){
                    EarnAccomplishment(pUser, acc_multiplayersession);
                }
                HandleSongCompletedForUser(s, pUser, diff);
            }
        }
    }
}

void AccomplishmentManager::HandlePreSongCompletedForUser(Symbol s, LocalBandUser* u){
    if(TheGameMode){
        if(!TheGameMode->Property("update_leaderboards", true)->Int()) return;
    }
    Symbol goal = TheCampaign->GetCurrentGoal();
    if(goal != gNullStr){
        BandProfile* pProfile = TheProfileMgr.GetProfileForUser(u);
        MILO_ASSERT(pProfile, 0x75C);
        AccomplishmentProgress* prog = pProfile->AccessAccomplishmentProgress();
        prog->ClearStepTrackingMap();
        InitializeSongIncrementalDataForUserGoal(goal, u);
    }
}

void AccomplishmentManager::HandleSongCompletedForUser(Symbol s, LocalBandUser* u, Difficulty diff){
    if(TheGameMode){
        if(!TheGameMode->Property("update_leaderboards", true)->Int()) return;
    }
    if(u->unkc){
        UpdateSongStatusFlagsForUser(s, u, diff);
        UpdateMiscellaneousSongDataForUser(s, u);
        CheckForOneShotAccomplishments(s, u, diff);
        CheckForFinishedAccomplishmentsForUser(s, u);
        Symbol goal = TheCampaign->GetCurrentGoal();
        if(goal != gNullStr){
            CheckForIncrementalProgressForUserGoal(goal, s, u);
        }
    }
}

void AccomplishmentManager::InitializeSongIncrementalDataForUserGoal(Symbol s, LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0x81B);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0x81E);
    AccomplishmentProgress* prog = pProfile->AccessAccomplishmentProgress();
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0x823);
    int i1c = 0;
    int i20 = 0;
    pAccomplishment->InqProgressValues(pProfile, i1c, i20);
    prog->SetCurrentValue(s, i1c);
}

int AccomplishmentManager::GetNumAccomplishments() const {
    int num = 0;
    for(std::map<Symbol, Accomplishment*>::const_iterator it = mAccomplishments.begin(); it != mAccomplishments.end(); ++it){
        if(IsAvailableToView(it->first)) num++;
    }
    return num;
}

bool AccomplishmentManager::HasCompletedAccomplishment(LocalBandUser* u, Symbol s) const {
    BandProfile* p = TheProfileMgr.GetProfileForUser(u);
    if(p){
        AccomplishmentProgress* prog = p->GetAccomplishmentProgress();
        return prog->IsAccomplished(s);
    }
    else return false;
}

int AccomplishmentManager::GetNumCompletedAccomplishments(LocalBandUser* u) const {
    int ret = 0;
    BandProfile* p = TheProfileMgr.GetProfileForUser(u);
    if(p){
        AccomplishmentProgress* prog = p->GetAccomplishmentProgress();
        ret = prog->GetNumCompleted();
    }
    return ret;
}

bool AccomplishmentManager::HasNewAwards() const {
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalBandUsers(&users, 0x802);
    for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        LocalBandUser* pUser = *it;
        MILO_ASSERT(pUser, 0x907);
        BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
        if(p && p->HasValidSaveData() && pUser->CanSaveData()){
            AccomplishmentProgress* prog = p->GetAccomplishmentProgress();
            if(prog->HasNewAwards()) return true;
        }
    }
    return false;
}

LocalBandUser* AccomplishmentManager::GetUserForFirstNewAward(){
    std::vector<LocalBandUser*> users;
    TheBandUserMgr->GetLocalBandUsers(&users, 0x802);
    for(std::vector<LocalBandUser*>::iterator it = users.begin(); it != users.end(); ++it){
        LocalBandUser* pUser = *it;
        MILO_ASSERT(pUser, 0x923);
        BandProfile* p = TheProfileMgr.GetProfileForUser(pUser);
        if(p){
            AccomplishmentProgress* prog = p->GetAccomplishmentProgress();
            if(prog->HasNewAwards()) return pUser;
        }
    }
    MILO_ASSERT(false, 0x931);
    return nullptr;
}

Symbol AccomplishmentManager::GetReasonForFirstNewAward(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x938);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0x93B);
    AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
    if(prog->HasNewAwards()) return prog->GetFirstNewAwardReason();
    else {
        MILO_ASSERT(false, 0x946);
        Symbol ret = "";
        return ret;
    }
}
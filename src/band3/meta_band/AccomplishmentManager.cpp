#include "AccomplishmentManager.h"
#include "AccomplishmentProgress.h"
#include "BandProfile.h"
#include "Campaign.h"
#include "bandobj/BandCharacter.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMode.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentOneShot.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/AccomplishmentTrainerCategoryConditional.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/Award.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/Utl.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
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
    mAssetToAward.clear();
    mAwardToSource.clear();
    mDiscSongs.clear();
    mTourSafeDiscSongs.clear();
    mFanValues.clear();
    m_vFanScalingData.clear();
    for(std::map<Symbol, SongSortMgr::SongFilter*>::iterator it = mPrecachedFilters.begin(); it != mPrecachedFilters.end(); ++it){
        RELEASE(it->second);
    }
    mPrecachedFilters.clear();
    mPrecachedFilterCounts.clear();
    TheContentMgr->UnregisterCallback(this, true);
}

void AccomplishmentManager::InitializePrecachedFilters(){
    mPrecachedFilterCounts.clear();
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int songid = *it;
        BandSongMetadata* pSongData = (BandSongMetadata*)TheSongMgr->Data(songid);
        MILO_ASSERT(pSongData, 200);
        for(std::map<Symbol, SongSortMgr::SongFilter*>::iterator it = mPrecachedFilters.begin(); it != mPrecachedFilters.end(); ++it){
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
    mDiscSongs.clear();
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int songid = *it;
        BandSongMetadata* pSongData = (BandSongMetadata*)TheSongMgr->Data(songid);
        MILO_ASSERT(pSongData, 0xEB);
        if(!pSongData->IsDownload()){
            mDiscSongs.push_back(TheSongMgr->GetShortNameFromSongID(songid, true));
        }
    }
    std::stable_sort(mDiscSongs.begin(), mDiscSongs.end(), SongDifficultyCmp(gNullStr));
}

void AccomplishmentManager::InitializeTourSafeDiscSongs(){
    mTourSafeDiscSongs.clear();
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
        mTourSafeDiscSongs.push_back(shortname);
    }
    std::stable_sort(mTourSafeDiscSongs.begin(), mTourSafeDiscSongs.end(), SongDifficultyCmp(gNullStr));
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
        else mFanValues[key] = val;
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

DECOMP_FORCEACTIVE(AccomplishmentManager, "pDataArray", "%s precached filter already exists, skipping")

void AccomplishmentManager::ConfigurePrecachedFilterData(DataArray* arr){

}

void AccomplishmentManager::ConfigureAccomplishmentRewardData(DataArray* arr){
    DataArray* pLeaderboardThresholds = arr->Array(1);
    for(int i = 0; i < 4; i++){
        MILO_ASSERT(pLeaderboardThresholds->Array(i+1)->Int(0) == i, 0x2EF);
        mAccomplishmentRewardLeaderboardThresholds[i] = pLeaderboardThresholds->Array(i+1)->Int(1);
    }
    DataArray* pIconThresholds = arr->Array(2);
    for(int i = 0; i < 4; i++){
        MILO_ASSERT(pIconThresholds->Array( i + 1 )->Int( 0 ) == i, 0x2F6);
        mAccomplishmentRewardIconThresholds[i] = pIconThresholds->Array(i+1)->Int(1);
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

DECOMP_FORCEACTIVE(AccomplishmentManager, "!m_vFanScalingData.empty()", "iNextPointValue > iLastPointValue", "i_iPointValue >= iLastPointValue", "iNextFanValue > iLastFanValue")

bool AccomplishmentManager::HasFanValue(Symbol s){
    return mFanValues.find(s) != mFanValues.end();
}

int AccomplishmentManager::GetMetaScoreValue(Symbol s){
    std::map<Symbol, int>::iterator it = mFanValues.find(s);
    if(it != mFanValues.end()) return it->second;
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
    std::map<Symbol, int>::const_iterator it = mPrecachedFilterCounts.find(s);
    if(it != mPrecachedFilterCounts.end()) return it->second;
    else return 0;
}

void AccomplishmentManager::SetPrecachedFilterCount(Symbol s, int i){
    mPrecachedFilterCounts[s] = i;
}

SongSortMgr::SongFilter* AccomplishmentManager::GetPrecachedFilter(Symbol s) const {
    std::map<Symbol, SongSortMgr::SongFilter*>::const_iterator it = mPrecachedFilters.find(s);
    if(it != mPrecachedFilters.end()) return it->second;
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
    std::map<Symbol, Symbol>::const_iterator it = mAwardToSource.find(s);
    if(it != mAwardToSource.end()) return it->second;
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
        mAwardToSource[s1] = awardsource_multiple;
    }
    else mAwardToSource[s1] = s2;
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
    std::map<Symbol, Symbol>::const_iterator it = mAssetToAward.find(s);
    if(it != mAssetToAward.end()) return it->second;
    else return gNullStr;
}

void AccomplishmentManager::AddAssetAward(Symbol s1, Symbol s2){
    if(GetAssetAward(s1) != gNullStr) MILO_WARN("Asset:%s is earned by multiple sources!", s1.Str());
    else mAssetToAward[s1] = s2;
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
        if(n < mAccomplishmentRewardLeaderboardThresholds[i]) break;
        else ret = i;
    }
    return ret;
}

int AccomplishmentManager::GetIconHardCoreStatus(int n) const {
    int ret = 0;
    for(int i = 0; i < 4; i++){
        if(n < mAccomplishmentRewardIconThresholds[i]) break;
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

Symbol AccomplishmentManager::GetNameForFirstNewAward(LocalBandUser* i_pUser) const {
    MILO_ASSERT(i_pUser, 0x950);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0x953);
    AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
    if(prog->HasNewAwards()) return prog->GetFirstNewAward();
    else {
        MILO_ASSERT(false, 0x95E);
        Symbol ret = "";
        return ret;
    }
}

Symbol AccomplishmentManager::GetAwardDescription(Symbol s) const {
    if(s != ""){
        Award* pAward = GetAward(s);
        MILO_ASSERT(pAward, 0x96C);
        return pAward->GetDescription();
    }
    else {
        MILO_ASSERT(false, 0x972);
        return "";
    }
}

Symbol AccomplishmentManager::GetAwardNameDisplay(Symbol s) const {
    Symbol ret(gNullStr);
    if(s != ""){
        Award* pAward = GetAward(s);
        MILO_ASSERT(pAward, 0x980);
        ret = pAward->GetDisplayName();
    }
    else {
        MILO_ASSERT(false, 0x986);
    }
    return ret;
}

void AccomplishmentManager::UpdateReasonLabelForAward(Symbol s, UILabel* i_pLabel){
    MILO_ASSERT(i_pLabel, 0x98F);
    if(HasAccomplishment(s)){
        i_pLabel->SetTokenFmt(DataArrayPtr(campaign_award_earned_by_goal, s));
    }
    else if(HasAccomplishmentCategory(s)){
        i_pLabel->SetTokenFmt(DataArrayPtr(campaign_award_earned_by_category, s));
    }
    else if(HasAccomplishmentGroup(s)){
        i_pLabel->SetTokenFmt(DataArrayPtr(campaign_award_earned_by_group, s));
    }
    else if(TheCampaign->HasCampaignLevel(s)){
        i_pLabel->SetTokenFmt(DataArrayPtr(campaign_award_earned_by_level, s));
    }
    else i_pLabel->SetTextToken(s);
}

bool AccomplishmentManager::CanEquipAward(LocalBandUser* i_pUser, Symbol symAward) const {
    MILO_ASSERT(i_pUser, 0x9B0);
    MILO_ASSERT(symAward != gNullStr, 0x9B1);
    BandCharacter* loc = i_pUser->GetCharLocal();
    if(!loc) return false;
    else {
        Award* pAward = GetAward(symAward);
        MILO_ASSERT(pAward, 0x9BC);
        if(pAward->HasAssets()) return true;
        else return false;
    }
}

void AccomplishmentManager::EquipAward(LocalBandUser* i_pUser, Symbol symAward){
    MILO_ASSERT(i_pUser, 0x9C9);
    MILO_ASSERT(symAward != gNullStr, 0x9CA);
    Award* pAward = GetAward(symAward);
    MILO_ASSERT(pAward, 0x9CD);
    std::vector<Symbol> assets;
    bool hasassets = pAward->InqAssets(assets);
    if(!hasassets) MILO_ASSERT(false, 0x9D2);
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x9D6);
    pAssetMgr->EquipAssets(i_pUser, assets);
}

bool AccomplishmentManager::HasAwardIcon(Symbol s) const {
    if(s != ""){
        Award* pAward = GetAward(s);
        MILO_ASSERT(pAward, 0x9E1);
        return pAward->HasIconArt();
    }
    else return false;
}

String AccomplishmentManager::GetAwardIcon(Symbol s) const {
    String ret;
    if(s != ""){
        Award* pAward = GetAward(s);
        MILO_ASSERT(pAward, 0x9F0);
        ret = MakeString("ui/accomplishments/award_art/%s_keep.png", pAward->GetIconArt().Str());
    }
    else MILO_ASSERT(false, 0x9F9);
    return ret;
}

void AccomplishmentManager::ClearFirstNewAward(LocalBandUser* i_pUser){
    MILO_ASSERT(i_pUser, 0xA02);
    BandProfile* pProfile = TheProfileMgr.GetProfileForUser(i_pUser);
    MILO_ASSERT(pProfile, 0xA05);
    pProfile->AccessAccomplishmentProgress()->ClearFirstNewAward();
}

Symbol AccomplishmentManager::GetNameForFirstNewRewardVignette() const {
    BandProfile* pProfile = TheProfileMgr.GetPrimaryProfile();
    MILO_ASSERT(pProfile, 0xA31);
    AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
    if(prog->HasNewRewardVignettes()) return prog->GetFirstNewRewardVignette();
    else {
        MILO_ASSERT(false, 0xA3B);
        return "";
    }
}

void AccomplishmentManager::ClearFirstNewRewardVignette(){
    BandProfile* pProfile = TheProfileMgr.GetPrimaryProfile();
    MILO_ASSERT(pProfile, 0xA46);
    pProfile->AccessAccomplishmentProgress()->ClearFirstNewRewardVignette();
}

bool AccomplishmentManager::HasNewRewardVignetteFestival() const {
    if(MetaPerformer::Current()->GetVenueClass() == festival){
        BandProfile* p = TheProfileMgr.GetPrimaryProfile();
        if(p && p->HasValidSaveData()){
            AccomplishmentProgress* prog = p->GetAccomplishmentProgress();
            if(prog->HasNewRewardVignetteFestival()) return true;
        }
    }
    return false;
}

void AccomplishmentManager::ClearNewRewardVignetteFestival(){
    BandProfile* pProfile = TheProfileMgr.GetPrimaryProfile();
    MILO_ASSERT(pProfile, 0xA65);
    pProfile->AccessAccomplishmentProgress()->ClearNewRewardVignetteFestival();
}

bool AccomplishmentManager::IsCategoryComplete(BandProfile* i_pProfile, Symbol s) const {
    MILO_ASSERT(i_pProfile, 0xA6E);
    AccomplishmentProgress* prog = i_pProfile->GetAccomplishmentProgress();
    int numincat = GetNumAccomplishmentsInCategory(s);
    return numincat <= prog->GetNumCompletedInCategory(s);
}

bool AccomplishmentManager::IsGroupComplete(BandProfile* i_pProfile, Symbol s) const {
    MILO_ASSERT(i_pProfile, 0xA7B);
    AccomplishmentProgress* prog = i_pProfile->GetAccomplishmentProgress();
    int numincat = GetNumAccomplishmentsInGroup(s);
    return numincat <= prog->GetNumCompletedInGroup(s);
}

Symbol AccomplishmentManager::GetFirstUnfinishedAccomplishmentEntry(BandProfile* i_pProfile, Symbol s){
    MILO_ASSERT(i_pProfile, 0xA88);
    MetaPerformer* pPerformer = MetaPerformer::Current();
    MILO_ASSERT(pPerformer, 0xA8B);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0xA8E);
    std::vector<Symbol> vAccomplishmentEntries;
    bool bGotSymbols = pAccomplishment->InqIncrementalSymbols(i_pProfile, vAccomplishmentEntries);
    MILO_ASSERT(bGotSymbols, 0xA93);
    AccomplishmentProgress* prog = i_pProfile->GetAccomplishmentProgress();
    if(prog->IsAccomplished(s)){
        MILO_ASSERT(!vAccomplishmentEntries.empty(), 0xA99);
        return vAccomplishmentEntries[0];
    }
    else {
        Symbol symFirst(gNullStr);
        std::vector<Symbol>::iterator it;
        for(it = vAccomplishmentEntries.begin(); it != vAccomplishmentEntries.end(); ++it){
            if(pAccomplishment->IsSymbolEntryFulfilled(i_pProfile, *it)) break;
        }
        symFirst = *it;
        if(symFirst == goal_filtersong_unknown){
            symFirst = pAccomplishment->GetFirstUnfinishedAccomplishmentEntry(i_pProfile);
        }
        MILO_ASSERT(symFirst != gNullStr, 0xAB1);
        return symFirst;
    }
}

bool AccomplishmentManager::IsAvailable(Symbol s, bool b) const {
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0xAB9);
    if(!pAccomplishment->IsDynamic()) return true;
    else if(b && pAccomplishment->GetDynamicAlwaysVisible()) return true;
    else {
        Symbol filt = pAccomplishment->GetDynamicPrereqsFilter();
        if(filt == gNullStr){
            const std::vector<Symbol>& rSongs = pAccomplishment->GetDynamicPrereqsSongs();
            int numrsongs = rSongs.size();
            int iNumSongs = pAccomplishment->GetDynamicPrereqsNumSongs();
            if(iNumSongs <= 0) iNumSongs = numrsongs;
            MILO_ASSERT(iNumSongs <= rSongs.size(), 0xAD4);
            int i7 = 0;
            for(int i = 0; i < numrsongs; i++){
                if(TheSongMgr->HasSong(rSongs[i], false)) i7++;
                if(i7 >= iNumSongs) return true;
            }
        }
        else {
            int filtcount = GetPrecachedFilterCount(filt);
            if(filtcount >= pAccomplishment->GetDynamicPrereqsNumSongs()) return true;
        }
        return false;
    }
}

bool AccomplishmentManager::IsAvailableToView(Symbol s) const {
    return IsAvailable(s, true);
}

bool AccomplishmentManager::IsAvailableToEarn(Symbol s) const {
    return IsAvailable(s, false);
}

void AccomplishmentManager::HandleRemoteAccomplishmentEarned(Symbol s1, const char* cc, Symbol s2){
    GoalAcquisitionInfo info;
    info.unk0 = s1;
    info.unk4 = cc;
    info.unk10 = s2;
    unk138.push_back(info);
}

void AccomplishmentManager::AddGoalAcquisitionInfo(Symbol s1, const char* cc, Symbol s2){
    GoalAcquisitionInfo info;
    info.unk0 = s1;
    info.unk4 = cc;
    info.unk10 = s2;
    unk138.push_back(info);
}

void AccomplishmentManager::AddGoalProgressionInfo(Symbol s1, const char* cc, Symbol s2, int iii){
    GoalProgressionInfo info;
    info.unk0 = s1;
    info.unk4 = cc;
    info.unk10 = s2;
    info.unk14 = iii;
    unk140.push_back(info);
}

int AccomplishmentManager::GetNumOtherGoalsAcquired(const char* cc, Symbol s){
    int num = 0;
    for(std::vector<GoalAcquisitionInfo>::iterator it = unk138.begin(); it != unk138.end(); ++it){
        if(strcmp(it->unk4.c_str(), cc) == 0 && it->unk0 != s) num++;
    }
    return num;
}

bool AccomplishmentManager::InqGoalsAcquiredForSong(BandUser* i_pUser, Symbol symSong, std::vector<Symbol>& o_rAcquiredGoals){
    MILO_ASSERT(i_pUser, 0xB68);
    MILO_ASSERT(symSong != gNullStr, 0xB69);
    MILO_ASSERT(o_rAcquiredGoals.empty(), 0xB6A);
    const char* username = i_pUser->UserName();
    if(strcmp(username, "") == 0) return false;
    else {
        for(std::vector<GoalAcquisitionInfo>::iterator it = unk138.begin(); it != unk138.end(); ++it){
            if(it->unk10 == symSong && strcmp(it->unk4.c_str(), username) == 0){
                o_rAcquiredGoals.push_back(it->unk0);
            }
        }
        return !o_rAcquiredGoals.empty();
    }
}

bool AccomplishmentManager::DidUserMakeProgressOnGoal(LocalBandUser* i_pUser, Symbol s){
    MILO_ASSERT(i_pUser, 0xB8F);
    for(std::vector<GoalProgressionInfo>::iterator it = unk140.begin(); it != unk140.end(); ++it){
        if(it->unk0 == s){
            if(strcmp(it->unk4.c_str(), i_pUser->ProfileName()) == 0) return true;
        }
    }
    return false;
}

Symbol AccomplishmentManager::GetTourSafeDiscSongAtDifficultyIndex(int idx){
    if(idx >= mTourSafeDiscSongs.size()){
        MILO_WARN("Trying to access tour disc song %i which is beyond number of songs avaiable!", idx);
        idx = mTourSafeDiscSongs.size() - 1;
    }
    return mTourSafeDiscSongs[idx];
}

void AccomplishmentManager::CheatReloadData(DataArray* arr){
    Cleanup();
    Init(arr->FindArray("accomplishment_info", true));
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(AccomplishmentManager)
    HANDLE(earn_accomplishment, OnEarnAccomplishment)
    HANDLE_ACTION(earn_accomplishment_for_all, EarnAccomplishmentForAllParticipants(_msg->Sym(2)))
    HANDLE_EXPR(get_num_goals, GetNumAccomplishments())
    HANDLE_EXPR(get_num_completed_goals, GetNumCompletedAccomplishments(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(has_completed_goal, HasCompletedAccomplishment(_msg->Obj<LocalBandUser>(2), _msg->Sym(3)))
    HANDLE_EXPR(has_new_awards, HasNewAwards())
    HANDLE_EXPR(get_award_description, GetAwardDescription(_msg->Sym(2)))
    HANDLE_EXPR(get_award_name, GetAwardNameDisplay(_msg->Sym(2)))
    HANDLE_EXPR(get_award_icon, GetAwardIcon(_msg->Sym(2)))
    HANDLE_EXPR(has_award_icon, HasAwardIcon(_msg->Sym(2)))
    HANDLE_ACTION(clear_first_new_award, ClearFirstNewAward(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(can_equip_award, CanEquipAward(_msg->Obj<LocalBandUser>(2), _msg->Sym(3)))
    HANDLE_ACTION(equip_award, EquipAward(_msg->Obj<LocalBandUser>(2), _msg->Sym(3)))
    HANDLE_EXPR(has_new_reward_vignettes, HasNewRewardVignettes())
    HANDLE_EXPR(get_name_for_first_new_reward_vignette, GetNameForFirstNewRewardVignette())
    HANDLE_ACTION(clear_first_new_reward_vignette, ClearFirstNewRewardVignette())
    HANDLE_EXPR(has_new_reward_vignette_festival, HasNewRewardVignetteFestival())
    HANDLE_ACTION(clear_new_reward_vignette_festival, ClearNewRewardVignetteFestival())
    HANDLE_ACTION(update_reason_for_award, UpdateReasonLabelForAward(_msg->Sym(2), _msg->Obj<UILabel>(3)))
    HANDLE_ACTION(clear_goal_info, ClearGoalProgressionAcquisitionInfo())
    HANDLE_ACTION(check_for_tour_goals, CheckForFinishedTourAccomplishments())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xBF6)
END_HANDLERS
#pragma pop
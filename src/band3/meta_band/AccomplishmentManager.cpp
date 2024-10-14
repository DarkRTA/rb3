#include "AccomplishmentManager.h"
#include "BandProfile.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentOneShot.h"
#include "meta_band/AccomplishmentTrainerCategoryConditional.h"
#include "meta_band/Award.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "stl/_algo.h"
#include "stl/_pair.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

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
    for(std::map<Symbol, std::set<Symbol>*>::iterator it = unk100.begin(); it != unk100.end(); ++it){
        RELEASE(it->second);
    }
    unk100.clear();
    for(std::map<Symbol, std::list<Symbol>*>::iterator it = unke8.begin(); it != unke8.end(); ++it){
        RELEASE(it->second);
    }
    unke8.clear();
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
    unke0.clear();
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
        // why does this match but sticking all of this into one big && chain doesn't
        if(!pSongData->IsDownload()){
            if(pSongData->HasPart(drum, false)){
                if(pSongData->HasPart(vocals, false)){
                    if(pSongData->HasPart(bass, false)){
                        if(pSongData->HasPart(guitar, false)){
                            if(pSongData->HasPart(real_guitar, false)){
                                if(pSongData->HasPart(real_bass, false)){
                                    if(pSongData->HasPart(keys, false)){
                                        if(pSongData->HasPart(real_keys, false)){
                                            Symbol shortname = TheSongMgr->GetShortNameFromSongID(songid, true);
                                            unk150.push_back(shortname);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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
        case 0:
            ret = new Accomplishment(arr, idx);
            break;
        case 1:
            // ret = new AccomplishmentSongListConditional(arr, idx);
            break;
        case 2:
            // ret = new AccomplishmentSongFilterConditional(arr, idx);
            break;
        case 3:
            // ret = new AccomplishmentLessonSongListConditional(arr, idx);
            break;
        case 4:
            // ret = new AccomplishmentLessonDiscSongConditional(arr, idx);
            break;
        case 5:
            // ret = new AccomplishmentPlayerConditional(arr, idx);
            break;
        case 6:
            // ret = new AccomplishmentTourConditional(arr, idx);
            break;
        case 7:
            // ret = AccomplishmentTrainerListConditional(arr, idx);
            break;
        case 8:
            // ret = new AccomplishmentTrainerCategoryConditional(arr, idx);
            break;
        case 9:
            // ret = new AccomplishmentOneShot(arr, idx);
            break;
        case 10:
            // ret = new AccomplishmentSetlist(arr, idx);
            break;
        case 11:
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
            unke0.push_back(std::make_pair(i3, i4));
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

void AccomplishmentManager::ConfigurePrecachedFilterData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentCategoryGroupingData(){}
void AccomplishmentManager::ConfigureAccomplishmentGroupToCategoriesData(){}
void AccomplishmentManager::ConfigureAccomplishmentRewardData(DataArray*){}

Symbol AccomplishmentManager::GetTourSafeDiscSongAtDifficultyIndex(int index) {
    if (index) {
        TheDebug.Notify(MakeString("", 0));
    }

    return NULL;
}
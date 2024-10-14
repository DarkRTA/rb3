#include "AccomplishmentManager.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "stl/_algo.h"
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

}

void AccomplishmentManager::FactoryCreateAccomplishment(DataArray*, int) {

}

void AccomplishmentManager::ConfigureFanValueData(DataArray*){}
void AccomplishmentManager::ConfigureFanScalingData(DataArray*){}
void AccomplishmentManager::ConfigureAwardData(DataArray*){}
void AccomplishmentManager::ConfigurePrecachedFilterData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentGroupData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentCategoryData(DataArray*){}
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

void AccomplishmentManager::GetCategoryListForGroup(Symbol) const {}
void AccomplishmentManager::GetAccomplishmentSetForCategory(Symbol) const {}
void AccomplishmentManager::GetNumAccomplishmentsInCategory(Symbol) const {}
void AccomplishmentManager::GetNumAccomplishmentsInGroup(Symbol) const {}
void AccomplishmentManager::HasFanValue(Symbol) {}
void AccomplishmentManager::GetMetaScoreValue(Symbol) {}
void AccomplishmentManager::GetScaledFanValue(int) {}
bool AccomplishmentManager::HasAccomplishmentCategory(Symbol) const {}
// void AccomplishmentManager::GetAccomplishmentCategory(Symbol) const {}
bool AccomplishmentManager::HasAccomplishmentGroup(Symbol) const {}
// void AccomplishmentManager::GetAccomplishmentGroup(Symbol) const {}
// void AccomplishmentManager::GetPrecachedFilterCount(Symbol) const {}
void AccomplishmentManager::SetPrecachedFilterCount(Symbol, int) {}
void AccomplishmentManager::GetPrecachedFilter(Symbol) const {}
void AccomplishmentManager::HasAward(Symbol) const {}
// void AccomplishmentManager::GetAward(Symbol) const {}
// void AccomplishmentManager::GetAwardSource(Symbol) const {}
void AccomplishmentManager::GetAwardSourceList(Symbol) const {}
void AccomplishmentManager::AddAwardSource(Symbol, Symbol) {}

bool AccomplishmentManager::DoesAssetHaveSource(Symbol) const {}

void AccomplishmentManager::AddAssetAward(Symbol, Symbol) {
    Symbol s2 = gNullStr;
    
}
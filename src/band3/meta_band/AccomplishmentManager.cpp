#include "AccomplishmentManager.h"
#include "os/Debug.h"

AccomplishmentManager* TheAccomplishmentMgr;

AccomplishmentManager::AccomplishmentManager() {

}

AccomplishmentManager::~AccomplishmentManager(){

}

void AccomplishmentManager::InitializeTourSafeDiscSongs(){
    
}


void AccomplishmentManager::ContentDone() {
    InitializeDiscSongs();
    InitializeTourSafeDiscSongs();
    InitializePrecachedFilters();
}


void AccomplishmentManager::Init(DataArray* configure) {
    ConfigureFanValueData(configure);
    ConfigureFanScalingData(configure);
    ConfigureAwardData(configure);
    ConfigurePrecachedFilterData(configure);
    ConfigureAccomplishmentGroupData(configure);
    ConfigureAccomplishmentCategoryData(configure);
    ConfigureAccomplishmentData(configure);
    ConfigureAccomplishmentCategoryGroupingData();
    ConfigureAccomplishmentGroupToCategoriesData();
    ConfigureAccomplishmentRewardData(configure);
}

void AccomplishmentManager::SanityCheckAwards() {

}

void AccomplishmentManager::Poll() {

}

void AccomplishmentManager::FactoryCreateAccomplishment(DataArray*, int) {

}

void AccomplishmentManager::InitializeDiscSongs(){

}

void AccomplishmentManager::InitializePrecachedFilters(){

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
void AccomplishmentManager::GetPrecachedFilterCount(Symbol) const {}
void AccomplishmentManager::SetPrecachedFilterCount(Symbol, int) {}
void AccomplishmentManager::GetPrecachedFilter(Symbol) const {}
void AccomplishmentManager::HasAward(Symbol) const {}
void AccomplishmentManager::GetAward(Symbol) const {}
void AccomplishmentManager::GetAwardSource(Symbol) const {}
void AccomplishmentManager::GetAwardSourceList(Symbol) const {}
void AccomplishmentManager::AddAwardSource(Symbol, Symbol) {}

bool AccomplishmentManager::DoesAssetHaveSource(Symbol) const {}

void AccomplishmentManager::AddAssetAward(Symbol, Symbol) {
    Symbol s2 = gNullStr;
    
}
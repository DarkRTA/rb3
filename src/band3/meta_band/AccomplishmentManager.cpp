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
    ConfigureAccomplishmentCategoryGroupingData(configure);
    ConfigureAccomplishmentGroupToCategoriesData(configure);
    ConfigureAccomplishmentRewardData(configure);
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
void AccomplishmentManager::ConfigureAccomplishmentCategoryGroupingData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentGroupToCategoriesData(DataArray*){}
void AccomplishmentManager::ConfigureAccomplishmentRewardData(DataArray*){}

Symbol AccomplishmentManager::GetTourSafeDiscSongAtDifficultyIndex(int index) {
    if (index) {
        TheDebug.Notify(MakeString("", 0));
    }

    return NULL;
}

void AccomplishmentManager::AddAssetAward(Symbol, Symbol) {
    Symbol s2 = gNullStr;
    
}
#include "AccomplishmentManager.h"

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

void AccomplishmentManager::GetTourSafeDiscSongAtDifficultyIndex(int index) {

}
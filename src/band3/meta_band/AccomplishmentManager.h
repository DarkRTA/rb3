#ifndef METABAND_ACCOMPLISHMENTMANAGER_H
#define METABAND_ACCOMPLISHMENTMANAGER_H

#include "system/obj/Data.h"
#include <map>
#include <utility>
#include "AccomplishmentCategory.h"
#include "Accomplishment.h"

class Award;

class AccomplishmentManager {
    std::map<Symbol, Award*> mAwards;
    std::map<Symbol, AccomplishmentCategory> mAccomplishmentCategory;
    std::map<Symbol, Accomplishment*> mAccomplishments;
    std::map<Symbol, Symbol> mSymbols;

    void InitializeTourSafeDiscSongs();
    void ContentDone();
    void Init(DataArray*);
    void InitializeDiscSongs();
    void InitializePrecachedFilters();

    void ConfigureFanValueData(DataArray*);
    void ConfigureFanScalingData(DataArray*);
    void ConfigureAwardData(DataArray*);
    void ConfigurePrecachedFilterData(DataArray*);
    void ConfigureAccomplishmentGroupData(DataArray*);
    void ConfigureAccomplishmentCategoryData(DataArray*);
    void ConfigureAccomplishmentData(DataArray*);
    void ConfigureAccomplishmentCategoryGroupingData(DataArray*);
    void ConfigureAccomplishmentGroupToCategoriesData(DataArray*);
    void ConfigureAccomplishmentRewardData(DataArray*);
public:
    AccomplishmentManager();
    virtual ~AccomplishmentManager();

    Symbol GetTourSafeDiscSongAtDifficultyIndex(int index);
    void AddAssetAward(Symbol, Symbol);
};

extern AccomplishmentManager TheAccomplishmentMgr;
#endif // METABAND_ACCOMPLISHMENTMANAGER_H

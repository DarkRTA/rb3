#ifndef METABAND_ACCOMPLISHMENTMANAGER_H
#define METABAND_ACCOMPLISHMENTMANAGER_H

#include "system/obj/Data.h"

class AccomplishmentManager {
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

    void GetTourSafeDiscSongAtDifficultyIndex(int index);
};

static AccomplishmentManager TheAccomplishmentMgr;
#endif // METABAND_ACCOMPLISHMENTMANAGER_H
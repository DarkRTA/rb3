#ifndef METABAND_ACCOMPLISHMENTMANAGER_H
#define METABAND_ACCOMPLISHMENTMANAGER_H

#include "system/obj/Data.h"
#include <map>
#include <utility>
#include "AccomplishmentCategory.h"
#include "Accomplishment.h"

class Award;

class AccomplishmentManager {
public:
    std::map<Symbol, Award*> mAwards;
    std::map<Symbol, AccomplishmentCategory> mAccomplishmentCategory;
    std::map<Symbol, Accomplishment*> mAccomplishments;
    std::map<Symbol, Symbol> mSymbols;

    void InitializeDiscSongs();
    void InitializePrecachedFilters();

    void InitializeTourSafeDiscSongs();
    void ContentDone();
    void Init(DataArray*);
    void SanityCheckAwards();
    void Poll();
    void FactoryCreateAccomplishment(DataArray*, int);
    void ConfigureFanValueData(DataArray*);
    void ConfigureFanScalingData(DataArray*);
    void ConfigureAccomplishmentCategoryData(DataArray*);
    void ConfigureAccomplishmentGroupData(DataArray*);
    void ConfigureAwardData(DataArray*);
    void ConfigureAccomplishmentData(DataArray*);
    void ConfigureAccomplishmentCategoryGroupingData();
    void ConfigureAccomplishmentGroupToCategoriesData();
    void ConfigurePrecachedFilterData(DataArray*);
    void ConfigureAccomplishmentRewardData(DataArray*);
    void GetCategoryListForGroup(Symbol) const;
    void GetAccomplishmentSetForCategory(Symbol) const;
    void GetNumAccomplishmentsInCategory(Symbol) const;
    void GetNumAccomplishmentsInGroup(Symbol) const;
    void HasFanValue(Symbol);
    void GetMetaScoreValue(Symbol);
    void GetScaledFanValue(int);
    bool HasAccomplishmentCategory(Symbol) const;
    void GetAccomplishmentCategory(Symbol) const;
    bool HasAccomplishmentGroup(Symbol) const;
    void GetAccomplishmentGroup(Symbol) const;
    void GetPrecachedFilterCount(Symbol) const;
    void SetPrecachedFilterCount(Symbol, int);
    void GetPrecachedFilter(Symbol) const;
    void HasAward(Symbol) const;
    void GetAward(Symbol) const;
    void GetAwardSource(Symbol) const;
    void GetAwardSourceList(Symbol) const;
    void AddAwardSource(Symbol, Symbol);
    void UpdateMostStarsForAllParticipants(Symbol, int);
    bool DoesAssetHaveSource(Symbol) const;
    void UpdateTourPlayedForAllParticipants(Symbol);


    AccomplishmentManager();
    virtual ~AccomplishmentManager();

    Symbol GetTourSafeDiscSongAtDifficultyIndex(int index);
    void AddAssetAward(Symbol, Symbol);



    void CheckForFinishedTrainerAccomplishmentsForUser(LocalBandUser*);


};

extern AccomplishmentManager* TheAccomplishmentMgr;
#endif // METABAND_ACCOMPLISHMENTMANAGER_H

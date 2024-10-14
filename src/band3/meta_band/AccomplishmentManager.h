#ifndef METABAND_ACCOMPLISHMENTMANAGER_H
#define METABAND_ACCOMPLISHMENTMANAGER_H
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "system/obj/Data.h"
#include <map>
#include "AccomplishmentCategory.h"
#include "Accomplishment.h"
#include "meta_band/Award.h"

struct GoalAlpaCmp {
    GoalAlpaCmp();
    bool operator()(Symbol, Symbol) const;
};

struct SongDifficultyCmp {
    SongDifficultyCmp(Symbol);
    bool operator()(Symbol, Symbol) const;

    Symbol mInst; // 0x0
};

class AccomplishmentManager : public Hmx::Object, public ContentMgr::Callback {
public:
    AccomplishmentManager();
    virtual ~AccomplishmentManager();
    virtual DataNode Handle(DataArray*, bool);
    virtual const char* ContentDir();
    virtual void ContentDone();

    void InitializeDiscSongs();
    void InitializePrecachedFilters();

    void InitializeTourSafeDiscSongs();
    void Init(DataArray*);
    void SanityCheckAwards();
    void Poll();
    Accomplishment* FactoryCreateAccomplishment(DataArray*, int);
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
    bool HasFanValue(Symbol);
    void GetMetaScoreValue(Symbol);
    void GetScaledFanValue(int);
    bool HasAccomplishmentCategory(Symbol) const;
    bool HasAccomplishmentGroup(Symbol) const;
    int GetPrecachedFilterCount(Symbol) const;
    void SetPrecachedFilterCount(Symbol, int);
    void GetPrecachedFilter(Symbol) const;
    bool HasAward(Symbol) const;
    void GetAwardSourceList(Symbol) const;
    void AddAwardSource(Symbol, Symbol);
    void UpdateMostStarsForAllParticipants(Symbol, int);
    bool DoesAssetHaveSource(Symbol) const;
    void UpdateTourPlayedForAllParticipants(Symbol);
    Accomplishment* GetAccomplishment(Symbol) const;
    void AddGoalAcquisitionInfo(Symbol, const char*, Symbol);
    int GetLeaderboardHardcoreStatus(int) const;
    int GetIconHardCoreStatus(int) const;
    AccomplishmentCategory* GetAccomplishmentCategory(Symbol) const;
    bool IsCategoryComplete(BandProfile*, Symbol) const;
    bool IsGroupComplete(BandProfile*, Symbol) const;
    AccomplishmentGroup* GetAccomplishmentGroup(Symbol) const;
    Symbol GetTourSafeDiscSongAtDifficultyIndex(int index);
    Award* GetAward(Symbol) const;
    void AddAssetAward(Symbol, Symbol);
    void CheckForFinishedTrainerAccomplishmentsForUser(LocalBandUser*);
    void Cleanup();
    Symbol GetAwardSource(Symbol) const;

    std::map<Symbol, Accomplishment*> mAccomplishments; // 0x20
    std::map<Symbol, AccomplishmentCategory*> mAccomplishmentCategory; // 0x38
    std::map<Symbol, AccomplishmentGroup*> mAccomplishmentGroups; // 0x50
    std::map<Symbol, Award*> mAwards; // 0x68
    std::map<Symbol, Symbol> unk80; // 0x80
    std::map<Symbol, Symbol> unk98; // 0x98
    std::map<Symbol, std::vector<Symbol>*> unkb0; // 0xb0
    std::map<Symbol, int> unkc8; // 0xc8
    std::vector<std::pair<int, int> > unke0; // 0xe0
    std::map<Symbol, std::list<Symbol>*> unke8; // 0xe8
    std::map<Symbol, std::set<Symbol>*> unk100; // 0x100
    int unk118[4];
    int unk128[4];
    std::vector<int> unk138; // 0x138
    std::vector<int> unk140; // 0x140
    std::vector<Symbol> unk148; // 0x148
    std::vector<Symbol> unk150; // 0x150
    std::map<Symbol, SongSortMgr::SongFilter*> unk158; // 0x158
    std::map<Symbol, int> unk170; // 0x170
};

extern AccomplishmentManager* TheAccomplishmentMgr;
#endif // METABAND_ACCOMPLISHMENTMANAGER_H

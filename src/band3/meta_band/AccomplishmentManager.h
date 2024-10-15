#ifndef METABAND_ACCOMPLISHMENTMANAGER_H
#define METABAND_ACCOMPLISHMENTMANAGER_H
#include "BandProfile.h"
#include "game/BandUser.h"
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

struct GoalAcquisitionInfo {
    GoalAcquisitionInfo(){}
    Symbol unk0;
    String unk4;
    Symbol unk10;
};

struct GoalProgressionInfo {
    GoalProgressionInfo(){}
    Symbol unk0;
    String unk4;
    Symbol unk10;
    int unk14;
};

class AccomplishmentManager : public Hmx::Object, public ContentMgr::Callback {
public:
    AccomplishmentManager();
    virtual ~AccomplishmentManager();
    virtual DataNode Handle(DataArray*, bool);
    virtual const char* ContentDir(){ return nullptr; }
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
    std::list<Symbol>* GetCategoryListForGroup(Symbol) const;
    std::set<Symbol>* GetAccomplishmentSetForCategory(Symbol) const;
    int GetNumAccomplishmentsInCategory(Symbol) const;
    int GetNumAccomplishmentsInGroup(Symbol) const;
    bool HasFanValue(Symbol);
    int GetMetaScoreValue(Symbol);
    void GetScaledFanValue(int);
    bool HasAccomplishmentCategory(Symbol) const;
    bool HasAccomplishmentGroup(Symbol) const;
    int GetPrecachedFilterCount(Symbol) const;
    void SetPrecachedFilterCount(Symbol, int);
    SongSortMgr::SongFilter* GetPrecachedFilter(Symbol) const;
    bool HasAward(Symbol) const;
    std::vector<Symbol>* GetAwardSourceList(Symbol) const;
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
    bool HasAccomplishment(Symbol) const;
    bool IsAvailableToView(Symbol) const;
    bool InqAssetSourceList(Symbol, std::vector<Symbol>&) const;
    Symbol GetAssetAward(Symbol) const;
    String GetHintStringForSource(Symbol) const;
    void UpdateAssetHintLabel(Symbol, UILabel*);
    void EarnAccomplishment(LocalBandUser*, Symbol);
    void EarnAccomplishment(BandProfile*, Symbol);
    bool IsAvailableToEarn(Symbol) const;
    void EarnAccomplishmentForProfile(BandProfile*, Symbol);
    void UpdatePlayedTourForAllRemoteParticipants(Symbol);
    void UpdateMostStarsForAllRemoteParticipants(Symbol, int);
    void EarnAccomplishmentForAllParticipants(Symbol);
    void EarnAccomplishmentForAllRemoteParticipants(Symbol);
    void CheckForIncrementalProgressForUserGoal(Symbol, Symbol, LocalBandUser*);
    void AddGoalProgressionInfo(Symbol, const char*, Symbol, int);
    void CheckForFinishedTourAccomplishments();
    void CheckForFinishedTourAccomplishmentsForProfile(BandProfile*);
    void CheckForFinishedTourAccomplishmentsForUser(LocalBandUser*);
    void CheckForFinishedAccomplishmentsForUser(Symbol, LocalBandUser*);
    void HandlePreSongCompleted(Symbol);
    void HandlePreSongCompletedForUser(Symbol, LocalBandUser*);
    void HandleSetlistCompleted(Symbol, bool, Difficulty, int);
    void HandleSetlistCompletedForUser(Symbol, bool, LocalBandUser*, Difficulty, int);
    void HandleSongCompleted(Symbol, Difficulty);
    void HandleSongCompletedForUser(Symbol, LocalBandUser*, Difficulty);
    void InitializeSongIncrementalDataForUserGoal(Symbol, LocalBandUser*);
    void UpdateSongStatusFlagsForUser(Symbol, LocalBandUser*, Difficulty);
    void UpdateMiscellaneousSongDataForUser(Symbol, LocalBandUser*);
    void CheckForOneShotAccomplishments(Symbol, LocalBandUser*, Difficulty);
    int GetNumAccomplishments() const;
    bool HasCompletedAccomplishment(LocalBandUser*, Symbol) const;
    int GetNumCompletedAccomplishments(LocalBandUser*) const;
    bool HasNewAwards() const;
    LocalBandUser* GetUserForFirstNewAward();
    Symbol GetReasonForFirstNewAward(LocalBandUser*) const;
    Symbol GetNameForFirstNewAward(LocalBandUser*) const;
    Symbol GetAwardDescription(Symbol) const;
    Symbol GetAwardNameDisplay(Symbol) const;
    void UpdateReasonLabelForAward(Symbol, UILabel*);
    bool CanEquipAward(LocalBandUser*, Symbol) const;
    void EquipAward(LocalBandUser*, Symbol);
    bool HasAwardIcon(Symbol) const;
    String GetAwardIcon(Symbol) const;
    void ClearFirstNewAward(LocalBandUser*);
    Symbol GetNameForFirstNewRewardVignette() const;
    void ClearFirstNewRewardVignette();
    bool HasNewRewardVignetteFestival() const;
    void ClearNewRewardVignetteFestival();
    Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile*, Symbol);
    bool IsAvailable(Symbol, bool) const;
    void HandleRemoteAccomplishmentEarned(Symbol, const char*, Symbol);
    int GetNumOtherGoalsAcquired(const char*, Symbol);
    bool InqGoalsAcquiredForSong(BandUser*, Symbol, std::vector<Symbol>&);
    bool DidUserMakeProgressOnGoal(LocalBandUser*, Symbol);
    void CheatReloadData(DataArray*);
    bool HasNewRewardVignettes() const;
    void ClearGoalProgressionAcquisitionInfo();

    DataNode OnEarnAccomplishment(const DataArray*);

    std::map<Symbol, Accomplishment*> mAccomplishments; // 0x20
    std::map<Symbol, AccomplishmentCategory*> mAccomplishmentCategory; // 0x38
    std::map<Symbol, AccomplishmentGroup*> mAccomplishmentGroups; // 0x50
    std::map<Symbol, Award*> mAwards; // 0x68
    std::map<Symbol, Symbol> mAssetToAward; // 0x80
    std::map<Symbol, Symbol> mAwardToSource; // 0x98
    std::map<Symbol, std::vector<Symbol>*> unkb0; // 0xb0
    std::map<Symbol, int> mFanValues; // 0xc8
    std::vector<std::pair<int, int> > m_vFanScalingData; // 0xe0
    std::map<Symbol, std::list<Symbol>*> m_mapGroupToCategories; // 0xe8
    std::map<Symbol, std::set<Symbol>*> m_mapCategoryToAccomplishmentSet; // 0x100
    int mAccomplishmentRewardLeaderboardThresholds[4]; // 0x118
    int mAccomplishmentRewardIconThresholds[4]; // 0x128
    std::vector<GoalAcquisitionInfo> unk138; // 0x138
    std::vector<GoalProgressionInfo> unk140; // 0x140
    std::vector<Symbol> mDiscSongs; // 0x148
    std::vector<Symbol> mTourSafeDiscSongs; // 0x150
    std::map<Symbol, SongSortMgr::SongFilter*> mPrecachedFilters; // 0x158
    std::map<Symbol, int> mPrecachedFilterCounts; // 0x170
};

extern AccomplishmentManager* TheAccomplishmentMgr;
#endif // METABAND_ACCOMPLISHMENTMANAGER_H

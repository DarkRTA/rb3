#pragma once
#include "os/Debug.h"
#include "system/obj/Data.h"
#include "utl/MemMgr.h"
#include <set>
#include "BandProfile.h"
#include "band3/game/BandUser.h"
#include "band3/game/Tracker.h"
#include "band3/meta_band/MusicLibrary.h"
#include "system/ui/UILabel.h"

enum AccomplishmentType {
    kAccomplishmentTypeUnique = 0,
    kAccomplishmentTypeSongListConditional = 1,
    kAccomplishmentTypeSongFilterConditional = 2,
    kAccomplishmentTypeLessonSongListConditional = 3,
    kAccomplishmentTypeLessonDiscSongConditional = 4,
    kAccomplishmentTypePlayerConditional = 5,
    kAccomplishmentTypeTourConditional = 6,
    kAccomplishmentTypeTrainerListConditional = 7,
    kAccomplishmentTypeTrainerCategoryConditional = 8,
    kAccomplishmentTypeOneShot = 9,
    kAccomplishmentTypeSetlist = 10,
    kAccomplishmentTypeDiscSongConditional = 11
};

class Accomplishment {
public:
    Accomplishment(DataArray *, int);
    virtual ~Accomplishment();
    virtual AccomplishmentType GetType() const;
    virtual bool ShowBestAfterEarn() const;
    virtual void UpdateIncrementalEntryName(UILabel *, Symbol) { MILO_ASSERT(false, 109); }
    virtual bool IsFulfilled(BandProfile *) const;
    virtual bool IsRelevantForSong(Symbol) const;
    virtual Difficulty GetRequiredDifficulty() const;
    virtual bool InqRequiredScoreTypes(std::set<ScoreType> &) const;
    virtual bool InqProgressValues(BandProfile *, int &, int &);
    virtual bool InqIncrementalSymbols(BandProfile *, std::vector<Symbol> &) const;
    virtual bool IsSymbolEntryFulfilled(BandProfile *, Symbol) const;
    virtual Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile *) const;
    virtual bool CanBeLaunched() const;
    virtual bool HasSpecificSongsToLaunch() const;
    virtual void
    InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask &, BandProfile *) const;
    virtual void InitializeTrackerDesc(TrackerDesc &) const;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    void Configure(DataArray *);
    Symbol GetName() const;
    Symbol GetDescription() const;
    Symbol GetSecretDescription() const;
    Symbol GetFlavorText() const;
    bool GetShouldShowDenominator() const;
    bool HideProgress() const;
    Symbol GetSecretCampaignLevelPrereq() const;
    const std::vector<Symbol> &GetSecretPrereqs() const;
    bool IsDynamic() const;
    bool GetDynamicAlwaysVisible() const;
    const std::vector<Symbol> &GetDynamicPrereqsSongs() const;
    int GetDynamicPrereqsNumSongs() const;
    Symbol GetDynamicPrereqsFilter() const;
    Symbol GetCategory() const;
    int GetContextID() const;
    const char *GetIconArt() const;
    Symbol GetAward() const;
    bool HasAward() const;
    Symbol GetMetaScoreValue() const;
    bool IsUserOnValidScoreType(LocalBandUser *) const;
    bool IsUserOnValidController(LocalBandUser *) const;
    ScoreType GetRequiredScoreType() const;
    int GetRequiredMinPlayers() const;
    int GetRequiredMaxPlayers() const;
    bool GetRequiresUnisonAbility() const;
    bool GetRequiresBREAbility() const;
    bool CanBeEarnedWithNoFail() const;
    bool IsTrackedInLeaderboard() const;
    Symbol GetUnitsToken(int) const;
    Symbol GetPassiveMsgChannel() const;
    int GetPassiveMsgPriority() const;
    static const char *GetIconPath();

    Symbol mName; // 0x04
    std::vector<Symbol> mSecretPrereqs; // 0x08
    int mAccomplishmentType; // 0x10
    Symbol mCategory; // 0x14
    Symbol mAward; // 0x18
    Symbol mUnitsToken; // 0x1c
    Symbol mUnitsTokenSingular; // 0x20
    Symbol mIconOverride; // 0x24
    Symbol mSecretCampaignLevelPrereq; // 0x28
    std::vector<ControllerType> mControllerTypes; // 0x2c
    ScoreType mScoreType; // 0x34
    Difficulty mLaunchableDifficulty; // 0x38
    Symbol mPassiveMsgChannel; // 0x3c
    int mPassiveMsgPriority; // 0x40
    int mPlayerCountMin; // 0x44
    int mPlayerCountMax; // 0x48
    int mDynamicPrereqsNumSongs; // 0x4c
    std::vector<Symbol> mDynamicPrereqsSongs; // 0x50
    Symbol mDynamicPrereqsFilter; // 0x58
    int mProgressStep; // 0x5c
    int mIndex; // 0x60
    int mContextId; // 0x64
    Symbol mMetaScoreValue; // 0x68
    bool mRequiresUnison; // 0x6c
    bool mRequiresBre; // 0x6d
    bool mDynamicAlwaysVisible; // 0x6e
    bool mShouldShowDenominator; // ox6f
    bool mShowBestAfterEarn; // 0x70
    bool mHideProgress; // 0x71
    bool mCanBeEarnedWithNoFail; // 0x72
    bool mIsTrackedInLeaderboard; // 0x73
};

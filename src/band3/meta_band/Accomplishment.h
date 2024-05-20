#ifndef METABAND_ACCOMPLISHMENT_H
#define METABAND_ACCOMPLISHMENT_H

#include "system/obj/Data.h"
#include <set>
#include "BandProfile.h"
#include "band3/game/BandUser.h"

enum ScoreType {

};

enum Difficulty {
    kDifficultyEasy = 0,
    kDifficultyMedium = 1,
    kDifficultyHard = 2,
    kDifficultyExpert = 3,
    kNumDifficulties = 4,
};

// Don't know where to put this yet
enum ControllerType {
    kControllerDrum = 0,
    kControllerGuitar = 1,
    kControllerVocals = 2,
    kControllerNone = 3,
    kNumControllerTypes = 3,
};

class TrackerDesc;

class Accomplishment {
public:
    Accomplishment(DataArray*, int);
    virtual ~Accomplishment();

private:
    void Configure(DataArray*);
    int GetType() const;
    Symbol GetName() const;
    Symbol GetDescription() const;
    Symbol GetSecretDescription() const;
    Symbol GetFlavorText() const;
    bool GetShouldShowDenominator() const;
    bool ShowBestAfterEarn() const;
    bool HideProgress() const;
    Symbol GetSecretCampaignLevelPrereq() const;
    Accomplishment* GetSecretPrereqs() const;
    bool IsDynamic() const;
    bool GetDynamicAlwaysVisible() const;
    Accomplishment* GetDynamicPrereqsSongs() const;
    int GetDynamicPrereqsNumSongs() const;
    Symbol GetDynamicPrereqsFilter() const;
    Symbol GetCategory() const;
    Symbol GetContextID() const;
    void GetIconArt() const;
    bool IsFulfilled(BandProfile*) const;
    bool IsRelevantForSong(Symbol) const;
    bool InqProgressValues(BandProfile*, int&, int&);
    bool GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol, unsigned short>&) const;
    bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    bool CanBeLaunched() const;
    bool HasSpecificSongsToLaunch() const;
    Symbol GetAward() const;
    bool HasAward() const;
    int GetMetaScoreValue() const;
    char* GetIconPath();
    void IsUserOnValidScoreType(LocalBandUser*) const;
    void IsUserOnValidController(LocalBandUser*) const;
    Symbol GetRequiredDifficulty() const;
    void GetRequiredScoreType() const;
    void InqRequiredScoreTypes(std::set<ScoreType>&) const;
    int GetRequiredMinPlayers() const;
    int GetRequiredMaxPlayers() const;
    bool GetRequiresUnisonAbility() const;
    bool GetRequiresBREAbility() const;
    // void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    void InitializeTrackerDesc(TrackerDesc&) const;
    bool CanBeEarnedWithNoFail() const;
    bool IsTrackedInLeaderboard() const;
    Symbol GetUnitsToken(int) const;
    Symbol GetPassiveMsgChannel() const;
    Symbol GetPassiveMsgPriority() const;

    Symbol mName;       // 0x04
    Accomplishment* mSecretPrereqs; // 0x08 this REALLY feels like a vector
    int mPadding;
    int mAccomplishmentType;    //0x10
    Symbol mCategory; // 0x14
    Symbol mAward; // 0x18
    Symbol mUnitsToken; // 0x1c
    Symbol mUnitsTokenSingular; // 0x20
    Symbol mIconOverride; // 0x24
    Symbol mSecretCampaignLevelPrereq; // 0x28
    std::vector<int> mControllerTypes; // don't know this type yet, used in destructor

    Symbol mScoreType; //0x34
    Symbol mLaunchableDifficulty; // 0x38
    Symbol mPassiveMsgChannel;  // 0x3c
    Symbol mPassiveMsgPriority; // 0x40
    int mPlayerCountMin; // 0x44
    int mPlayerCountMax; // 0x48
    int mDynamicPrereqsNumSongs; // 0x4c
    Accomplishment* mDynamicPrereqsSongs; // 0x50
    Symbol mPadding2;
    Symbol mDynamicPrereqsFilter; // 0x58
    int mProgressStep; // 0x5c

    int mPadding3; // 0x60, Don't know what this is yet
    
    Symbol mContextId;  // 0x64

    int mMetaScoreValue; // 0x68
    bool mRequiresUnison; // 0x6c
    bool mRequiresBre; // 0x6d
    bool mDynamicAlwaysVisible; // 0x6e
    bool mShouldShowDenominator; // ox6f
    bool mShowBestAfterEarn; // 0x70
    bool mHideProgress; // 0x71
    bool mCanBeEarnedWithNoFail; // 0x72
    bool mIsTrackedInLeaderboard; // 0x73
};
#endif // METABAND_ACCOMPLISHMENT_H
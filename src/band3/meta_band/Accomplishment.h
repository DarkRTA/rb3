#ifndef METABAND_ACCOMPLISHMENT_H
#define METABAND_ACCOMPLISHMENT_H

#include "system/obj/Data.h"
#include <set>

class BandProfile;
class LocalBandUser;
enum ScoreType {

};
enum ControllerType {};
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
    int GetDynamicPrereqsSongs() const;
    int GetDynamicPrereqsNumSongs() const;
    void GetDynamicPrereqsFilter() const;
    Symbol GetCategory() const;
    void GetContextID() const;
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
    void GetRequiredDifficulty() const;
    void GetRequiredScoreType() const;
    void InqRequiredScoreTypes(std::set<ScoreType>&) const;
    void GetRequiredMinPlayers() const;
    void GetRequiredMaxPlayers() const;
    void GetRequiresUnisonAbility() const;
    void GetRequiresBREAbility() const;
    // void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    void InitializeTrackerDesc(TrackerDesc&) const;
    bool CanBeEarnedWithNoFail() const;
    bool IsTrackedInLeaderboard() const;
    void GetUnitsToken(int) const;
    void GetPassiveMsgChannel() const;
    void GetPassiveMsgPriority() const;

    Symbol mName;       // 0x04
    Accomplishment* mSecretPrereqs; // 0x08
    Symbol mCategory; // 0x14
    Symbol mAward; // 0x18
    Symbol mSecretCampaignLevelPrereq; // 0x28


















    Symbol mPassiveMsgChannel;  // 0x3c
    Symbol mPassiveMsgPriority; // 0x40
    int mDynamicPrereqsNumSongs; // 0x4c

    int mMetaScoreValue; // 0x68
    bool mDynamicAlwaysVisible; // 0x6e
    bool mShouldShowDenominator; // ox6f
    bool mShowBestAfterEarn; // 0x70
    bool mHideProgress; // 0x71
    bool mCanBeEarnedWithNoFail; // 0x72
    bool mIsTrackedInLeaderboard; // 0x73

    std::set<ScoreType> mScoreTypes;
};
#endif // METABAND_ACCOMPLISHMENT_H
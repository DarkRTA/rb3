#ifndef METABAND_ACCOMPLISHMENT_H
#define METABAND_ACCOMPLISHMENT_H

#include "system/obj/Data.h"
#include <set>

class BandProfile;
class LocalBandUser;
class ScoreType {};
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
    void GetShouldShowDenominator() const;
    void ShowBestAfterEarn() const;
    void HideProgress() const;
    void GetSecretCampaignLevelPrereq() const;
    void GetSecretPrereqs() const;
    void IsDynamic() const;
    void GetDynamicAlwaysVisible() const;
    void GetDynamicPrereqsSongs() const;
    void GetDynamicPrereqsNumSongs() const;
    void GetDynamicPrereqsFilter() const;
    void GetCategory() const;
    void GetContextID() const;
    void GetIconArt() const;
    bool IsFulfilled(BandProfile*) const;
    bool IsRelevantForSong(Symbol) const;
    bool InqProgressValues(BandProfile*, int&, int&);
    void GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol, unsigned short>&) const;
    void IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    void CanBeLaunched() const;
    bool HasSpecificSongsToLaunch() const;
    void GetAward() const;
    void HasAward() const;
    void GetMetaScoreValue() const;
    void GetIconPath();
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
    void CanBeEarnedWithNoFail() const;
    void IsTrackedInLeaderboard() const;
    void GetUnitsToken(int) const;
    void GetPassiveMsgChannel() const;
    void GetPassiveMsgPriority() const;

    Symbol mName;       // 0x04
};
#endif // METABAND_ACCOMPLISHMENT_H
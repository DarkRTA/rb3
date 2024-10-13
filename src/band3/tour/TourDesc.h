#pragma once
#include "obj/Data.h"
#include "utl/Symbol.h"

class TourDescEntry {
public:
    TourDescEntry() : mTier(-1), mGroup(""), mQuest(""), mNumSongs(0), mFilter(""), mVenue(""), mAnnouncementScreen(""), mMapScreen(""), mFlavor("") {}
    virtual ~TourDescEntry(){}

    int mTier; // 0x4
    Symbol mGroup; // 0x8
    Symbol mQuest; // 0xc
    int mNumSongs; // 0x10
    std::vector<Symbol> mSetlistTypes; // 0x14
    Symbol mFilter; // 0x1c
    Symbol mCity; // 0x20
    Symbol mVenue; // 0x24
    Symbol mAnnouncementScreen; // 0x28
    Symbol mMapScreen; // 0x2c
    Symbol mFlavor; // 0x30
};

class TourDesc {
public:
    TourDesc(DataArray*, int);
    virtual ~TourDesc();
    virtual void Configure(DataArray*);

    Symbol GetFilterForGigNum(int) const;
    Symbol GetSetlistTypeForGigNum(int, int) const;
    int GetNumSongsForGigNum(int) const;
    Symbol GetVenueForGigNum(int) const;
    Symbol GetLeaderboardGoal() const;
    bool HasLeaderboardGoal() const;
    int GetNumGigs() const;
    int GetNumStarsPossibleForTour() const;
    Symbol GetCityForGigNum(int) const;
    Symbol GetName() const;
    Symbol GetWelcome() const;
    void Cleanup();
    Symbol GetDescription() const;
    Symbol GetConclusionText() const;
    int GetIndex() const;
    TourDescEntry* GetTourDescEntryForGigNum(int) const;
    bool HasSpecificQuest(int) const;
    Symbol GetSpecificQuestForGigNum(int) const;
    Symbol GetQuestGroupForGigNum(int) const;
    bool HasQuestGroup(int) const;
    int GetQuestTierForGigNum(int) const;
    Symbol GetAnnouncementScreenForGigNum(int) const;
    bool HasQuestTier(int) const;
    bool HasAnnouncementScreen(int) const;
    Symbol GetFlavorForGigNum(int) const;
    Symbol GetMapScreenForGigNum(int) const;
    int GetNumSongs() const;
    Symbol GetTourStarsBronzeGoalValue() const;
    Symbol GetTourStarsSilverGoalValue() const;
    Symbol GetTourStarsGoldGoalValue() const;
    Symbol GetTourBronzeGoal() const;
    Symbol GetTourSilverGoal() const;
    Symbol GetTourGoldGoal() const;
    bool HasRequiredCampaignLevel() const;
    Symbol GetRequiredCampaignLevel() const;
    const char* GetArt() const;
    const char* GetGrayArt() const;
    Symbol GetGigGuideMap() const;

    Symbol mName; // 0x4
    int mIndex; // 0x8
    Symbol mTourStarsBronzeGoal; // 0xc
    Symbol mTourStarsSilverGoal; // 0x10
    Symbol mTourStarsGoldGoal; // 0x14
    Symbol mRequiredCampaignLevel; // 0x18
    Symbol mLeaderboardGoal; // 0x1c
    Symbol mDifficulty; // 0x20
    Symbol mGigGuideMap; // 0x24
    std::vector<TourDescEntry*> m_vEntries; // 0x28
};
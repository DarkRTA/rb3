#ifndef TOUR_TOURPROGRESS_H
#define TOUR_TOURPROGRESS_H
#include "obj/Object.h"
#include "tour/TourPropertyCollection.h"
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/QuestJournal.h"
#include "utl/BinStream.h"

#define kTour_NumQuestFilters 3

class TourProgress : public TourSavable, public FixedSizeSaveable {
public:
    TourProgress();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourProgress();
    virtual int SecBetweenUploads() const { return 45; }
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void HandleTourRewardApplied();
    void SetOnTour(bool);
    void ClearQuestFilters();
    void SyncSave(BinStream&);
    void SyncLoad(BinStream&);
    void HandleDirty(int);
    void UpdateLastTouchTime();
    String GetLastTouchedDateString() const;
    TourPropertyCollection& GetTourProperties();
    const TourPropertyCollection& GetTourProperties() const;
    TourPropertyCollection& GetPerformanceProperties();
    const TourPropertyCollection& GetPerformanceProperties() const;
    void ClearPerformanceState();
    void ClearPeformanceProperties();
    void HandleQuestFinished();
    void SetCurrentQuest(Symbol);
    bool IsOnTour() const;
    Symbol GetTourDesc() const;
    void SetTourDesc(Symbol);
    int GetNumTotalGigs() const;
    void FinalizeNewStars();
    void ClearNewStars();
    void UpdateMostStars();
    int GetNumStars() const;
    Symbol GetFilterForCurrentGig() const;
    Symbol GetSetlistTypeForCurrentGig(int) const;
    int GetNumSongsForCurrentGig() const;
    Symbol GetVenueForCurrentGig() const;
    bool IsTourComplete() const;
    bool AreAllTourGigsComplete() const;
    Symbol GetTourLeaderboardGoal() const;
    bool DoesTourHaveLeaderboard() const;
    void SetNumCompletedGigs(int);
    int GetCurrentGigNum() const;
    int GetNumStarsForGig(int) const;
    int GetNumCompletedGigs() const;
    void SetCurrentGigNum(int);
    void ResetTourData();
    float GetTourPropertyValue(Symbol) const;
    void RemoveStars(int);
    void EarnStars(int);
    bool GetWonQuest() const;
    void SetWonQuest(bool);
    int GetTotalStarsForTour() const;
    Symbol GetTourStatus(int) const;
    int GetNumStarsForTourStatus(int) const;
    bool DoesTourStatusExist(int) const;
    Symbol GetNextCity() const;
    Symbol GetTourName() const;
    Symbol GetTourWelcome() const;
    bool AreQuestFiltersEmpty() const;
    Symbol GetQuestFilter(int) const;
    bool HasQuestFilter(Symbol) const;
    void SetQuestFilter(int, Symbol);
    int GetToursPlayed(Symbol) const;
    int GetTourMostStars(Symbol) const;
    void SetMetaScore(int);
    void SetToursPlayedMap(const std::map<Symbol, int>&);
    void SetTourMostStarsMap(const std::map<Symbol, int>&);
    void FakeFill();
    void DumpProperties();

    static int SaveSize(int);

    QuestJournal mQuests; // 0x1c
    TourPropertyCollection mTourProperties; // 0x40
    unsigned int mLastTouchTime; // 0x60
    bool mOnTour; // 0x64
    mutable Symbol m_symTourDesc; // 0x68
    int mNumCompletedGigs; // 0x6c
    std::vector<int> unk70; // 0x70
    Symbol mCurrentQuest; // 0x78
    Symbol mQuestFilters[3]; // 0x7c, 0x80, 0x84
    std::map<Symbol, int> unk88;
    std::map<Symbol, int> unka0;
    int mMetaScore; // 0xb8
    int mNewStars; // 0xbc
    bool mWonQuest; // 0xc0
    int mCurrentGigNum; // 0xc4
    TourPropertyCollection mPerformanceProperties; // 0xc8
};

#endif // TOUR_TOURPROGRESS_H
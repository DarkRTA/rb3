#pragma once
#include "game/BandUserMgr.h"
#include "meta_band/MetaPerformer.h"
#include "ui/UILabel.h"

enum TourSetlistType {
    kTourSetlist_Random = 0,
    kTourSetlist_Custom = 1,
    kTourSetlist_Fixed = 2,
    kTourSetlist_Invalid = 3
};

class GigData {
public:
    GigData() : unk4(0), unk8(0), unkc(0) {}
    Symbol unk0; // 0x0
    int unk4; // 0x4
    int unk8; // 0x8
    int unkc; // 0xc
};

class TourPerformerImpl : public MetaPerformerImpl {
public:
    TourPerformerImpl(BandUserMgr&);
    virtual ~TourPerformerImpl();
    virtual DataNode Handle(DataArray*, bool);
    virtual void CompleteSong(std::vector<BandUser*>&, const BandStatsInfo*, bool);
    virtual bool IsRandomSetList() const;
    virtual bool IsWinning() const;
    virtual void RestartLastSong();
    virtual bool IsLocal() const = 0;
    virtual bool HasWritePermission() const;
    virtual void CompleteQuest();

    Symbol GetCurrentQuest() const;
    int GetTotalQuestStars() const;
    Symbol GetCurrentQuestDisplayName() const;
    Symbol GetCurrentQuestDescription() const;
    Symbol GetCurrentQuestLongDescription() const;
    Symbol GetCurrentQuestFilter() const;
    int GetGigSongCount() const;
    bool GetCurrentQuestFilterIsCustom() const;
    void CleanupGigData();
    const GigData& GetMostRecentGigData() const;
    int GetSongQuestStars() const;
    void HandleSongCompleted(const BandStatsInfo*);
    void UpdateGigDataForSong(Symbol, int);
    void UpdateCompleteTourStats(TourProgress*);
    bool IsQuestWon(Symbol) const;
    int GetQuestSuccessfulSongCount() const;
    int GetBaseSongStars() const;
    int GetTotalSongStars() const;
    Symbol GetCurrentQuestSuccessMessage() const;
    void UpdateTourStats(TourProgress*);
    int GetTotalStarsPossibleForCurrentGig();
    void HandleSongCompleteWithInvalidScore();
    void HandleCheatWinQuest(Symbol);
    int GetTotalGigStars() const;
    void UpdateQuestGoalLabel(UILabel*);
    void UpdateQuestResultLabel(UILabel*);
    void UpdateTourPlayerContributionLabel(UILabel*, BandUser*);

    const BandUserMgr& mUserMgr; // 0x1c
    MetaPerformer* mMetaPerformer; // 0x20
    Symbol mQuestFilter; // 0x24
    TourSetlistType mFilterType; // 0x28
    std::vector<GigData> mGigData; // 0x2c
};
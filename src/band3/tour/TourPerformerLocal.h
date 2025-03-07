#pragma once
#include "game/BandUserMgr.h"
#include "os/Debug.h"
#include "tour/TourPerformer.h"

class TourPerformerLocal : public TourPerformerImpl {
public:
    TourPerformerLocal(BandUserMgr &);
    virtual ~TourPerformerLocal();
    virtual DataNode Handle(DataArray *, bool);
    virtual void SyncSave(BinStream &, unsigned int) const;
    virtual bool IsLocal() const { return 1; }
    virtual bool HasSyncPermission() const { return 1; }
    virtual void SyncLoad(BinStream &, unsigned int) { MILO_ASSERT(false, 35); }
    virtual void CompleteQuest();

    void MakeDirty();
    void SelectVenue();
    void ClearCurrentQuest();
    void ClearCurrentQuestFilter();
    void SetCurrentQuest(Symbol);
    void SetCurrentQuestFilter(Symbol, TourSetlistType);
    void ChooseRandomQuestForGroupAndTier(Symbol, int);
    void InqSongsInFilterData(Symbol, std::map<Symbol, int> &, std::map<Symbol, int> &);
    void GetRandomArtistFromMap(const std::map<Symbol, int> &, int);
    void
    GetRandomQuestFilter(TourProgress *, int, const std::map<Symbol, int> &, const std::map<Symbol, int> &);
    void GetRandomFixedSetlist(TourProgress *, int, Symbol);
    void ChooseQuestFilters();
    bool SanityCheckFilterAgainstType(Symbol, Symbol);
    void SanityCheckQuestFilters();
    void InitializeNextGig();
    void CheatCycleChallenge();
    void CheatCycleSetlist();
};
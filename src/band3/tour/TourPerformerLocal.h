#pragma once
#include "game/BandUserMgr.h"
#include "tour/TourPerformer.h"

class TourPerformerLocal : public TourPerformerImpl {
public:
    TourPerformerLocal(BandUserMgr&);
    virtual ~TourPerformerLocal();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool HasSyncPermission() const;
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool IsLocal() const;
    virtual void CompleteQuest();

    void MakeDirty();
    void SelectVenue();
    void ClearCurrentQuest();
    void ClearCurrentQuestFilter();
    void SetCurrentQuest(Symbol);
    void SetCurrentQuestFilter(Symbol, TourSetlistType);
};
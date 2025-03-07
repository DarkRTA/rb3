#pragma once

#include "os/Debug.h"
#include "tour/TourPerformer.h"

class TourPerformerRemote : public TourPerformerImpl {
    TourPerformerRemote(BandUserMgr &);
    virtual ~TourPerformerRemote();
    virtual void SyncLoad(BinStream &, uint);
    virtual void OnSynchronized(uint);
    virtual bool IsLocal() const { return false; }
    virtual void SelectSong(int, Symbol) { MILO_ASSERT(0, 29); } // wat
    virtual bool HasSyncPermission() const { return false; }
    virtual void SyncSave(BinStream &, uint) const { MILO_ASSERT(false, 33); }
};

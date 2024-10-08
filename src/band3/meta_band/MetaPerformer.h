#pragma once
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "meta_band/BandSongMgr.h"

class MetaPerformer : public Synchronizable, public MsgSource {
public:
    MetaPerformer(const BandSongMgr&, const char*);
    virtual ~MetaPerformer();
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual DataNode Handle(DataArray*, bool);

    static MetaPerformer* Current();
};
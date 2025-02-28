#pragma once
#include "meta/StoreOffer.h"

class BandStoreOffer : public StoreOffer {
public:
    BandStoreOffer(const StorePackedOfferBase *, SongMgr *, bool);
    virtual ~BandStoreOffer() {}
    virtual DataNode Handle(DataArray *, bool);
    virtual bool IsCompletelyUnavailable() const;
};
#pragma once
#include "meta/StoreOffer.h"

class BandStoreOffer : public StoreOffer {
public:
    BandStoreOffer(const StorePackedOfferBase*, SongMgr*, bool);
};
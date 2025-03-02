#include "meta_band/BandStoreOffer.h"
#include "meta/StoreOffer.h"
#include "meta/StorePackedMetadata.h"

BandStoreOffer::BandStoreOffer(const StorePackedOfferBase *base, SongMgr *mgr, bool b)
    : StoreOffer(base, mgr, b) {
    mPackedRbnOffer->GetPackedSong(0);
    mPackedOffer->GetPackedSong(0);
}

bool BandStoreOffer::IsCompletelyUnavailable() const {
    return StoreOffer::IsCompletelyUnavailable();
}

BEGIN_HANDLERS(BandStoreOffer)
    HANDLE_SUPERCLASS(StoreOffer)
    HANDLE_CHECK(0x79)
END_HANDLERS
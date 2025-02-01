#include "meta_band/BandStoreOffer.h"
#include "meta/StorePackedMetadata.h"

BandStoreOffer::BandStoreOffer(const StorePackedOfferBase *base, SongMgr *mgr, bool b)
    : StoreOffer(base, mgr, b) {
    mPackedRbnOffer->GetPackedSong(0);
    mPackedOffer->GetPackedSong(0);
}
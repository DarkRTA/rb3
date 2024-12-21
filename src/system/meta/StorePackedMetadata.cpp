#include "meta/StorePackedMetadata.h"
#include "meta/StoreOffer.h"

String StorePackedOfferBase::GetOfferId() const {
    String ret;
    ret.reserve(0x11);
    memcpy((void*)ret.c_str(), mId, 16);
    char* ptr = (char*)ret.c_str();
    ptr[16] = 0;
    return ret;
}

String StorePackedOfferBase::GetUpgradeId() const {
    String ret;
    ret.reserve(0x11);
    memcpy((void*)ret.c_str(), mUpgradeId, 16);
    char* ptr = (char*)ret.c_str();
    ptr[16] = 0;
    return ret;
}
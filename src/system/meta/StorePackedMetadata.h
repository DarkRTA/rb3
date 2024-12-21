#pragma once
#include "obj/Object.h"

class StorePackedMetadata : public Hmx::Object {
public:
    StorePackedMetadata(){}
    ~StorePackedMetadata(){}
    virtual DataNode Handle(DataArray*, bool);

    int GetOfferStatus(const class StorePackedOfferBase*);
};

extern StorePackedMetadata TheStoreMetadata;
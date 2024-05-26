#ifndef METABAND_ASSET_H
#define METABAND_ASSET_H

#include "system/obj/Data.h"

class Asset {
    Asset(DataArray*, int);
    virtual ~Asset();
    Symbol GetDescription() const;
    void HasFinishes();
    void GetFinishes(std::vector<Symbol>&) const;
    void GetFinish(int) const;
    Symbol GetHint() const;

    Symbol mName; // 0x04
};

#endif // METABAND_ASSET_H
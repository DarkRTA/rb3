#ifndef METABAND_ASSET_H
#define METABAND_ASSET_H

#include "system/obj/Data.h"
#include "types.h"

class Asset {
    Asset(DataArray*, int);
    virtual ~Asset();
    Symbol GetDescription() const;
    bool HasFinishes();
    void GetFinishes(std::vector<Symbol>&) const;
    Symbol GetFinish(int) const;
    Symbol GetHint() const;

    Symbol mName; // 0x04
    int unk_0x8, unk_0xC, unk_0x10;
    std::vector<Symbol> mFinishes; // 0x14
    u8 unk_0x1C, unk_0x1D;
    int unk_0x20;
};

#endif // METABAND_ASSET_H
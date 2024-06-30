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
    int mType, mGender, mBoutique;
    std::vector<Symbol> mFinishes; // 0x14
    bool mPatchable, mHidden;
    int mIndex;
};

#endif // METABAND_ASSET_H
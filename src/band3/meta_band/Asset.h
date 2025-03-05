#pragma once
#include "meta_band/AssetTypes.h"
#include "system/obj/Data.h"
#include "types.h"

class Asset {
public:
    Asset(DataArray *, int);
    virtual ~Asset();
    Symbol GetDescription() const;
    bool HasFinishes();
    void GetFinishes(std::vector<Symbol> &) const;
    Symbol GetFinish(int) const;
    Symbol GetHint() const;
    Symbol GetName() const { return mName; }
    AssetType GetType() const { return mType; }
    AssetGender GetGender() const { return mGender; }
    int GetIndex() const { return mIndex; }
    bool IsHidden() const { return mHidden; }
    AssetBoutique GetBoutique() const { return mBoutique; }

    Symbol mName; // 0x04
    AssetType mType; // 0x08
    AssetGender mGender; // 0x0c
    AssetBoutique mBoutique; // 0x10
    std::vector<Symbol> mFinishes; // 0x14
    bool mPatchable; // 0x1c
    bool mHidden; // 0x1d
    int mIndex; // 0x20
};

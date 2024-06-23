#pragma once

#include "obj/Data.h"
class TourProperty {
    public:
    TourProperty(const DataArray*);
    virtual ~TourProperty();
    void Configure(const DataArray*);
    Symbol GetName() const;
    float GetDefaultValue() const;
    float GetMinValue() const;
    float GetMaxValue() const;
    bool IsAutomatic() const;

    Symbol mName; // 0x4
    u8 unk_0x8, unk_0x9;
    float mDefaultValue; // 0xC
    float mMinValue; // 0x10
    float mMaxValue; // 0x14
    bool mIsAutomatic; // 0x18
};

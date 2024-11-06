#pragma once
#include "obj/Data.h"
#include <map>

class TrackerMultiplierMap {
public:
    class MultiplierEntry {
    public:
        float unk0;
        int unk4;
    };

    TrackerMultiplierMap();
    ~TrackerMultiplierMap();

    void InitFromDataArray(const DataArray*);
    float GetMultiplier(float) const;
    int GetMultiplierIndex(float) const;
    const MultiplierEntry& FindEntry(float) const;
    float GetPercentOfMaxMultiplier(float) const;

    float unk0; // 0x0
    std::map<float, MultiplierEntry> unk4; // 0x4
};
#include "game/TrackerUtils.h"
#include "math/MathFuncs.h"

TrackerMultiplierMap::TrackerMultiplierMap() : unk0(-1.0f) {

}

TrackerMultiplierMap::~TrackerMultiplierMap(){

}

void TrackerMultiplierMap::InitFromDataArray(const DataArray* iDataArray){
    unk4.clear();
}

float TrackerMultiplierMap::GetMultiplier(float f) const {
    return FindEntry(f).unk0;
}

int TrackerMultiplierMap::GetMultiplierIndex(float f) const {
    return FindEntry(f).unk4;
}

float TrackerMultiplierMap::GetPercentOfMaxMultiplier(float f) const {
    return Max(f / unk0, 1.0f);
}

const TrackerMultiplierMap::MultiplierEntry& TrackerMultiplierMap::FindEntry(float f) const {
    return unk4.find(f)->second;
}
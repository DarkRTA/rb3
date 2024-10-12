#pragma once
#include "obj/Data.h"
#include "utl/Symbol.h"
#include <map>

class TourWeightManager {
public:
    TourWeightManager();
    virtual ~TourWeightManager();
    virtual void Init(const DataArray*);

    void Cleanup();
    void ConfigureQuestWeightData(DataArray*);

    std::map<Symbol, float> unk4;
};
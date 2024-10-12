#pragma once
#include "TourDesc.h"
#include "tour/TourProperty.h"
#include "utl/Symbol.h"
class Tour {
public:
    bool HasTourProperty(Symbol) const;
    TourProperty* GetTourProperty(Symbol) const;
    void UpdateProgressWithCareerData();
    TourDesc* GetTourDesc(Symbol) const;
    Symbol GetTourStatusForStarCount(int, int) const;
    int GetStarsForTourStatus(Symbol) const;
    bool DoesTourStatusExist(int, int) const;
};

extern Tour* TheTour;

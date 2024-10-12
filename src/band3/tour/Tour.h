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
};

extern Tour* TheTour;

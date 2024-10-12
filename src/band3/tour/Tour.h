#pragma once

#include "tour/TourProperty.h"
#include "utl/Symbol.h"
class Tour {
public:
    bool HasTourProperty(Symbol) const;
    TourProperty* GetTourProperty(Symbol) const;
};

extern Tour* TheTour;

#pragma once

#include "tour/TourProperty.h"
#include "utl/Symbol.h"
class Tour {
    public:
    TourProperty* GetTourProperty(Symbol) const;
};

extern Tour* TheTour;

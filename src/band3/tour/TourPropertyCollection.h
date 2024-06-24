#pragma once

#include "utl/Symbol.h"
class TourPropertyCollection {
    public:
    float GetPropertyValue(Symbol) const;
    void SetPropertyValue(Symbol, float);
};

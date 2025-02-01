#pragma once
#include "obj/Data.h"
#include <set>

class TourGameModifier {
public:
    TourGameModifier();
    virtual ~TourGameModifier();
    void Init(const DataArray *);

    std::set<Symbol> mModifiers;
};

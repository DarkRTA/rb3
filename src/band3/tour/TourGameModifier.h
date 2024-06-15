#ifndef TOUR_TOURGAMEMODIFIER_H
#define TOUR_TOURGAMEMODIFIER_H

#include "obj/Data.h"
#include <set>

class TourGameModifier {
    public:
    TourGameModifier();
    virtual ~TourGameModifier();
    void Init(const DataArray*);

    std::set<Symbol> mModifiers;
};

#endif // TOUR_TOURGAMEMODIFIER_H

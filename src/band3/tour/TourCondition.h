#ifndef TOUR_TOURCONDITION_H
#define TOUR_TOURCONDITION_H

#include "obj/Data.h"
#include "tour/TourProgress.h"

class TourCondition {
    public:
    TourCondition();
    virtual ~TourCondition();

    void Init(const DataArray*);
    bool IsMet(const TourProgress&) const;
    bool IsConditionMet(const TourProgress&, const DataArray*) const;

    DataArray* mConds;
};

#endif //TOUR_TOURCONDITION_H

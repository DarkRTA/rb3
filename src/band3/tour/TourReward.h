#ifndef TOUR_TOURREWARD_H
#define TOUR_TOURREWARD_H

#include "obj/Data.h"

class TourReward {
    public:
    TourReward();
    virtual ~TourReward();
    void Init(const DataArray*);

    DataArray* mRewards;
};

#endif // TOUR_TOURREWARD_H

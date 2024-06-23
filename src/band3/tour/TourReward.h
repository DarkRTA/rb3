#pragma once

#include "obj/Data.h"
#include "tour/TourProgress.h"
#include "tour/TourPropertyCollection.h"

class TourReward {
    public:
    TourReward();
    virtual ~TourReward();
    void Init(const DataArray*);
    void Apply(TourProgress*) const;
    void ApplyRewardEntry(TourProgress*, DataArray*) const;
    void ApplyRewardEntry(TourProgress*, TourPropertyCollection&, DataArray*) const;
    void ApplyRewardValue(TourProgress*, TourPropertyCollection&, Symbol, float) const;
    void ApplyAddReward(TourProgress*, TourPropertyCollection&, DataArray*) const;
    void ApplySubtractReward(TourProgress*, TourPropertyCollection&, DataArray*) const;
    void ApplyMultiplyReward(TourProgress*, TourPropertyCollection&, DataArray*) const;
    void ApplyDivideReward(TourProgress*, TourPropertyCollection&, DataArray*) const;
    void ValidatePropertyModification(Symbol) const;

    DataArray* mRewards;
};


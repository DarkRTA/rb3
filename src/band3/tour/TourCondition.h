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
    bool IsComparisonConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsAndConditionMet(const TourProgress&, const DataArray*) const;
    bool IsOrConditionMet(const TourProgress&, const DataArray*) const;
    bool IsNotConditionMet(const TourProgress&, const DataArray*) const;
    bool IsGreaterConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsLessConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsGreaterEqualConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsLessEqualConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsEqualConditionMet(const TourPropertyCollection&, const DataArray*) const;
    bool IsNotEqualConditionMet(const TourPropertyCollection&, const DataArray*) const;

    const DataArray* mConds; // 0x4
};

#endif //TOUR_TOURCONDITION_H

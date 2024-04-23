#ifndef TOUR_TOURQUESTGAMERULES_H
#define TOUR_TOURQUESTGAMERULES_H

#include "obj/Data.h"
#include "tour/TourGameModifier.h"
#include "tour/TourGameRules.h"

class TourQuestGameRules : public TourGameRules {
public:
    TourQuestGameRules();
    virtual ~TourQuestGameRules();
    virtual void Init(const DataArray*);
    TourGameModifier mModifier;
};

#endif // TOUR_TOURQUESTGAMERULES_H

#ifndef TOUR_TOURPROGRESS_H
#define TOUR_TOURPROGRESS_H

#include "obj/Object.h"
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/QuestJournal.h"

class TourProgress : public TourSavable, public FixedSizeSaveable {
    public:
    TourProgress();
    virtual ~TourProgress();
    virtual DataNode Handle(DataArray*, bool);

    void HandleTourRewardApplied();
    void SetOnTour(bool);
    int SecBetweenUploads() const;

    QuestJournal mQuests;
};

#endif // TOUR_TOURPROGRESS_H

#ifndef TOUR_TOURPROGRESS_H
#define TOUR_TOURPROGRESS_H

#include "obj/Object.h"
#include "tour/TourPropertyCollection.h"
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/QuestJournal.h"

class TourProgress : public TourSavable, public FixedSizeSaveable {
public:
    TourProgress();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourProgress();
    virtual int SecBetweenUploads() const;
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void HandleTourRewardApplied();
    void SetOnTour(bool);
    TourPropertyCollection& GetPerformanceProperties();
    TourPropertyCollection& GetTourProperties();

    QuestJournal mQuests;
};

#endif // TOUR_TOURPROGRESS_H

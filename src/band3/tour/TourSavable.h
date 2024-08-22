#ifndef TOUR_TOURSAVABLE_H
#define TOUR_TOURSAVABLE_H

#include "obj/Object.h"

class TourSavable : public virtual Hmx::Object {
    public:
    TourSavable();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourSavable();
    virtual bool IsDirtySave();
    virtual bool IsUploadNeeded();
    virtual int SecBetweenUploads() const;
    virtual void SetDirty(bool, int);
};

#endif // TOUR_TOURSAVABLE_H

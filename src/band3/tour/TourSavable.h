#ifndef TOUR_TOURSAVABLE_H
#define TOUR_TOURSAVABLE_H
#include "os/DateTime.h"
#include "obj/Object.h"

class TourSavable : public virtual Hmx::Object {
public:
    TourSavable();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourSavable();
    virtual bool IsDirtySave() const;
    virtual bool IsUploadNeeded() const;
    virtual int SecBetweenUploads() const = 0;
    virtual void SetDirty(bool, int);
    virtual void UploadComplete();

    bool unk8;
    bool unk9;
    bool unka;
    DateTime unkb;
    bool unk11;
    bool unk12;
};

#endif // TOUR_TOURSAVABLE_H

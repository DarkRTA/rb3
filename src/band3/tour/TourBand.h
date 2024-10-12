#pragma once
#include "tour/TourSavable.h"
#include "meta/FixedSizeSaveable.h"

class BandProfile;

class TourBand : public TourSavable, public FixedSizeSaveable {
public:
    TourBand(BandProfile*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~TourBand();
    virtual bool IsUploadNeeded() const;
    virtual int SecBetweenUploads() const;
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);
};
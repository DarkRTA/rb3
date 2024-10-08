#pragma once
#include "tour/TourChar.h"

class TourCharLocal : public TourChar {
public:
    TourCharLocal();
    virtual DataNode Handle(DataArray*, bool);
    virtual RndTex* GetTexAtPatchIndex(int, bool) const;
    virtual ~TourCharLocal();
    virtual void SetDirty(bool, int);
};
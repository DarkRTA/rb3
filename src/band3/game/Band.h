#pragma once
#include "obj/Object.h"

class BandUser;
class BeatMaster;

class Band : public Hmx::Object {
public:
    Band(bool, int, BandUser*, BeatMaster*);
    virtual ~Band();
    virtual DataNode Handle(DataArray*, bool);

    int EnergyMultiplier() const;
    int EnergyCrowdBoost() const;
    void ForceStars(int);
};
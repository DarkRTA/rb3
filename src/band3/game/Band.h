#pragma once
#include "game/Performer.h"
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
    void UpdateBonusLevel(float);
    int DeployBandEnergy(BandUser*);
    int GetMultiplier(bool, int&, int&, int&) const;
    Performer* MainPerformer() const;
    Performer* GetBand() const;
};
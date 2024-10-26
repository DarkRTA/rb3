#pragma once
#include "game/Performer.h"
#include "obj/MsgSource.h"

class BeatMaster;

class Player : public Performer, public MsgSource {
public:
    Player(BandUser*, Band*, int, BeatMaster*);
    virtual DataNode Handle(DataArray*, bool);

    void DeterminePerformanceAwards();
};
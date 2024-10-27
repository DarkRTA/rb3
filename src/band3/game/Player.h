#pragma once
#include "beatmatch/TrackType.h"
#include "game/Performer.h"
#include "obj/MsgSource.h"

class BeatMaster;

class Player : public Performer, public MsgSource {
public:
    Player(BandUser*, Band*, int, BeatMaster*);
    virtual DataNode Handle(DataArray*, bool);

    void DeterminePerformanceAwards();
    TrackType GetTrackType() const { return unk_tracktype; }

    int unk_player;
    TrackType unk_tracktype;
};
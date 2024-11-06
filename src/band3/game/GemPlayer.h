#pragma once
#include "beatmatch/BeatMatchSink.h"
#include "game/Player.h"

class BandPerformer;

class GemPlayer : public Player, public BeatMatchSink {
public:
    GemPlayer(BandUser*, BeatMaster*, Band*, int, BandPerformer*);

    int GetRGFret(int) const;
    int GetMaxSlots() const;
};
#pragma once
#include "game/Player.h"
#include "rndobj/Overlay.h"

class VocalPlayer : public Player, public RndOverlay::Callback {
public:
    VocalPlayer(BandUser *, BeatMaster *, Band *, int, Performer *, int);
};
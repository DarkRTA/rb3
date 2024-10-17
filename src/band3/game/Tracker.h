#ifndef GAME_TRACKER_H
#define GAME_TRACKER_H

#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "game/BandUser.h"
#include "types.h"

struct TrackerDesc {
    int mType; // 0x0 - enum TrackerType
    LocalBandUser* mUser;  // 0x04 - LocalBandUser*
    Symbol symbol3;  // 0x08
    int unkc;        // 0x0c
    int unk10;
    float unk14;
    std::vector<float> unk18;
};

class Tracker {

};

#endif // GAME_TRACKER_H

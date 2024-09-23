#ifndef GAME_TRACKER_H
#define GAME_TRACKER_H

#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "os/User.h"
#include "types.h"

struct TrackerDesc {
    Symbol symbol1;  // 0x00
    Symbol symbol2;  // 0x04
    Symbol symbol3;  // 0x08
    int int1;        // 0x0c
};

class Tracker {

};

#endif // GAME_TRACKER_H

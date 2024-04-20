#ifndef BEATMATCH_GAMEGEMLIST_H
#define BEATMATCH_GAMEGEMLIST_H
#include "beatmatch/GameGem.h"
#include <vector>

class GameGemList {
public:
    GameGemList(int);
    int mHopoThreshold;
    std::vector<GameGem*> mGems;
};

#endif

#ifndef BEATMATCH_GAMEGEMLIST_H
#define BEATMATCH_GAMEGEMLIST_H
#include "beatmatch/GameGem.h"
#include <vector>

class GameGemList {
public:
    GameGemList(int);
    void Clear();
    bool AddMultiGem(const MultiGemInfo&);
    bool AddRGGem(const RGGemInfo&);
    void MergeChordGems();
    void Finalize();
    void CopyFrom(const GameGemList*);

    int mHopoThreshold;
    std::vector<GameGem*> mGems;
};

#endif

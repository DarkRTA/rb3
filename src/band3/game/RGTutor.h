#pragma once
#include "beatmatch/GameGem.h"
#include "game/Defines.h"
#include <map>

class RGTutor {
public:
    RGTutor();
    ~RGTutor();
    void Clear();
    void Hit(int, const GameGem &);
    bool Miss(int, const GameGem &, Difficulty);
    int GetMapKey(int, const GameGem &) const;
    void Loop();

    int mNumPlays; // 0x0
    std::map<int, int> unk4; // 0x4
};
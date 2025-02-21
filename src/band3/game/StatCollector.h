#pragma once
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/GameGem.h"
#include "game/Stats.h"

class GemPlayer;

class StatCollector {
public:
    StatCollector(GemPlayer &);

    void Reset();
    void Poll(float);
    void HitGem(float, const GameGem &, int, unsigned int, GemHitFlags);
    void PassGem(float, const GameGem &, int);
    void GemPassedNow(float, const GameGem &, int, bool);
    void CheckRolls(int, bool);
    void CheckKickGem(const GameGem &, int, bool);

    GemPlayer *mGemPlayer; // 0x0
    Stats *mStats; // 0x4
    bool unk0x8; // 0x8
    bool unk0x9; // 0x9
};
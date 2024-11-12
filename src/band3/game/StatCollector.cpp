#include "StatCollector.h"
#include "GemPlayer.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/TrackType.h"
#include "utl/TimeConversion.h"

StatCollector::StatCollector(GemPlayer &player)
    : mGemPlayer(&player), mStats(&player.mStats) {
    Reset();
}

void StatCollector::Reset() {
    unk0x8 = false;
    unk0x9 = false;
}

void StatCollector::Poll(float time) {
    if (unk0x8 != false) {
        int tick = MsToTick(time);
        CheckRolls(tick, true);
    }
}

void StatCollector::HitGem(
    float time, const GameGem &gameGem, int i, unsigned int, GemHitFlags flags
) {
    GemPassedNow(time, gameGem, i, true);
}

void StatCollector::PassGem(float time, const GameGem &gameGem, int i) {
    GemPassedNow(time, gameGem, i, false);
}

void StatCollector::GemPassedNow(float time, const GameGem &gameGem, int i, bool b) {
    int tick = MsToTick(time);
    CheckRolls(tick, b);
    CheckKickGem(gameGem, i, b);
}

void StatCollector::CheckRolls(int tick, bool b) {}

void StatCollector::CheckKickGem(const GameGem &gameGem, int i, bool b) {
    if (mGemPlayer->mTrackType == kTrackDrum) {
    }
}
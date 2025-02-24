#include "StatCollector.h"
#include "GemPlayer.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/TrackType.h"
#include "utl/TimeConversion.h"

StatCollector::StatCollector(GemPlayer &player)
    : mGemPlayer(player), mStats(player.mStats) {
    Reset();
}

void StatCollector::Reset() {
    unk0x8 = false;
    unk0x9 = false;
}

void StatCollector::Poll(float time) {
    if (unk0x8) {
        CheckRolls(MsToTickInt(time), true);
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
    CheckRolls(MsToTickInt(time), b);
    CheckKickGem(gameGem, i, b);
}

void StatCollector::CheckRolls(int tick, bool b) {
    bool b2 = false;
    for (int i = 0; i < mGemPlayer.GetNumRolls(); i++) {
        int start, end;
        mGemPlayer.GetRollInfo(i, start, end);
        if (tick < start) {
            break;
        }
        if (tick < end) {
            b2 = true;
            break;
        }
    }
    bool old = unk0x8;
    if (!old && b2) {
        unk0x8 = true;
        unk0x9 = false;
    } else if (old && !b2) {
        unk0x8 = false;
        mStats.AddRoll(!unk0x9);
    } else if (old) {
        unk0x9 |= !b;
    }
}

void StatCollector::CheckKickGem(const GameGem &gameGem, int i, bool b) {
    if (mGemPlayer.GetTrackType() == kTrackDrum && gameGem.GetSlot() == 0) {
        mStats.m0x68++;
        if (b) {
            mStats.m0x6c++;
        }
    }
}
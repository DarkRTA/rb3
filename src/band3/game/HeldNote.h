#ifndef GAME_HELDNOTE_H
#define GAME_HELDNOTE_H

#include "beatmatch/GameGem.h"
#include "beatmatch/TrackType.h"

class HeldNote {
public:
    HeldNote();
    HeldNote(TrackType, int, const GameGem &, unsigned int);

    const GameGem *GetGem();
    unsigned int GetGemSlots() const;
    bool IsDone() const;
    bool HeldCompletely() const;
    double SetHoldTime(float);

    float GetPointFraction();

    float GetAwardedPercent() const;
    float GetAwardedPoints() const;

    void ReleaseSlot(int);

    const GameGem *mGameGem;
    int unk_0x4;
    TrackType mTrackType;
    float unk_0xc;
    int unk_0x10;
    float unk_0x14;
    int unk_0x18;
    unsigned int unk_0x1c;
    bool unk_0x20;
};

#endif // GAME_HELDNOTE_H
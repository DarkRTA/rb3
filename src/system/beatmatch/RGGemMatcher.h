#pragma once
#include "beatmatch/RGState.h"
#include "beatmatch/GameGem.h"

enum RGMatchType {
    i,
    d,
    k
};

// no clue what this is
// gets referenced in AddFretHistory, maybe the pair is time and fret?
struct RGGemMatcherPair {
    RGGemMatcherPair() : f(0.0f), i(-1) {}
    float f;
    int i;
};

class RGGemMatcher {
public:
    RGGemMatcher();
    void Reset();
    void Swing(int, float);
    void FretDown(int, float);
    void FretUp(int, float);
    bool
    FretMatch(const GameGem &, float, float, float, float, bool, bool, RGMatchType) const;
    bool FretMatchImpl(
        const GameGem &, float, float, float, float, bool, bool, RGMatchType
    ) const;
    RGState *GetState();
    const RGState *GetState() const;
    void ClearStringSwings();
    void ClearNonStrums();
    bool FretHistoryMatch(int, int, float, float, RGMatchType) const;
    void AddFretHistory(int, int, float);

    RGState mState; // 0x0
    float mStringSwings[6]; // 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c
    float mStringNonStrum[6]; // 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44
    RGGemMatcherPair pairs[6][4]; // 0x48
};

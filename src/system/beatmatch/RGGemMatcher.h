#ifndef BEATMATCH_RGGEMMATCHER_H
#define BEATMATCH_RGGEMMATCHER_H
#include "beatmatch/RGState.h"
#include "beatmatch/GameGem.h"

enum RGMatchType {
    i, d, k
};

// no clue what this is
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
    bool FretMatch(const GameGem&, float, float, float, float, bool, bool, RGMatchType) const;
    bool FretMatchImpl(const GameGem&, float, float, float, float, bool, bool, RGMatchType) const;
    RGState* GetState();
    const RGState* GetState() const;
    void ClearStringSwings();
    void ClearNonStrums();
    bool FretHistoryMatch(int, int, float, float, RGMatchType) const;
    void AddFretHistory(int, int, float);

    RGState mState;
    float mStringSwings[6];
    float mStringNonStrum[6];
    RGGemMatcherPair pairs[24];
};

#endif

#ifndef GAME_FRETHAND_H
#define GAME_FRETHAND_H
#include "types.h"

#define kNumFingers 4
class GameGem;

class FretFinger {
public:
    int mFret; // 0x0
    int mLowString; // 0x4
    int mHighString; // 0x8
};

class FretHand { // 0x30
public:
    FretHand();
    ~FretHand();

    void Reset();
    void GetFinger(uint id, int&, int&, int&) const;
    void SetFinger(uint id, int, int, int);
    void SetFingers(const GameGem&);
    int GetFret(int) const;
    bool BarAll(const GameGem&);

    FretFinger mFinger[4]; // 0x0, 0xc, 0x18, 0x24
};

#endif // GAME_FRETHAND_H

#ifndef GAME_FRETHAND_H
#define GAME_FRETHAND_H
#include "types.h"

#define kNumFingers 4
class GameGem;


class FretHand { // 0x30
    FretHand();
    ~FretHand();

    void Reset();
    void GetFinger(uint id, int&, int&, int&) const;
    void SetFinger(uint id, int, int, int);
    void SetFingers(const GameGem&);
    int  GetFret(int) const;
    void BarAll(const GameGem&);

    int test[12];
};

#endif // GAME_FRETHAND_H

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "obj/Object.h"

class Game : public Hmx::Object {
    public:
    Game();
    virtual ~Game();

    void SetPaused(bool, bool, bool);

    bool mIsPaused; // 0x68 iunno
};

Game* /*you just lost*/ TheGame;

#endif // GAME_GAME_H

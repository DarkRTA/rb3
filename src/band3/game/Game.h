#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "obj/Object.h"
#include "types.h"

class Game : public Hmx::Object {
    public:
    Game();
    virtual ~Game();

    void SetPaused(bool, bool, bool);
    void SetGameOver(bool);
    bool ResumedNoScore() const;

    u8 pad[0x4C];
    bool mIsPaused; // 0x68 iunno
};

extern Game* /*you just lost*/ TheGame;

#endif // GAME_GAME_H

#ifndef RB3_GAMEMODE_HPP
#define RB3_GAMEMODE_HPP
#include "msgsource.hpp"
#include "symbol.hpp"

class GameMode : public MsgSource {
public:
    GameMode();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~GameMode();

    void SetMode(Symbol);
    bool InMode(Symbol);
    DataNode OnSetMode(const DataArray*);

    Symbol curMode;
};

void GameModeInit();

#endif

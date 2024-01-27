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
    int unk20, unk24, unk28, unk2c, unk30, unk34, unk38, unk3c, unk40, unk44, unk48, unk4c, unk50, unk54, unk58, unk5c, unk60, unk64, unk68, unk6c, unk70;
};

void GameModeInit();

#endif

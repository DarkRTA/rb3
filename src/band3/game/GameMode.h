#pragma once
#include "obj/MsgSource.h"

class GameMode : public MsgSource {
public:
    GameMode();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~GameMode();
};

extern GameMode* TheGameMode;
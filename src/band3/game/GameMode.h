#pragma once
#include "obj/MsgSource.h"

class GameMode : public MsgSource {
public:
    GameMode();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~GameMode();

    void SetMode(Symbol);
    bool InMode(Symbol);
    DataNode OnSetMode(const DataArray*);

    Symbol mMode; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
    int unk28; // 0x28
    int unk2c; // 0x2c
    int unk30; // 0x30
    int unk34; // 0x34
    int unk38; // 0x38
    int unk3c; // 0x3c
    int unk40; // 0x40
    int unk44; // 0x44
    int unk48; // 0x48
    int unk4c; // 0x4c
    int unk50; // 0x50
    int unk54; // 0x54
    int unk58; // 0x58
    int unk5c; // 0x5c
    int unk60; // 0x60
    int unk64; // 0x64
    int unk68; // 0x68
    int unk6c; // 0x6c
    int unk70; // 0x70
};

void GameModeInit();

extern GameMode* TheGameMode;
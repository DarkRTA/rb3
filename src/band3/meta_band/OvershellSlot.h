#pragma once
#include "obj/Object.h"

class OvershellPanel;
class OvershellDir;
class BandUserMgr;
class SessionMgr;

enum OvershellOverrideFlow {
    kOverrideFlow_None = 0,
    kOverrideFlow_SongSettings = 1,
    kOverrideFlow_RegisterOnline = 2
};

class OvershellSlot : public Hmx::Object {
public:
    OvershellSlot(int, OvershellPanel*, OvershellDir*, BandUserMgr*, SessionMgr*);
    virtual ~OvershellSlot();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SetTypeDef(DataArray*);
    virtual class ObjectDir* DataDir();

    bool InOverrideFlow(OvershellOverrideFlow) const;

    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    int unk2c;
    OvershellPanel* unk30;
    BandUserMgr* unk34;
    SessionMgr* unk38;
    int unk3c;
    std::vector<int> unk40;
    std::vector<int> unk48;
    OvershellDir* unk50;
    bool unk54;
    bool unk55;
    Symbol unk58;
    bool unk5c;
    bool unk5d;
    bool unk5e;
    std::vector<int> unk60;
    int unk68, unk6c;
    int unk70, unk74, unk78, unk7c;
    bool unk80;
    bool unk81;
    int unk84;
    int unk88;
};
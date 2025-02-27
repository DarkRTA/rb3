#pragma once
#include "obj/Data.h"
#include "obj/Object.h"
#include "game/BandUser.h"

class PresenceMgr : public Hmx::Object {
public:
    PresenceMgr();
    virtual ~PresenceMgr() {}
    virtual DataNode Handle(DataArray *, bool);

    void UpdatePresence();
    Symbol GetPresenceMode();
    int GetPresenceContextFromMode(Symbol, bool);
    int GetPlayModeContextFromUser(const LocalBandUser *, bool);

    DataNode OnPresenceChange(DataArray *);

    DataArray *unk1c;
    DataArray *unk20;
    int unk24;
    Symbol unk28;
    std::vector<Symbol> unk2c;
    int unk34;
    bool unk38;
    bool unk39;
    int unk3c;
};

extern PresenceMgr ThePresenceMgr;
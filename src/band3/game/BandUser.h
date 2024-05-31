#ifndef GAME_BANDUSER_H
#define GAME_BANDUSER_H

#include "game/Defines.h"
#include "meta_band/GameplayOptions.h"
#include "os/User.h"
#include "types.h"

class BandUser : public virtual User {
    BandUser();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~BandUser();

public:
    ControllerType GetControllerType() const;
    TrackType GetTrackType() const;
    Symbol GetTrackSym() const;

private:
    Difficulty unk_0x8;
    u8 unk_0xC;
    int unk_0x10, unk_0x14;
    u8 unk_0x18, unk_0x19;
    int unk_0x1C, unk_0x20;
    class String unk_0x24;
    int unk_0x30;
    GameplayOptions unk_0x34;
    u8 unk_0x70;
    Symbol unk_0x74;
    float unk_0x78;
    int unk_0x7C, unk_0x80;
    u8 unk_0x84, unk_0x85, unk_0x86;
};

class LocalBandUser : public BandUser {

};

#endif // GAME_BANDUSER_H

#include "BandUser.h"
#include "game/Defines.h"
#include "utl/Symbols.h"

BandUser::BandUser() : unk_0x8(DefaultDifficulty()), unk_0xC(0), unk_0x10(10), unk_0x14(5), unk_0x18(0), unk_0x19(0), unk_0x1C(10),
    unk_0x20(5), unk_0x30(0), unk_0x70(0), unk_0x78(0), unk_0x7C(0), unk_0x80(0), unk_0x84(0),
    unk_0x85(0), unk_0x86(0) { unk_0x74 = none; }

BandUser::~BandUser() { }
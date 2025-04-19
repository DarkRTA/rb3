#pragma once

#include "Platform/InetAddress.h"
#include "types.h"
#include "Platform/BerkeleySocketDriver.h"

namespace Quazal {
    class IOCompletionContext {
    public:
        u8 *unk0;
        u32 unk4;
        s32 unk8;
        BerkeleySocket *unkC;
        InetAddress *unk10;
        s8 unk14;
        s8 unk15;
        s32 unk18;
        void *unk1C;

        void Reset();
    };
}
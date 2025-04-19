#pragma once

#include "types.h"

namespace Quazal {

    class BerkeleySocket {
    public:
        virtual s32 unk8(bool);
        virtual BerkeleySocket *unkC();
        virtual s32 unk10(u32);
        virtual s32 unk14(u8 *, u32, s32 *, s32 *); // recv
        virtual s32 unk18(u8 *, u32, s32 *, s32 *); // send
        virtual void unk1C();
        virtual s32 unk20(u8 *, u32, s32 *); // recv
        virtual s32 unk24(u8 *, u32, s32 *); // send
    };

    class BerkeleySocketDriver : public BerkeleySocket {
    public:
    };
}
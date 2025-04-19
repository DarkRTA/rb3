#include "Platform/InetAddress.h"
#include "types.h"

class IOResult {
public:
    virtual s32 unk8(bool);
    virtual IOResult *unkC();
    virtual s32 unk10(u32);
    virtual s32 unk14(u8 *, u32, s32 *, s32 *); // recv
    virtual s32 unk18(u8 *, u32, s32 *, s32 *); // send
    virtual void unk1C();
    virtual s32 unk20(u8 *, u32, s32 *); // recv
    virtual s32 unk24(u8 *, u32, s32 *); // send
};

namespace Quazal {
    class IOCompletionContext {
    public:
        u8 *unk0;
        u32 unk4;
        s32 unk8;
        IOResult *unkC;
        InetAddress *unk10;
        s8 unk14;
        s8 unk15;
        s32 unk18;
        void *unk1C;

        void Reset();
    };
}
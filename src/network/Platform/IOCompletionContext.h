#include "Platform/InetAddress.h"
#include "types.h"
#include "Platform/Socket.h"

namespace Quazal {
    class IOCompletionContext {
    public:
        u8 *unk0;
        u32 unk4;
        s32 unk8;
        s32 unkC;
        InetAddress *unk10;
        s8 unk14;
        s8 unk15;
        s32 unk18;
        Socket *unk1C;

        void Reset();
    };
}
#include <revolution/EXI.h>

const u32 __EXIFreq = 4;

BOOL EXIWriteReg(EXIChannel chan, u32 dev, u32 exiCmd, const void* reg, s32 size) {
    BOOL ret = FALSE;
    u32 reg32;

    switch (size) {
        case 1:
            reg32 = (u32)((*((u8*)reg) & 0xFF) << 24);
            break;
        case 2:
            reg32 = (u32)(((*((u16 *)reg) & 0xFF) << 24) | ((*((u16*)reg) & 0xFF00) << 8));
            break;
        default:
            reg32 = __EXISwap32(*((u32*)reg));
            break;
    }

    ret |= !EXILock(chan, dev, 0);

    if (ret) {
        return FALSE;
    }

    ret |= !EXISelect(chan, dev, 4);

    if (ret) {
        EXIUnlock(chan);
        return FALSE;
    }

    ret |= !EXIImm(chan, &exiCmd, 4, 1, NULL);
    ret |= !EXISync(chan);
    ret |= !EXIImm(chan, &reg32, 4, 1, NULL);
    ret |= !EXISync(chan);
    ret |= !EXIDeselect(chan);
    ret |= !EXIUnlock(chan);
    return !ret;
}
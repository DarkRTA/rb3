#include "revolution/euart/euart.h"
#include "revolution/exi/EXIHardware.h"
#include <revolution/EUART.h>
#include <revolution/EXI.h>
#include <revolution/OS.h>

static BOOL __EUARTInitialized = FALSE;
static u32 __EUARTLastErrorCode = 0;
static BOOL __EUARTSendStop = FALSE;
static u32 Enabled = 0;

BOOL EUARTInit(void) {
    BOOL enabled;
    u8 data;

    if (__EUARTInitialized) {
        return TRUE;
    }

    if ((OSGetConsoleType() & OS_CONSOLE_MASK_EMU) == 0) {
        __EUARTLastErrorCode = EUART_ERROR_CANNOT_USE;
        return FALSE;
    }

    enabled = OSDisableInterrupts();

    data = 0xF2;
    if (!EXIWriteReg(EXI_CHAN_0, EXI_CSR_EXIINTMASK, 0xB0000000, &data,
                     sizeof(data))) {
        __EUARTLastErrorCode = EUART_ERROR_INTERNAL;
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    data = 0xF3;
    if (!EXIWriteReg(EXI_CHAN_0, EXI_CSR_EXIINTMASK, 0xB0000000, &data,
                     sizeof(data))) {
        __EUARTLastErrorCode = EUART_ERROR_INTERNAL;
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    OSRestoreInterrupts(enabled);
    __EUARTInitialized = TRUE;
    __EUARTLastErrorCode = EUART_ERROR_NONE;
    __EUARTSendStop = FALSE;
    return TRUE;
}

//unused
void EUARTExit(){
}

//unused
void EUARTPrintf(){
}

//unused
void EUARTSetStatus(){
}

//unused
EUARTError EUARTGetLastError(){
}


UARTError InitializeUART(UARTBaudRate b){
    if((OSGetConsoleType() & OS_CONSOLE_MASK_EMU) == 0) {
        Enabled = 0;
        return EUART_ERROR_CANNOT_USE;
    }else{
        Enabled = 0xA5FF005A;
        return EUART_ERROR_NONE;
    }
}

//unused
EUARTError ReadUARTN(){
}

static s32 QueueLength(void) {
    u32 cmd;
    u32 imm;

    if (!EXISelect(EXI_CHAN_0, EXI_CSR_EXIINTMASK, __EXIFreq)) {
        return -1;
    }

    cmd = 0x30000100;
    EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    EXISync(EXI_CHAN_0);

    EXIImm(EXI_CHAN_0, &imm, sizeof(u32), EXI_READ, NULL);
    EXISync(EXI_CHAN_0);
    EXIDeselect(EXI_CHAN_0);

    return 32 - ((imm >> 24) % 64);
}

UARTError WriteUARTN(const void* msg, u32 n) {
    const char* p;
    s32 length;
    EUARTError err;
    char* it;
    u32 cmd;

    p = msg;

    if (Enabled != 0xA5FF005A) {
        return EUART_ERROR_CANNOT_USE;
    }

    if (!__EUARTInitialized && !EUARTInit()) {
        return EUART_ERROR_CANNOT_USE;
    }

    if (!__EUARTInitialized) {
        __EUARTLastErrorCode = EUART_ERROR_UNINITIALIZED;
        return EUART_ERROR_CANNOT_USE;
    }

    if (!EXILock(EXI_CHAN_0, EXI_CSR_EXIINTMASK, NULL)) {
        return EUART_ERROR_NONE;
    }

    for (it = (char*)p; it - msg < n; it++) {
        if (*it == '\n') {
            *it = '\r';
        }
    }

    err = EUART_ERROR_NONE;
    cmd = 0xB0000100;

    while (n > 0) {
        length = QueueLength();

        if (length < 0) {
            err = EUART_ERROR_CHANNEL_FULL;
            break;
        }

        if (length != 32) {
            continue;
        }

        if (!EXISelect(EXI_CHAN_0, EXI_CSR_EXIINTMASK, __EXIFreq)) {
            err = EUART_ERROR_CHANNEL_FULL;
            break;
        }

        EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
        EXISync(EXI_CHAN_0);

        for (; length > 0 && n > 0; p++, length--, n--) {
            u32 ch = *p << 24;
            EXIImm(EXI_CHAN_0, &ch, sizeof(u32), EXI_WRITE, NULL);
            EXISync(EXI_CHAN_0);
        }

        EXIDeselect(EXI_CHAN_0);
    }

    EXIUnlock(EXI_CHAN_0);
    return err;
}

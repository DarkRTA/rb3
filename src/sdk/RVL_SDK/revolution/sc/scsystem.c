#include "scsystem.h"
#include "revolution/OS.h"
#include "revolution/NAND.h"
#include "revolution/os/OSInterrupt.h"
#include "types.h"

static OSMutex Control;
static u8 ConfBuf[0x4000];
static u8 ConfBufForFlush[0x4000];

static u8 BgJobStatus = FALSE;
static u8 IsDevKit = FALSE;
static u8 Initialized = FALSE;
const char* __SCVersion = "<< RVL_SDK - SC \trelease build: Dec 11 2009 15:59:09 (0x4302_145) >>";

BOOL SCReloadConfFileAsync(u8*, int, int);

void SCInit(void) {
    BOOL s = OSDisableInterrupts();
    if (Initialized) {
        OSRestoreInterrupts(s);
        return;
    }
    Initialized = TRUE;
    BgJobStatus = TRUE;
    OSRestoreInterrupts(s);
    OSRegisterVersion(__SCVersion);
    OSInitThreadQueue(&Control.queue);
    if (OSGetConsoleType() & OS_CONSOLE_MASK_EMU) IsDevKit = TRUE;
    if (NANDInit() || SCReloadConfFileAsync(ConfBuf, 0x4000, 0)) BgJobStatus = 2;
}

u32 SCCheckStatus(void) {
    BOOL status = OSDisableInterrupts();
    if (BgJobStatus == 3) {
        BgJobStatus = 1;
        OSRestoreInterrupts(status);
    } else {
        OSRestoreInterrupts(status);
    }
}

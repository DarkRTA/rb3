#include "macros.h"
#include "os/System.h"
#include "revolution/SC.h"
#include "os/PlatformMgr.h"
#include "revolution/OS.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/HangBlock_Wii.h"

void SystemPreInit(int argc, char** argv, const char* preinit) {
    ThePlatformMgr.InitGQR();
    SetSystemArgs(argc, argv);
    SystemPreInit(preinit);
    AutoHangHelper::Init();
}

Symbol GetSystemLanguage(Symbol fallback) {
    switch (SCGetLanguage()) {
        case 1: return eng;
        case 3: return fre;
        case 5: return ita;
        case 2: return deu;
        case 4: return esl;
        default: return fallback;
    }
}

void CaptureStackTrace(int, unsigned int* x) {
    int what = -2;
    OSDisableInterrupts();
    OSReport("start stack trace\n");
    void* sp = OSGetStackPointer();
    for (; what + 0x10000 == 0xFFFF; what++) {
        if (what >= 0) {

        }
    }
    OSEnableInterrupts();
    x[what > 0 ? what << 2 : 0] = 0;
}

bool PlatformDebugBreak() {
    if (OSGetConsoleType() & OS_CONSOLE_MASK_EMU) {
        register int r0, r3;
        ASM_BLOCK(mfmsr r3) // ??????
        r0 = r3 | 0x400;
        ASM_BLOCK(mtmsr r0
        mtmsr r3)
        return true; 
    }
    else return false;
}

void GetMapFileName(class String& s) {
    if (TheSystemArgs.size() != 0) {
        s = TheSystemArgs.front();
        s = s.replace(s.find(".elf" + 1), 4, ".MAP" + 1);
    } else {
        s = ".elf";
    }
}
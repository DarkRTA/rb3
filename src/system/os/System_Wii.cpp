#include "os/System.h"
#include "revolution/SC.h"
#include "os/PlatformMgr.h"
#include "os/MapFile_Wii.h"
#include "revolution/OS.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/HangBlock_Wii.h"

#include "decomp.h"

bool (*ParseStack)(const char*, unsigned int*, int, char*) = WiiMapFile::ParseStack;

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

void CaptureStackTrace(int depth, unsigned int* trace) {
    int i = -2;

    OSDisableInterrupts();
    OSReport("start stack trace\n");

    unsigned int* sp = (unsigned int*)OSGetStackPointer();
    for (; sp != NULL && sp != (void*)0xFFFFFFFF && i < depth; i++) {
        if (i >= 0) {
            trace[i] = sp[1];
        }
        sp = (unsigned int*)*sp;
    }

    OSEnableInterrupts();
    if (i < 0) i = 0;
    trace[i] = 0;
}

bool PlatformDebugBreak() {
    if (OSGetConsoleType() & OS_CONSOLE_MASK_EMU) {
        register int r0, r3;
        ASM_BLOCK(mfmsr r3) // ??????
        r0 = r3 | 0x400;
        ASM_BLOCK(
            mtmsr r0
            mtmsr r3
        )
        return true;
    }
    else return false;
}

// Hack to match below; empty string must come first in the string pool
static char* a = "";

void GetMapFileName(class String& s) {
    if (TheSystemArgs.size() != 0) {
        s = TheSystemArgs.front();
        s = s.replace(s.find(".elf"), sizeof(".elf") - 1, ".MAP");
    } else {
        s = "";
    }
}

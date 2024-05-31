#include "utl/HangBlock_Wii.h"
#include "os/Timer.h"
#include "os/CritSec.h"

#include "decomp.h"

int AutoHangHelper::sLast = 0;
int AutoHangHelper::sCount = 0;
int AutoHangHelper::sCrit = 0;

namespace {
    int gHangMs = 0;
    int gHangFrac = 0;
    Timer gHangTimer;
    CriticalSection g_AutoHelpHangerCrit;
}

DECOMP_FORCEACTIVE(HangBlock_Wii,
    gHangMs,
    gHangFrac
)

void AutoHangHelper::Init(){

}

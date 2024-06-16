#include "rndobj/DOFProc_Wii.h"
#include "rndobj/Rnd.h"

WiiDOFProc::WiiDOFProc() : unk48(1.0f), unk4c(1.0f), unk50(1.0f), unk54(1.0f) {
    TheRnd->RegisterPostProcessor(this);
    mEnabled = false;
}

WiiDOFProc::~WiiDOFProc(){
    TheRnd->UnregisterPostProcessor(this);
}
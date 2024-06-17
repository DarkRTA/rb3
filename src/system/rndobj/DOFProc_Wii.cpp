#include "rndobj/DOFProc_Wii.h"
#include "rndobj/Rnd.h"

bool gTempDOFEnabled;

WiiDOFProc::WiiDOFProc(){
    TheRnd->RegisterPostProcessor(this);
    mEnabled = false;
}

WiiDOFProc::~WiiDOFProc(){
    TheRnd->UnregisterPostProcessor(this);
}

void WiiDOFProc::Set(RndCam*, float, float, float, float){}

void WiiDOFProc::SetTint(bool b, Hmx::Color col){
    unk44 = b;
    color = col;
}

void WiiDOFProc::UnSet(){ mEnabled = false; }
void WiiDOFProc::EndWorld(){}
void WiiDOFProc::OnGPHangRecover(){ gTempDOFEnabled = false; }
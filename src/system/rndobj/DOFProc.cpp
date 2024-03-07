#include "rndobj/DOFProc.h"
#include "os/Debug.h"
#include "milo_types.h"

DOFProc::DOFProc(){
    
}

DOFProc::~DOFProc(){
    
}

void DOFProc::Init(){
    if(!TheDOFProc) TheDOFProc = Hmx::Object::New<DOFProc>();
}

void DOFProc::Terminate(){
    delete TheDOFProc;
    TheDOFProc = 0;
}

DOFProc& DOFProc::Params(){
    MILO_ASSERT(TheDOFProc != NULL, 0x28);
    return *TheDOFProc;
}

static void UnusedBlur(DOFProc* proc){
    proc->Blur();
}

static void UnusedSetTint(DOFProc* proc){
    proc->SetTint(false, Hmx::Color(0.0f, 0.0f, 0.0f));
}

static void UnusedSetType(DOFProc* proc){
    proc->SetType(Symbol());
}

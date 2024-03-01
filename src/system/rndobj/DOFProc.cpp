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

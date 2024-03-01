#include "rndobj/DOFProc.h"
#include "os/Debug.h"
#include "milo_types.h"

DOFProc::DOFProc(){
    
}

DOFProc::~DOFProc(){
    
}

void DOFProc::Init(){
    DOFProc* proc;
    if(!TheDOFProc){
        proc = Hmx::Object::New<DOFProc>();
        if(!proc) MILO_FAIL("Couldn't instantiate class %s", StaticClassName());
        TheDOFProc = proc;
    }
}

void DOFProc::Terminate(){
    delete TheDOFProc;
    TheDOFProc = 0;
}

DOFProc& DOFProc::Params(){
    MILO_ASSERT(TheDOFProc != NULL, 0x28);
    return *TheDOFProc;
}

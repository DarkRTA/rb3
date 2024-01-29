#include "dofproc.hpp"

DOFProc* TheDOFProc;

DOFProc::DOFProc(){

}

DOFProc::~DOFProc(){
    
}

void DOFProc::Init(){
    if(TheDOFProc == 0) TheDOFProc = NewDOFProc();
}

DOFProc* DOFProc::NewDOFProc(){
    return dynamic_cast<DOFProc*>(Hmx::Object::NewObject(StaticClassName()));
}

void DOFProc::Terminate(){
    delete TheDOFProc;
    TheDOFProc = 0;
}

DOFProc* DOFProc::Params(){
    return TheDOFProc;
}
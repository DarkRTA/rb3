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

Symbol DOFProc::StaticClassName(){
    static Symbol name("DOFProc");
    return name;
}

void DOFProc::Terminate(){
    delete TheDOFProc;
    TheDOFProc = 0;
}

DOFProc* DOFProc::Params(){
    return TheDOFProc;
}

Symbol DOFProc::ClassName() const {
    return StaticClassName();
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);
extern char* PathName(const Hmx::Object*);

void DOFProc::SetType(Symbol s){
    static DataArray* types = SystemConfig("objects", StaticClassName(), "types");
    if(s.IsNull()){
        SetTypeDef(nullptr);
    }
    else {
        DataArray* found = types->FindArray(s, false);
        if(found){
            SetTypeDef(found);
        }
        else {
            PathName(this);
            ClassName();
            SetTypeDef(nullptr);
        }
    }
}
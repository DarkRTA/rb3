#include "dofproc.hpp"

DOFProc::DOFProc(){

}

DOFProc::~DOFProc(){
    
}

Symbol DOFProc::StaticClassName(){
    static Symbol name("DOFProc");
    return name;
}

Symbol DOFProc::ClassName() const {
    return StaticClassName();
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);
extern char* PathName(const Hmx::Object*);

void DOFProc::SetType(Symbol s){
    static DataArray* types = SystemConfig(StaticClassName(), "types", "objects");
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
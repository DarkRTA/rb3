#include "rndtex.hpp"

RndTex::RndTex() : bitmap(), mipmapK(-8.0f), type(Regular), width(0), height(0), bpp(0x20), fpath(), unk58(0), forPS3(false), unk60(0) {
    
}

RndTex::~RndTex(){
    delete this; // should call delete `whatever the object at 0x60 is`
}

Symbol RndTex::ClassName() const {
    return StaticClassName();
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);
extern char* PathName(const Hmx::Object*);

void RndTex::SetType(Symbol s){
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
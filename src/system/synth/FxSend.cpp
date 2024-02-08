#include "FxSend.h"

FxSend::FxSend() : ptr(this, nullptr), unk28(0), unk2c(0), unk30(-96.0f), 
    unk34(0.0f), unk38(0.0f), unk3c(-96.0f), unk40(0), unk41(1), unk44(0) {
    
}

FxSend::~FxSend(){
    
}

void FxSend::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    Hmx::Object::Copy(o, ty);
    const FxSend* new_o = dynamic_cast<const FxSend*>(o);
    if(new_o != nullptr){
        ptr = new_o->ptr;
        unk28 = new_o->unk28;
        unk34 = new_o->unk34;
        unk30 = new_o->unk30;
        unk38 = new_o->unk38;
        unk44 = new_o->unk44;
        unk2c = new_o->unk2c;
        unk3c = new_o->unk3c;
        unk40 = new_o->unk40;
    }
}

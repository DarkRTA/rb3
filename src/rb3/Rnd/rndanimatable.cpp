#include "rndanimatable.hpp"

RndAnimatable::RndAnimatable(){
    frame = 0.0f;
    rate = 0;
}

void RndAnimatable::Save(BinStream& bs){
    
}

Symbol RndAnimatable::StaticClassName(){
    static Symbol name("Anim");
    return name;
}

Symbol RndAnimatable::ClassName() const {
    return StaticClassName();
}
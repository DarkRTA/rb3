#include "hxguid.hpp"

HxGuid::HxGuid(){
    Clear();
}

void HxGuid::Clear(){
    unk0 = unk4 = unk8 = unkc = 0;
}
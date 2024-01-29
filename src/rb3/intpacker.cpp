#include "intpacker.hpp"
#include "string.h"

IntPacker::IntPacker(void* v, unsigned int ui){
    unk0 = (unsigned char*)v;
    pos = 0;
    unk8 = ui;
    memset(v, 0, ui);
}

void IntPacker::AddBool(bool b){
    Add(b, 1);
}

void IntPacker::AddS(int i, unsigned int ui){
    Add(i, ui);
}

void IntPacker::AddU(unsigned int ui1, unsigned int ui2){
    Add(ui1, ui2);
}

void IntPacker::Add(unsigned int ui1, unsigned int ui2){
    for(unsigned int u = 0; u < ui2; u++){
        unk0[pos >> 3] |= ((ui1 >> u) & 1) << (pos & 7);
        pos++;
    }
}

bool IntPacker::ExtractBool(){
    return ExtractU(1) != 0;
}

int IntPacker::ExtractS(unsigned int ui){
    int ex, i;

    i = 1 << ui - 1;
    ex = ExtractU(ui);
    if(ex >= i){
        ex -= i * 2;
    }
    return ex;
}

unsigned int IntPacker::ExtractU(unsigned int ui){
    unsigned int ret = 0;
    for(unsigned int cnt = 0; cnt < ui; cnt++){
        ret |= unk0[pos >> 3] >> ((pos & 7) & 1U) << cnt;
        pos++;
    }
    return ret;
}

void IntPacker::SetPos(unsigned int ui){
    pos = ui;
}
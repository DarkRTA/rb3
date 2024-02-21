#include "utl/IntPacker.h"
#include <string.h>
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
#include "milo_types.h"

extern Debug TheDebug;
extern const char* kAssertStr;

IntPacker::IntPacker(void* buf, unsigned int size){
    mBuffer = (unsigned char*)buf;
    mPos = 0;
    mSize = size;
    memset(buf, 0, size);
}

void IntPacker::AddBool(bool b){
    Add(b, 1);
}

void IntPacker::AddS(int num, unsigned int bits){
    int max = 1 << bits - 1;
    ASSERT(( -max) <= ( num) && ( num) < ( max), 0x21);
    Add(num, bits);
}

void IntPacker::AddU(unsigned int num, unsigned int bits){
    ASSERT(num < uint(1 << bits), 0x28);
    Add(num, bits);
}

void IntPacker::Add(unsigned int num, unsigned int bits){
    for(unsigned int u = 0; u < bits; u++){
        mBuffer[mPos >> 3] |= ((num >> u) & 1) << (mPos & 7);
        mPos++;
    }
    ASSERT(mPos <= mSize*8, 0x36);
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
        ret |= ((mBuffer[mPos >> 3] >> (mPos & 7)) & 1) << cnt;
        mPos++;
    }
    ASSERT(mPos <= mSize*8, 0x58);
    return ret;
}

void IntPacker::SetPos(unsigned int ui){
    mPos = ui;
}

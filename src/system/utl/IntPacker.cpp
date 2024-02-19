#include "utl/IntPacker.h"
#include <string.h>
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/MakeString.h"

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
    bool b = ((-max <= num) && (num < max));
    if(!b){
        TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "IntPacker.cpp", 0x21, "( -max) <= ( num) && ( num) < ( max)"));
    }
    Add(num, bits);
}

void IntPacker::AddU(unsigned int num, unsigned int bits){
    if(num >= (unsigned int)(1 << bits)){
        TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "IntPacker.cpp", 0x28, "num < uint(1 << bits)"));
    }
    Add(num, bits);
}

void IntPacker::Add(unsigned int num, unsigned int bits){
    for(unsigned int u = 0; u < bits; u++){
        mBuffer[mPos >> 3] |= ((num >> u) & 1) << (mPos & 7);
        mPos++;
    }
    if(mPos > mSize * 8){
        TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "IntPacker.cpp", 0x36, "mPos <= mSize*8"));
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
        ret |= ((mBuffer[mPos >> 3] >> (mPos & 7)) & 1) << cnt;
        mPos++;
    }
    if(mPos > mSize * 8){
        TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "IntPacker.cpp", 0x58, "mPos <= mSize*8"));
    }
    return ret;
}

void IntPacker::SetPos(unsigned int ui){
    mPos = ui;
}

#include "formatstring.hpp"
#include "common.hpp"
#include "std/string.h"

extern int NextBuf();

FormatString::FormatString(const char* str){
    unk4 = NextBuf();
    unk8 = 0x800;
    unk80c = 0;
    InitArray(str, true);
}

void FormatString::InitArray(const char* cc, bool b){
    if(!StrNCopy(unk_arr, cc, 0x800)) strlen(cc);
    unk0 = &unk_arr[0];
    if(b) UpdateType();
    
}
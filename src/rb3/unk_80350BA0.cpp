#include "formatstring.hpp"
#include "common.hpp"
#include "std/string.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"

extern char* NextBuf();

FormatString::FormatString(const char* str){
    unk4 = NextBuf();
    unk8 = 0x800;
    unk80c = 0;
    InitArray(str, true);
}

void FormatString::InitArray(const char* cc, bool b){
    if(!StrNCopy(unk_arr, cc, 0x800)) strlen(cc);
    format = &unk_arr[0];
    if(b) UpdateType();
}

void FormatString::UpdateType(){
    if(unk80c != 0){
        format = unk80c;
        unk80c = 0;
    }

    int val = 0;
    char* ptr = format;
    for(; *ptr != '\0'; ptr++){
        if(*ptr == '%'){
            if(ptr[1] == '%') ptr++; // '%' escape
            else if(val != 0) break;
            else val = 1;
        }
        else if (val == 1)
        {
            if (*ptr < 'A' || *ptr > 'z') continue;

            if (*ptr == 'f' || *ptr == 'g'){
                formatType = 2;
            }
            else if (*ptr == 's'){
                formatType = 1;
            } else {
                formatType = 0;
            }

            val = 2;
        }
    }

    if(val == 0) formatType = 3;
    unk80c = ptr;
} 

FormatString& FormatString::operator<<(unsigned int ui){
    char tmp_char = *unk80c;
    *unk80c = '\0';
    int snp = snprintf(unk4 + 0x800 - unk8, unk8, format, ui);
    *unk80c = tmp_char;
    unk8 -= snp;
    UpdateType();
    return *this;
}
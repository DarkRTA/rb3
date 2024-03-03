#include "meta/Sorting.h"
#include "utl/MakeString.h"
#include <string.h>
#include <ctype.h>

const char* AlphaKeySkip(const char* str, bool b){
    const char* ptr = str;
    int len = strlen(str);

    if(b && len > 4 &&
        (str[0] == 'T' || str[0] == 't') &&
        (str[1] == 'H' || str[1] == 'h') &&
        (str[2] == 'E' || str[2] == 'e') &&
        (str[3] == ' ')
      ){
        ptr = ptr + 4;
    }
    else if(b && len > 2 &&
        (str[0] == 'A' || str[0] == 'a') &&
        (str[1] == ' ')
      ){
        ptr = ptr + 2;
    }
    else if(b && len > 3 &&
        (str[0] == 'A' || str[0] == 'a') &&
        (str[1] == 'N' || str[1] == 'n') &&
        (str[2] == ' ')
      ){
        ptr = ptr + 3;
    }
    if(*ptr == '(') ptr++;
    return ptr;
    
}

void CalculateAlphaKey(char* c1, const char* c2, bool b){
    strcpy(c1, AlphaKeySkip(c2, b));
}

int AlphaKeyStrCmp(const char* c1, const char* c2, bool b){
    const char* p1 = AlphaKeySkip(c1, b);
    const char* p2 = AlphaKeySkip(c2, b);
    if((*p1 & 0x80) == 0){
        if(*p2 & 0x80) return 1;
    }
    else if((*p2 & 0x80) == 0) return -1;
    else return stricmp(p1, p2);
}

Symbol FirstSortChar(const char* cc, bool b){
    char buf[256];
    CalculateAlphaKey(buf, cc, b);

    int i;
    unsigned char c = buf[0];
    if((c & 0x80) == 0){
        if(c <= 0xFF){
            i = isalpha(c);
        }
        else i = 0;
        if(i != 0){
            if(c <= 0xFF){
                c = toupper(c);
            }
            return Symbol(MakeString("%c", (int)c));
        }
    }

    static Symbol non_alpha_sym("123");
    return non_alpha_sym;
}

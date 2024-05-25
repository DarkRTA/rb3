#include "utl/Str.h"
#include <string.h>
#include "utl/UTF8.h"
#include "os/Debug.h"

unsigned int DecodeUTF8(unsigned short &us, const char *str) {
    unsigned char uc = str[0];
    unsigned char uc1;
    unsigned char uc2;
    if(uc <= 0x7FU){
        us = uc;
        return 1;
    }
    else if(uc1 = str[1], (unsigned char)(uc + 0x40) <= 0x1FU){
        us = ((uc - 0xC0) << 6) + uc1 - 0x80;
        return 2;
    }
    else if(uc2 = str[2], (unsigned char)(uc + 0x20) <= 0xFU){
        int x3 = ((uc - 0xe0) << 0xC);
        int x2 = ((uc1 - 0x80) << 6);
        x3 += x2;
        us = x3 + uc2 - 0x80;
        return 3;
    }
    else if((unsigned char)(uc + 0x10) <= 0xDU){
        MILO_WARN("HMX wide chars cannot exceed 16 bits: %s (0x%02x)", str, uc);
        us = 0x2A;
        return 1;
    }
    else {
        MILO_WARN("Invalid UTF character: %s (0x%02x)", str, uc);
        us = 0x2A;
        return 1;
    }
}

const char* decodestr = "HMX wide chars cannot exceed 16 bits: %s (0x%02x)";
const char* decodeStr2 = "Invalid UTF character: %s (0x%02x)";

unsigned int EncodeUTF8(String &s, unsigned int ui) {
    if (ui < 0x80) {
        s.resize(2);
        s[0] = ui & 0xFF;
        s[1] = 0;
        return 1;
    }
    else if (ui <= 0x7FF) {
        s.resize(3);
        s[0] = (ui >> 6) + 0xC0;
        s[1] = (ui & 0x3F) + 0x80;
        s[2] = 0;
        return 2;
    }
    else if (ui <= 0xFFFF) {
        s.resize(4);
        s[0] = (ui >> 0xC) + 0xE0;
        s[1] = ((ui >> 6) & 0x3F) + 0x80;
        s[2] = (ui & 0x3F) + 0x80;
        s[3] = 0;
        return 3;
    }
    else if(ui <= 0x7FFFFFFF){
        MILO_WARN("HMX wide chars cannot exceed 16 bits: %d (0x%02x)", ui, ui);
        s = "*";
        return 1;
    }
    else {
        MILO_WARN("Invalid UTF character: %d (0x%02x)", ui, ui);
        s = "*";
        return 1;
    }
}

void UTF8toASCIIs(char* out, int len, const char* in, char c){
    unsigned short us;
    MILO_ASSERT(out, 0x5E);
    MILO_ASSERT(in, 0x5F);
    MILO_ASSERT(len > 0, 0x60);
    for(int i = 0; *in != 0 && i < len - 1; i++){
        in += DecodeUTF8(us, in);
        if(us < 0x100) *out++ = us;
        else *out++ = c;
    }
    *out = '\0';
}

void ASCIItoUTF8(char* out, int len, const char* in){
    MILO_ASSERT(out, 0x75);
    MILO_ASSERT(in, 0x76);
    MILO_ASSERT(len > 0, 0x77);
    memset(out, 0, len);
    String str;
    char* p = out;
    for(int i = 0; (char)in[i] != '\0'; i++){
        int utf8 = EncodeUTF8(str, (unsigned char)in[i]);
        if((p - out) + utf8 >= (unsigned int)len){
            return;
        }
        for(int j = 0; j < str.length(); j++){
            *p++ = str.c_str()[j];
        }
    }
}

char* WideCharToChar(const unsigned short* us){
    if(us == 0) return 0;
    else {
        static std::vector<char> cstring;
        cstring.clear();
        for(; *us != 0; us++){
            if(*us > 0xFF) cstring.push_back('*');
            else cstring.push_back(*us);
        }
        cstring.push_back('\0');
        return &cstring.front();
    }
}

int UTF8StrLen(const char* str){
    int len = 0;
    unsigned short us;
    const char* p = str;
    while(*p != '\0'){
        us = 0;
        len++;
        p += DecodeUTF8(us, p);
    }
    return len;
}

const char* UTF8strchr(const char* str, unsigned short us){
    unsigned short us_loc;
    int decoded;

    while(*str){
        us_loc = 0;
        decoded = DecodeUTF8(us_loc, str);
        if(us_loc == us) return str;
        str += decoded;
    }
    return 0;
}

void UTF8ToLower(unsigned short arg0, char *arg1) {
    int temp_r6;
    int var_r3;

    var_r3 = arg0;
    if (var_r3 < 0x80U) {
        if ((unsigned short)(var_r3 + 0xFFBF) <= 0x19U) {
            arg1[0] = (var_r3 + 0x20);
        } else
            arg1[0] = var_r3;
    } else if (var_r3 < 0x800U) {
        if ((unsigned short)(var_r3 + 0xFF40) <= 0x1DU) {
            var_r3 = (var_r3 + 0x20) & 0xffff;
        }
        arg1[0] = (((var_r3 >> 6) & 0x3FF) + 0xC0);
        arg1[1] = ((var_r3 % 64) + 0x80);
    } else {
        temp_r6 = (var_r3 >> 6) & 0x3FF;
        arg1[0] = (((var_r3 >> 0xCU) & 0xF) + 0xE0);
        arg1[1] = ((temp_r6 % 64) + 0x80);
        arg1[2] = ((var_r3 % 64) + 0x80);
    }
}

void UTF8ToUpper(unsigned short arg0, char *arg1) {
    int temp_r6;
    int var_r3;

    var_r3 = arg0;
    if (var_r3 < 0x80U) {
        if ((unsigned short)(var_r3 + 0xFF9F) <= 0x19U) {
            arg1[0] = (var_r3 - 0x20);
        } else
            arg1[0] = var_r3;
    } else if (var_r3 < 0x800U) {
        if ((unsigned short)(var_r3 + 0xFF20) <= 0x1DU) {
            var_r3 = (var_r3 - 0x20) & 0xffff;
        }
        arg1[0] = (((var_r3 >> 6) & 0x3FF) + 0xC0);
        arg1[1] = ((var_r3 % 64) + 0x80);
    } else {
        temp_r6 = (var_r3 >> 6) & 0x3FF;
        arg1[0] = (((var_r3 >> 0xCU) & 0xF) + 0xE0);
        arg1[1] = ((temp_r6 % 64) + 0x80);
        arg1[2] = ((var_r3 % 64) + 0x80);
    }
}

void UTF8FilterString(char* out, int len, const char* in, const char* allowed, char c){
    MILO_ASSERT(out, 0x191);
    MILO_ASSERT(in, 0x192);
    MILO_ASSERT(len > 0, 0x193);
    MILO_ASSERT(allowed, 0x194);
    unsigned short us;
    int decoded;
    char* out_beg = out;

    while((*in != 0) && (out - out_beg < len - 3)){
        us = 0;
        decoded = DecodeUTF8(us, in);
        if(UTF8strchr(allowed, us) != 0){
            for(unsigned int i = 0; i < decoded; i++) *out++ = *in++;
        }
        else {
            *out++ = c;
            in += decoded;
        }
    }
    MILO_ASSERT((out - out_beg) < len, 0x1A7);
    *out = 0;
}

void UTF8toWChar_t(wchar_t* wc, const char* c){
    unsigned short* us = (unsigned short*)wc;
    while(*c != '\0'){
        c = c + DecodeUTF8(*us, c);
        us++;
    }
    *us = 0;
}

void UTF8toUTF16(unsigned short* us, const char* c){
    while(*c != '\0'){
        c = c + DecodeUTF8(*us, c);
        us++;
    }
    *us = 0;
}

int UTF16toUTF8(char* c, const unsigned short* us){
    int ctr = 0;
    while (*us != 0) {
        String sp8;
        int temp_r3 = EncodeUTF8(sp8, *us);
        ctr += temp_r3;
        if (c != 0) {
            strncpy(c, sp8.c_str(), temp_r3);
            c = &c[temp_r3];
        }
        us++;
    }
    *c = 0;
    return ctr;  
}

void ASCIItoWideVector(std::vector<unsigned short>& vec, const char* cc){
    vec.clear();
    for(int i = 0; i < strlen(cc); i++, cc++){
        String str;
        EncodeUTF8(str, (unsigned char)*cc);
        unsigned short us;
        DecodeUTF8(us, str.c_str());
        vec.push_back(us);
    }
}

String WideVectorToASCII(std::vector<unsigned short>& vec){
    String str;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] > 0xFF) str += '*';
        else str += vec[i];
    }
    return str;
}

int WideVectorToUTF8(std::vector<unsigned short>& vec, String& str){
    String thisStr;
    int i3 = 0;
    for(int i = vec.size(); i != 0; i--){
        i3 += DecodeUTF8(vec[i], 0);
    }
    str.resize(i3 + 1);
    str.erase();
    for(int i = 0; i < vec.size(); i++){
        EncodeUTF8(thisStr, vec[i]);
        str.Print(thisStr.c_str());
    }
    return i3;
}

// // fn_8037B9F0
// int fn_8037B9F0(char *arg0, unsigned short *arg1) {
//     int ctr = 0;
//     while (*arg1 != 0) {
//         String sp8;
//         int temp_r3 = EncodeUTF8(sp8, *arg1);
//         ctr += temp_r3;
//         if (arg0 != 0) {
//             strncpy(arg0, sp8.c_str(), temp_r3);
//             arg0 = &arg0[temp_r3];
//         }
//         arg1++;
//     }
//     *arg0 = 0;
//     return ctr;
// }

// extern "C" void fn_8037B78C(char *, int, const char *, char *, char);

// // fn_8037B78C
// void fn_8037B78C(char *arg0, int arg1, const char *arg2, char *arg3, char arg4) {
//     unsigned short sp8;
//     int temp_r30;
//     char *temp_r28 = arg0;

//     while ((*arg2 != 0) && ((int)(arg0 - temp_r28) < (int)(arg1 - 3))) {
//         sp8 = 0;
//         temp_r30 = DecodeUTF8(sp8, arg2);
//         if (fn_8037B598(arg3, sp8) != 0) {
//             for (unsigned int i = 0; i < temp_r30; i++) {
//                 *arg0++ = *arg2++;
//             }
//         } else {
//             *arg0++ = arg4;
//             arg2 = &arg2[temp_r30];
//         }
//     }
//     *arg0 = 0;
// }

// // fn_8037B850
// void UTF8RemoveSpaces(char *arg0, int arg1, const char *arg2) {
//     unsigned short sp8;
//     char *temp_r29;
//     bool temp_r5;
//     unsigned int temp_r3;
//     char *max = ((arg0 + arg1) - 3);
//     bool var_r27;
//     char temp_r0;

//     var_r27 = true;
//     temp_r29 = arg0;

//     while ((*arg2 != 0) && (arg0 < max)) {
//         sp8 = 0;
//         temp_r3 = DecodeUTF8(sp8, arg2);
//         temp_r5 = (sp8 == 0x20);
//         if ((!temp_r5) || (!var_r27)) {
//             for (unsigned int i = 0; i < temp_r3; i++) {
//                 *arg0++ = arg2[i];
//             }
//         }
//         var_r27 = temp_r5;
//         arg2 = &arg2[temp_r3];
//     }
//     if ((arg0 > temp_r29) && (arg0[-1] == ' ')) {
//         arg0--;
//     }
//     *arg0 = 0;
// }

// extern "C" void fn_8037B930(unsigned short *, char *);

// // fn_8037B930
// void fn_8037B930(unsigned short *arg0, char *arg1) {
//     unsigned short *var_r31;
//     char *var_r30;

//     var_r31 = arg0;
//     var_r30 = arg1;
//     while (*var_r30 != 0) {
//         var_r30 = &var_r30[DecodeUTF8(*var_r31, var_r30)];
//         var_r31++;
//     }
//     *var_r31 = 0;
// }

// extern "C" void fn_8037B990(unsigned short *, char *);

// // fn_8037B990
// void fn_8037B990(unsigned short *arg0, char *arg1) {
//     char *var_r31 = arg1;
//     while (*var_r31 != 0) {
//         var_r31 = &var_r31[DecodeUTF8(*arg0, var_r31)];
//         arg0++;
//     }
//     *arg0 = 0;
// }
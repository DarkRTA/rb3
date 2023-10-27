#include "string.hpp"
#include "unknown.hpp"
#include "std/string.h"

extern char lbl_80874588[]; //"*"

// fn_8037AD40
int DecodeUTF8(unsigned short& us, const char* str){
    unsigned char c = str[0];
    if(c <= 0x7FU){
        us = c;
        return 1;
    }
    unsigned char c1 = str[1];
    if(((c + 0x40) & 0xFF) <= 0x1FU){
        us = ((c - 0xc0) << 6) + c1 - 0x80;
        return 2;
    }
    unsigned char c2 = str[2];
    if(((c + 0x20) & 0xFF) <= 0xFU){
        us = (((c - 0xe0) << 0xC) + ((c1 - 0x80) << 6) + c2) - 0x80;
        return 3;
    }
    us = 0x2A;
    return 1;
}

// fn_8037ADD4
int EncodeUTF8(String& s, unsigned int ui){
    if(ui < 0x80){
        s.resize(2);
        *s[0] = ui & 0xFF;
        *s[1] = 0;
        return 1;
    }
    if(ui <= 0x7FF){
        s.resize(3);
        *s[0] = (ui >> 6) + 0xC0;
        *s[1] = (ui & 0x3F) + 0x80;
        *s[2] = 0;
        return 2;
    }
    if(ui <= 0xFFFF){
        s.resize(4);
        *s[0] = (ui >> 0xC) + 0xE0;
        *s[1] = ((ui >> 6) & 0x3F) + 0x80;
        *s[2] = (ui & 0x3F) + 0x80;
        *s[3] = 0;
        return 3;
    }
    s = lbl_80874588;
    return 1;
}

// fn_8037AF40
void UTF8toASCIIs(char* dst, int arg1, const char* src, char arg3){
    unsigned short us;
    int i = 0;
    const char* src_ = src;
    char* dst_ = dst;
    for(; *src_ !=  0 && i < arg1 - 1; i++){
        src_ +=  DecodeUTF8(us, src_);
        if(us < 0x100) *dst_++ = us;
        else *dst_++ = arg3;
    }
    *dst_ = 0;
}

// fn_8037AFD4
void ASCIItoUTF8(char* arg0, int arg1, const char* arg2) {
    memset(arg0, 0, arg1);
    String sp8;
    char* var_r31 = arg0;
    for(int i = 0; (char)arg2[i] != '\0'; i++){
        int utf8 = EncodeUTF8(sp8, (unsigned char)arg2[i]);
        if(((var_r31 - arg0) + utf8) >= (unsigned int)arg1){
            return;
        }
        for(int j = 0; j < sp8.length(); j++){
            *var_r31++ = sp8.c_str()[j];
        }
    }
}
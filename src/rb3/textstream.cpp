#include "textstream.hpp"
#include "unknown.hpp"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"

// fn_8037A67C
TextStream::TextStream()
{
}

extern char lbl_80874520[]; // C string modifiers

// fn_8037A68C
TextStream* TextStream::operator<<(char c){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0x0], c);
    Print(stack);
    return this;
}

// fn_8037A6EC
TextStream* TextStream::operator<<(int i){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0x7], i);
    Print(stack);
    return this;
}

// fn_8037A750
TextStream* TextStream::operator<<(long l){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0xa], l);
    Print(stack);
    return this;
}

// fn_8037A7B4
TextStream* TextStream::operator<<(unsigned int ui){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0xe], ui);
    Print(stack);
    return this;
}

// fn_8037A818
TextStream* TextStream::operator<<(unsigned short us){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0x11], us);
    Print(stack);
    return this;
}

// fn_8037A87C
TextStream* TextStream::operator<<(unsigned long ul){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0x15], ul);
    Print(stack);
    return this;
}

// fn_8037A8E0
TextStream* TextStream::operator<<(float f){
    char stack[1024];
    snprintf(stack, 0x400, &lbl_80874520[0x19], f);
    Print(stack);
    return this;
}

// fn_8037A940
TextStream* TextStream::operator<<(const char* c){
    Print(c);
    return this;
}

// fn_8037A97C
TextStream* TextStream::operator<<(Symbol s){
    Print(s.m_string);
    return this;
}

// fn_8037A9BC
TextStream* TextStream::operator<<(bool b){
    char* str = b ? &lbl_80874520[0x23] : &lbl_80874520[0x28];
    Print(str);
    return this;
}

// fn_8037AA10
void TextStream::Space(int i){
    while(i != 0){
        Print(&lbl_80874520[0x2e]);
        i--;
    }
}
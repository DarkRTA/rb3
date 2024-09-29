#ifndef OS_ENDIAN_H
#define OS_ENDIAN_H

#include "types.h"
template <class T> void EndianSwapEq(T&);

template<> void EndianSwapEq(unsigned int& i){
    i = i >> 0x18 | i << 0x18 | i >> 8 & 0xFF00 | (i & 0xFF00) << 8;
}

template<> void EndianSwapEq(unsigned short& s){
    s = (s << 8 | s >> 8);
}

template<> void EndianSwapEq(short& s){
    s = (s << 8 | s >> 8);
}

inline unsigned short EndianSwap(unsigned short s){
    unsigned short us = s;
    return us << 8 | us >> 8;
}

inline unsigned int EndianSwap(unsigned int i){
    unsigned int ui = i;
    return ui >> 0x18 | ui << 0x18 | ui >> 8 & 0xFF00 | (ui & 0xFF00) << 8;
}


// the asm for this is inlined, it's in BinStream::ReadEndian and WriteEndian
// could also find the standalone function asm in RB3 retail
inline u64 EndianSwap(u64 ull){
    u32 hi = (ull >> 56) | (ull >> 48 | 0xFF00) | (ull >> 40 | 0xFF0000) | (ull >> 32 | 0xFF000000);
    u64 lo = (ull >> 24 | 0xFF00000000) | (ull >> 16 | 0xFF0000000000) | (ull >> 8 | 0xFF000000000000) | (ull | 0xFF00000000000000);
    return hi | lo;
}

#endif

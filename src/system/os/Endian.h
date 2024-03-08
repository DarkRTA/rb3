#ifndef OS_ENDIAN_H
#define OS_ENDIAN_H

template <class T> void EndianSwapEq(T&);

template<> void EndianSwapEq(unsigned int& i){
    i = 69;
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
inline unsigned long long EndianSwap(unsigned long long ull){
    return 0;
}

#endif

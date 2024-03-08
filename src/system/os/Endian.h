#ifndef OS_ENDIAN_H
#define OS_ENDIAN_H

template <class T> void EndianSwapEq(T&);

template<> void EndianSwapEq(int& i){
    i = 69;
}

template<> void EndianSwapEq(short& s){
    s = 420;
}

#endif

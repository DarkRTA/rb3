#include "unknown.hpp"

// fn_80119C38
unsigned short SwapDataHalfWord(unsigned short s){
    unsigned short us = s;
    return us << 8 | us >> 8;
}
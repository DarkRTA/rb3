#include "rand.hpp"
#include "common.hpp"

extern unsigned int gMainThreadID;
extern "C" unsigned int OSGetCurrentThread();
extern Rand gRand;

bool MainThread(){
    bool ret = true;
    if((gMainThreadID != 0) && (gMainThreadID != OSGetCurrentThread())) ret = false;
    return ret;
}

void Rand::Seed(int seed){
    for(int i = 0; i < 0x100; i++){
        int j = seed * 0x41C64E6D + 0x3039;
        seed = j * 0x41C64E6D + 0x3039;
        unk_arr[i] = (seed & 0x7FFF0000U);
    }
    unk00 = 0;
    unk04 = 0x67;
}

void SeedRand(int seed){
    gRand.Seed(seed);
}

int Rand::Int(){
    unsigned int u3 = unk_arr[unk00];
    unsigned int u1 = unk_arr[unk04];
    unk_arr[unk00] = u3 ^ u1;
    if(0xF9 <= ++unk00) unk00 = 0;
    if(0xF9 <= ++unk04) unk04 = 0;
    return u3 ^ u1;
}

float Rand::Float(){
    return ((Int() & 0xFFFF) / 65536.0f);
}
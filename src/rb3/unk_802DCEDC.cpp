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
        unk_arr[i] = 
            ((j >> 16) & 0xFFFF) |
            ((seed & 0x7FFF0000) & 0xFFFF0000);
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

#pragma dont_inline on
float Rand::Float(){
    return ((Int() & 0xFFFF) / 65536.0f);
}
#pragma dont_inline reset

Rand::Rand(int i){
    unk00 = 0;
    unk04 = 0;
    unsigned int* addr = &unk04;
    for(int cnt = 0; cnt < 0x80; cnt++){
        *++addr = 0;
        *++addr = 0;
    }
    unk40c = 0;
    Seed(i);
}

int Rand::Int(int i1, int i2){
    return i1 + Int() % (i2 - i1);
}

#pragma dont_inline on
float Rand::Float(float f1, float f2){
    return ((f2 - f1) * Float() + f1);
}
#pragma dont_inline reset

float Rand::Gaussian(){
    float f2, f3, f4, f5;

    if(unk40c){
        unk40c = false;
        return unk408;
    }
    else {
        do {
            do {
                f2 = Float(-1.0f, 1.0f);
                f3 = Float(-1.0f, 1.0f);
                f5 = f2 * f2 + f3 * f3;
            } while(f5 >= 1.0f);
        } while(0 == f5);
        f4 = LogThunk(f5);
        f5 = SqrtThunk((-2.0f * f4) / f5);
        unk408 = f2 * f5;
        unk40c = true;
        return f3 * f5;
    }
}
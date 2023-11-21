#include "rand.hpp"
#include "random.hpp"

extern unsigned int gMainThreadID;
extern "C" unsigned int OSGetCurrentThread();
extern Rand gRand;

bool MainThread(){
    bool ret = true;
    if((gMainThreadID != 0) && (gMainThreadID != OSGetCurrentThread())) ret = false;
    return ret;
}

void SeedRand(int seed){
    gRand.Seed(seed);
}

void RandomInt(){
    MainThread();
    gRand.Int();
}

void RandomInt(int i1, int i2){
    MainThread();
    gRand.Int(i1, i2);
}

void RandomFloat(){
    MainThread();
    gRand.Float();
}

void RandomFloat(float f1, float f2){
    MainThread();
    gRand.Float(f1, f2);
}
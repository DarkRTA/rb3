#include "platform.hpp"
#include "randomnumbergenerator.hpp"
#include "highresolutionclock.hpp"
#include "common.hpp"

const char* Unused(){
    return "Insufficient Memory";
}

#pragma dont_inline on
Quazal::Platform::Platform(){
    _Instance = this;
    HighResolutionClock clock;
    clock.GetTime();
    SetRandomNumberSeed((unsigned long long)clock);
}

Quazal::Platform::~Platform(){ }
#pragma dont_inline reset

void Quazal::Platform::CreateInstance(){
    _Instance = new ("Platform.cpp", 0x89) Platform();
}

void Quazal::Platform::DeleteInstance(){
    delete _Instance;
}

void Quazal::Platform::SetRandomNumberSeed(unsigned int ui){
    s_oRNG.SetRandomNumberSeed(ui);
}

unsigned int Quazal::Platform::GetRandomNumber(unsigned int ui){
    s_oRNG.GetRandomNumber(ui);
}

float Quazal::Platform::GetRealRandomNumber(float f){
    s_oRNG.GetRealRandomNumber(f);
}

#pragma force_active on
void Quazal::Platform::Breakpoint(){ }
#pragma force_active reset

extern "C" void OSSleepTicks(int, int);
extern "C" void OSYieldThread();

void Quazal::Platform::Sleep(unsigned int ui){

}
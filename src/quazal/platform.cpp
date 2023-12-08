#include "platform.hpp"
#include "randomnumbergenerator.hpp"

Quazal::Platform::Platform(){

}

Quazal::Platform::~Platform(){

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
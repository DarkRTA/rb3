#include "randomnumbergenerator.hpp"

Quazal::RandomNumberGenerator::RandomNumberGenerator(){
    unk_9c4 = 0;
    unk_9c8 = 0x9908B0DF;
    unk_9c0 = 0x271;
    SetRandomNumberSeed(1);
}

Quazal::RandomNumberGenerator::~RandomNumberGenerator(){ }


void Quazal::RandomNumberGenerator::SetRandomNumberSeed(unsigned int ui){
    unk_arr[0] = ui;
    unk_9c0 = 1;
    for(int i = 0; unk_9c0 < 0x270; i++){
        unk_arr[unk_9c0] = unk_arr[unk_9c0 - 1] * 0x10DCD;
        unk_9c0++;
    }
}

unsigned int Quazal::RandomNumberGenerator::GetRandomNumber(unsigned int ui){

}

float Quazal::RandomNumberGenerator::GetRealRandomNumber(float f){

}
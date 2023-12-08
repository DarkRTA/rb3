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
    unsigned int i;
    if(0x270 <= unk_9c0){
        if(unk_9c0 == 0x271) SetRandomNumberSeed(0x1105);

        for(i = 0; i < 0xE3; i++){
            unsigned int tmp = (unk_arr[i] & 0x80000000) | (unk_arr[i + 1] & 0x7FFFFFFF & ~0x80000000);
            unk_arr[i] = tmp ^ unk_arr[i + 0x18D] ^ (unk_arr[unk_arr[i + 1] & 1]);
        }

        for(; i < 0x26F; i++){
            unsigned int tmp = (unk_arr[i] & 0x80000000) | (unk_arr[i + 1] & 0x7FFFFFFF & ~0x80000000);
            unk_arr[i] = tmp ^ unk_arr[i - 0xE3] ^ (unk_arr[unk_arr[i + 1] & 1]);
        }
        
        unk_arr[0x26F] = unk_arr[0x18C] ^ 
                (unk_arr[0] & 0x7FFFFFFF) | 
                (unk_arr[0x26F] & 0x80000000 >> 1) ^ 
                unk_arr[(unk_arr[i + 1] & 1) + 0x9C4];
        unk_9c0 = 0;
    }
    int tmp = unk_9c0++;
    i = unk_arr[tmp] ^ (unk_arr[tmp] >> 0xB);
    i = i ^ ((i << 7) & 0x9D2C5680);
    i = i ^ ((i << 0xF) & 0xEFC60000);
    i = i ^ i >> 0x12;
    return i % ui;
}

float Quazal::RandomNumberGenerator::GetRealRandomNumber(float f){
    return (GetRandomNumber(0x10000) / 65536.0f * f);
}
#include "adsr.hpp"

Ps2ADSR::Ps2ADSR() : ADmask(0x8F1F), unk2(0x3C7) {
    
}

void Ps2ADSR::SetAttackMode(AttackMode mode){
    ADmask = (ADmask & 0xFFFF7FFF) | (mode << 0xF);
}

void Ps2ADSR::SetAttackRate(unsigned int ui){
    ADmask = (ADmask & 0xFFFF80FF) | (ui << 8);
}

void Ps2ADSR::SetDecayRate(unsigned int ui){
    ADmask = (ADmask & 0xFFFFFF0F) | (ui << 4);
}

void Ps2ADSR::SetSustainMode(SustainMode mode){
    unk2 = (unk2 & 0xFFFF1FFF) | (mode << 0xD);
}

void Ps2ADSR::SetSustainRate(unsigned int ui){
    unk2 = (unk2 & 0xFFFFE03F) | (ui << 6);
}

void Ps2ADSR::SetSustainLevel(unsigned int ui){
    ADmask = (ADmask & 0xFFFFFFF0) | ui;
}
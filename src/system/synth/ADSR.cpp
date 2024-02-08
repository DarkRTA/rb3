#include "ADSR.h"

const float gDecayRate[16] = {
    0.00007f, 0.00018f, 0.00039f, 0.00081f, 0.0016f, 0.0033f, 0.00669999989f, 0.013f,
    0.027f, 0.052999999f, 0.11f, 0.20999999f, 0.43f, 0.86f, 1.7f, 3.4f
};

const float gSustainLevel[16] = {
    0.0625f, 0.125f, 0.1875f, 0.25f, 0.3125f, 0.375f, 0.4375f, 0.5f,
    0.5625f, 0.625f, 0.6875f, 0.75f, 0.8125f, 0.875f, 0.9375f, 1.0f
};

const float gReleaseRateLin[32] = {
    0.000039999999f, 0.00009f, 0.00018f, 0.00036f, 0.00073f, 0.0015f, 0.0029f, 0.0057999999f,
    0.012f, 0.023f, 0.046f, 0.093f, 0.19f, 0.37f, 0.74f, 1.5f,
    3.0f, 5.9f, 12.0f, 24.0f, 48.0f, 95.0f, 190.0f, 380.0f,
    760.0f, 1520.0f, 3040.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f
};

const float gReleaseRateExp[32] = {
    0.00007f, 0.00018f, 0.00039f, 0.00081f, 0.0016f, 0.0033f, 0.0066999998f, 0.013f,
    0.027f, 0.052999999f, 0.11f, 0.20999999f, 0.43f, 0.86f, 1.7f, 3.4f,
    6.8f, 14.0f, 27.0f, 55.0f, 109.0f, 219.0f, 438.0f, 876.0f,
    1752.0f, 3504.0f, 7008.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f
};

// TODO: fill these out going off the elf
const float gLinInc[128] = { 1 };
const float gLinDec[128] = { 1 };
const float gExpInc[248] = { 1 };
const float gExpDec[86] = { 1 };

Ps2ADSR::Ps2ADSR() : mReg1(0x8F1F), mReg2(0x3C7) {
    
}

void Ps2ADSR::SetAttackMode(AttackMode mode){
    mReg1 = (mReg1 & 0xFFFF7FFF) | (mode << 0xF);
}

void Ps2ADSR::SetAttackRate(unsigned int ui){
    mReg1 = (mReg1 & 0xFFFF80FF) | (ui << 8);
}

void Ps2ADSR::SetDecayRate(unsigned int ui){
    mReg1 = (mReg1 & 0xFFFFFF0F) | (ui << 4);
}

void Ps2ADSR::SetSustainMode(SustainMode mode){
    mReg2 = (mReg2 & 0xFFFF1FFF) | (mode << 0xD);
}

void Ps2ADSR::SetSustainRate(unsigned int ui){
    mReg2 = (mReg2 & 0xFFFFE03F) | (ui << 6);
}

void Ps2ADSR::SetSustainLevel(unsigned int ui){
    mReg1 = (mReg1 & 0xFFFFFFF0) | ui;
}

void Ps2ADSR::SetReleaseMode(ReleaseMode mode){
    mReg2 = (mReg2 & 0xFFFFFFDF) | (mode << 5);
}

void Ps2ADSR::SetReleaseRate(unsigned int ui){
    mReg2 = (mReg2 & 0xFFFFFFE0) | ui;
}

AttackMode Ps2ADSR::GetAttackMode() const {
    return (AttackMode)((mReg1 >> 0xF) & 1);
}

SustainMode Ps2ADSR::GetSustainMode() const {
    return (SustainMode)((mReg2 >> 0xD) & 7);
}

ReleaseMode Ps2ADSR::GetReleaseMode() const {
    return (ReleaseMode)((mReg2 >> 5) & 1);
}

int FindNearestInTable(const float*, int, float);

int Ps2ADSR::NearestAttackRate(float f) const {
    const float* table;
    if(GetAttackMode() == kAttackLinear){
        table = gLinInc;
    }
    else table = gExpInc;
    return FindNearestInTable(table, 0x80, f);
}

int Ps2ADSR::NearestDecayRate(float f) const {
    return FindNearestInTable(gDecayRate, 0x10, f);
}

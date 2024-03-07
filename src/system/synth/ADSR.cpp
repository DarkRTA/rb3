#include "synth/ADSR.h"
#include "os/Debug.h"
#include <algorithm>

#define kMaxAttackRate 0x7f
#define kMaxDecayRate 0xf
#define kMaxSustainRate 0x7f
#define kMaxSustainLevel 0xf
#define kMaxReleaseRate 0x20

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
const float gExpInc[128] = { 1 };
const float gExpDec[128] = { 1 };

Ps2ADSR::Ps2ADSR() : mReg1(0x8F1F), mReg2(0x3C7) {

}

void Ps2ADSR::SetAttackMode(AttackMode mode){
    mReg1 = (mReg1 & 0xFFFF7FFF) | (mode << 0xF);
}

void Ps2ADSR::SetAttackRate(unsigned int rate){
    MILO_ASSERT(rate <= kMaxAttackRate, 71);
    mReg1 = (mReg1 & 0xFFFF80FF) | (rate << 8);
}

void Ps2ADSR::SetDecayRate(unsigned int rate){
    MILO_ASSERT(rate <= kMaxDecayRate, 78);
    mReg1 = (mReg1 & 0xFFFFFF0F) | (rate << 4);
}

void Ps2ADSR::SetSustainMode(SustainMode mode){
    mReg2 = (mReg2 & 0xFFFF1FFF) | (mode << 0xD);
}

void Ps2ADSR::SetSustainRate(unsigned int rate){
    MILO_ASSERT(rate <= kMaxSustainRate, 91);
    mReg2 = (mReg2 & 0xFFFFE03F) | (rate << 6);
}

void Ps2ADSR::SetSustainLevel(unsigned int level){
    MILO_ASSERT(level <= kMaxSustainLevel, 98);
    mReg1 = (mReg1 & 0xFFFFFFF0) | level;
}

void Ps2ADSR::SetReleaseMode(ReleaseMode mode){
    mReg2 = (mReg2 & 0xFFFFFFDF) | (mode << 5);
}

void Ps2ADSR::SetReleaseRate(unsigned int rate){
    MILO_ASSERT(rate <= kMaxReleaseRate, 111);
    mReg2 = (mReg2 & 0xFFFFFFE0) | rate;
}

inline Ps2ADSR::AttackMode Ps2ADSR::GetAttackMode() const {
    return (AttackMode)((mReg1 >> 0xF) & 1);
}

inline Ps2ADSR::SustainMode Ps2ADSR::GetSustainMode() const {
    return (SustainMode)((mReg2 >> 0xD) & 7);
}

inline Ps2ADSR::ReleaseMode Ps2ADSR::GetReleaseMode() const {
    return (ReleaseMode)((mReg2 >> 5) & 1);
}

static int FindNearestInTable(const float* table, int tableSize, float val) {
    MILO_ASSERT(val >= 0.0f, 139);

    const float* end;
    for(end = &table[tableSize]; table[-1] <= 0.0f; end--);
    const float* lbound = std::lower_bound(table, end, val);
    if(lbound == table) return 0;
    else if(lbound == end){

    }
    else {

    }
}

// int FindNearestInTable(float *param_1,int param_2,float param_3)

// {
//   uint uVar1;
//   char *pcVar2;
//   float *pfVar3;
//   int iVar4;
//   float *pfVar5;
//   float local_18;
//   undefined local_14 [12];
  
//   local_18 = param_3;
//   if (param_3 < 0.0) {
//     pcVar2 = MakeString(kAssertStr,&@stringBase0,0x108,s_val_>=_0.0f_80c2c7d3);
//     Debug::Fail((Debug *)TheDebug,pcVar2);
//   }
//   for (pfVar5 = param_1 + param_2; pfVar5[-1] <= 0.0; pfVar5 = pfVar5 + -1) {
//   }
//   local_14[0] = 0;
//   pfVar3 = (float *)__lower_bound<>__11stlpmtx_stdF PC f PC f RC f Q211stlpmtx_std13__less_2<f,f>Pl_PCf
//                               (param_1,pfVar5,&local_18,local_14,0);
//   if (pfVar3 == param_1) {
//     iVar4 = 0;
//   }
//   else if ((pfVar3 == pfVar5) || (local_18 - pfVar3[-1] < *pfVar3 - local_18)) {
//     uVar1 = (int)pfVar3 - (int)param_1;
//     iVar4 = ((int)uVar1 >> 2) + (uint)((int)uVar1 < 0 && (uVar1 & 3) != 0) + -1;
//   }
//   else {
//     uVar1 = (int)pfVar3 - (int)param_1;
//     iVar4 = ((int)uVar1 >> 2) + (uint)((int)uVar1 < 0 && (uVar1 & 3) != 0);
//   }
//   return iVar4;
// }

int Ps2ADSR::NearestAttackRate(float f) const {
    const float* table;
    if(GetAttackMode() == kAttackLinear){
        table = gLinInc;
    }
    else table = gExpInc;
    return FindNearestInTable(table, 0x80, f);
}

int Ps2ADSR::NearestSustainRate(float f) const {
    return FindNearestInTable(gDecayRate, 0x10, f);
}

int Ps2ADSR::NearestReleaseRate(float f) const {
    return FindNearestInTable(gDecayRate, 0x10, f);
}

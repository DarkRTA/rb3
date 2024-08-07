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
const float gLinInc[128] = {
    0.000049999999f, 0.000059999998f, 0.00007f, 0.00009f, 0.000099999997f, 0.00012f, 0.00015f, 0.00018f,
    0.00021f, 0.00023999999f, 0.00029f, 0.00036f, 0.00041f, 0.00047999999f, 0.00057999999f, 0.00073f,
    0.00082999998f, 0.00096999999f, 0.0012f, 0.0015f, 0.0017f, 0.0019f, 0.0023f, 0.0029f,
    0.0033f, 0.0038999999f, 0.0046f, 0.0057999999f, 0.0066f, 0.0077f, 0.0093f, 0.012f,
    0.013f, 0.015f, 0.019f, 0.023f, 0.027f, 0.031f, 0.037f, 0.046f,
    0.053f, 0.062f, 0.074f, 0.093f, 0.11f, 0.12f, 0.15f, 0.19f,
    0.21f, 0.25f, 0.30f, 0.37f, 0.42f, 0.50f, 0.59f, 0.74f,
    0.85f, 0.99f, 1.2f, 1.5f, 1.7f, 2.0f, 2.4f, 3.0f,
    3.4f, 4.0f, 4.8f, 5.9f, 6.8f, 7.9f, 9.5f, 12.0f,
    14.0f, 16.0f, 19.0f, 24.0f, 27.0f, 32.0f, 38.0f, 48.0f,
    54.0f, 63.0f, 76.0f, 95.0f, 109.0f, 127.0f, 152.0f, 190.0f,
    218.0f, 254.0f, 304.0f, 380.0f, 436.0f, 508.0f, 608.0f, 760.0f,
    872.0f, 1016.0f, 1216.0f, 1520.0f, 1744.0f, 2032.0f, 2432.0f, 3040.0f,
    3488.0f, 4064.0f, 4864.0f, 6080.0f, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, 0
};

const float gLinDec[128] = {
    0.000039999999f, 0.000049999999f, 0.000059999998f, 0.00007f, 0.00009f, 0.000099999997f, 0.00012f, 0.00015f,
    0.00018f, 0.00021f, 0.00023999999f, 0.00029f, 0.00036f, 0.00041f, 0.00057999999f, 0.00047999999f,
    0.00073f, 0.00082999998f, 0.00096999999f, 0.0012f, 0.0015f, 0.0017f, 0.0019f, 0.0023f,
    0.0029f, 0.0033f, 0.0038999999f, 0.0046f, 0.0057999999f, 0.0066f, 0.0077f, 0.0093f,
    0.012f, 0.013f, 0.015f, 0.019f, 0.023f, 0.027f, 0.031f, 0.037f,
    0.046f, 0.053f, 0.062f, 0.074f, 0.093f, 0.11f, 0.12f, 0.15f,
    0.19f, 0.21f, 0.25f, 0.30f, 0.37f, 0.42f, 0.50f, 0.59f,
    0.74f, 0.85f, 0.99f, 1.2f, 1.5f, 1.7f, 2.0f, 2.4f,
    3.0f, 3.4f, 4.0f, 4.8f, 5.9f, 6.8f, 7.9f, 9.5f,
    12.0f, 14.0f, 16.0f, 19.0f, 24.0f, 27.0f, 32.0f, 38.0f,
    48.0f, 54.0f, 63.0f, 76.0f, 95.0f, 109.0f, 127.0f, 152.0f,
    190.0f, 218.0f, 254.0f, 304.0f, 380.0f, 436.0f, 508.0f, 608.0f,
    760.0f, 872.0f, 1016.0f, 1216.0f, 1520.0f, 1744.0f, 2032.0f, 2432.0f,
    3040.0f, 3488.0f, 4064.0f, 4864.0f, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, 0
};


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

void Ps2ADSR::Set(const ADSR& adsr){
    SetAttackMode(adsr.mAttackMode);
    SetSustainMode(adsr.mSustainMode);
    SetReleaseMode(adsr.mReleaseMode);
    SetAttackRate(NearestAttackRate(adsr.mAttackRate));
    SetDecayRate(FindNearestInTable(gDecayRate, 0x10, adsr.mDecayRate));
    SetSustainRate(NearestSustainRate(adsr.mSustainRate));
    SetReleaseRate(NearestReleaseRate(adsr.mReleaseRate));
    SetSustainLevel(FindNearestInTable(gSustainLevel, 0x10, adsr.mSustainLevel));
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

DECOMP_FORCEACTIVE(ADSR, "ret > 0.0f")

static int FindNearestInTable(const float* table, int tableSize, float val) {
    MILO_ASSERT(val >= 0.0f, 0x108);

    const float* end;
    for(end = &table[tableSize]; end[-1] <= 0.0f; end--);

    const float* lbound = std::lower_bound(table, end, val);
    if(lbound == table) {
        return 0;
    }

    if(lbound == end || (val - lbound[-1]) < (lbound[0] - val)){
        return (lbound - table) - 1;
    }

    return (lbound - table);
}

DECOMP_FORCEACTIVE(ADSR, "( 0) <= (ar) && (ar) <= ( 60.0f)", "( 0) <= (dr) && (dr) <= ( 60.0f)",
    "( 0) <= (sr) && (sr) <= ( 60.0f)", "( 0.0f) <= (sl) && (sl) <= ( 1.0f)", "( 0) <= (rr) && (rr) <= ( 60.0f)", "0")

int Ps2ADSR::NearestAttackRate(float f) const {
    const float* table;
    int size;

    if(GetAttackMode() == kAttackLinear){
        table = gLinInc;
        size = 0x80;
    }
    else {
        table = gExpInc;
        size = 0x80;
    }
    
    return FindNearestInTable(table, size, f);
}

int Ps2ADSR::NearestSustainRate(float f) const {
    const float* table;
    int size;

    SustainMode sus = GetSustainMode();

    if(sus == kSustainLinInc){
        table = gLinInc;
        size = 0x80;
    }
    else if(sus == kSustainExpInc){
        table = gExpInc;
        size = 0x80;
    }
    else if(sus == kSustainExpDec){
        table = gExpDec;
        size = 0x80;
    }
    else {
        table = gLinDec;
        size = 0x80;
    }

    return FindNearestInTable(table, size, f);
}

int Ps2ADSR::NearestReleaseRate(float f) const {
    const float* table;
    int size;
    if(GetReleaseMode() == kReleaseLinear){
        table = gReleaseRateLin;
        size = 0x20;
    }
    else {
        table = gReleaseRateExp;
        size = 0x20;
    }
    return FindNearestInTable(table, size, f);
}

ADSR::ADSR() : mAttackRate(0.001f), mDecayRate(0.0001f), mSustainRate(0.001f), mReleaseRate(0.005f), mSustainLevel(1.0f),
    mAttackMode(Ps2ADSR::kAttackExp), mSustainMode(Ps2ADSR::kSustainLinInc), mReleaseMode(Ps2ADSR::kReleaseLinear), mPacked(), mSynced(0) {

}

float ADSR::GetAttackRate() const { return mAttackRate; }
float ADSR::GetReleaseRate() const { return mReleaseRate; }

void ADSR::Load(BinStream& bs){
    int version;
    bs >> version;
    if(version > 1) MILO_WARN("Can't load new ADSR");
    else {
        bs >> mAttackRate >> mDecayRate >> mSustainRate >> mReleaseRate >> mSustainLevel;
        int ps2enum;
        bs >> ps2enum;
        mAttackMode = (Ps2ADSR::AttackMode)ps2enum;
        bs >> ps2enum;
        mSustainMode = (Ps2ADSR::SustainMode)ps2enum;
        bs >> ps2enum;
        mReleaseMode = (Ps2ADSR::ReleaseMode)ps2enum;
        mSynced = false;
        SyncPacked();
    }
}

void ADSR::SyncPacked(){
    if(!mSynced){
        mPacked.Set(*this);
        mSynced = true;
    }
}

BinStream& operator>>(BinStream& bs, ADSR& adsr){
    adsr.Load(bs);
    return bs;
}

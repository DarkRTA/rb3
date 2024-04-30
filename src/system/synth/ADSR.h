#ifndef SYNTH_ADSR_H
#define SYNTH_ADSR_H
#include "utl/BinStream.h"

class Ps2ADSR {
public:
    enum AttackMode {
        kAttackLinear = 0,
        kAttackExp = 1,
    };
    enum SustainMode {
        kSustainLinInc = 0,
        kSustainLinDec = 2,
        kSustainExpInc = 4,
        kSustainExpDec = 6,
    };
    enum ReleaseMode {
        kReleaseLinear = 0,
        kReleaseExp = 1,
    };

    Ps2ADSR();

    void SetAttackMode(AttackMode);
    void SetAttackRate(unsigned int);

    void SetDecayRate(unsigned int);

    void SetSustainMode(SustainMode);
    void SetSustainRate(unsigned int);
    void SetSustainLevel(unsigned int);

    void SetReleaseMode(ReleaseMode);
    void SetReleaseRate(unsigned int);

    Ps2ADSR::AttackMode GetAttackMode() const;
    Ps2ADSR::SustainMode GetSustainMode() const;
    Ps2ADSR::ReleaseMode GetReleaseMode() const;

    int NearestAttackRate(float) const;
    int NearestSustainRate(float) const;
    int NearestReleaseRate(float) const;

    unsigned short mReg1;
    unsigned short mReg2;
};

class ADSR {
public:
    ADSR();
    float mAttackRate;
    float mDecayRate;
    float mSustainRate;
    float mReleaseRate;
    float mSustainLevel;
    Ps2ADSR::AttackMode mAttackMode;
    Ps2ADSR::SustainMode mSustainMode;
    Ps2ADSR::ReleaseMode mReleaseMode;
    Ps2ADSR mPacked;
    bool mSynced;
};

BinStream& operator>>(BinStream&, ADSR&);

#endif

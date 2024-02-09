#ifndef SYNTH_ADSR_H
#define SYNTH_ADSR_H

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

class Ps2ADSR {
public:
    Ps2ADSR();

    void SetAttackMode(AttackMode);
    void SetAttackRate(unsigned int);

    void SetDecayRate(unsigned int);

    void SetSustainMode(SustainMode);
    void SetSustainRate(unsigned int);
    void SetSustainLevel(unsigned int);

    void SetReleaseMode(ReleaseMode);
    void SetReleaseRate(unsigned int);

    AttackMode GetAttackMode() const;
    SustainMode GetSustainMode() const;
    ReleaseMode GetReleaseMode() const;

    int NearestAttackRate(float) const;
    int NearestDecayRate(float) const;

    unsigned short mReg1;
    unsigned short mReg2;
};

class ADSR {
public:
    float mAttackRate;
    float mDecayRate;
    float mSustainRate;
    float mReleaseRate;
    float mSustainLevel;
    AttackMode mAttackMode;
    SustainMode mSustainMode;
    ReleaseMode mReleaseMode;
    Ps2ADSR mPacked;
    bool mSynced;
};

#endif

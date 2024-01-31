#ifndef RB3_ADSR_HPP
#define RB3_ADSR_HPP

class Ps2ADSR {
public:
    enum AttackMode { LINEAR_INC, EXPONENTIAL_INC };
    enum SustainMode { s1, s2, s3 };
    enum ReleaseMode { r1, r2, r3 }; 

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

    unsigned short ADmask;
    unsigned short SRmask;
};

#endif

#ifndef RB3_ADSR_HPP
#define RB3_ADSR_HPP

class Ps2ADSR {
public:
    enum AttackMode { a1, a2, a3 };
    enum DecayMode { d1, d2, d3 };
    enum SustainMode { s1, s2, s3 };
    enum ReleaseMode { r1, r2, r3 }; 

    Ps2ADSR();

    void SetAttackMode(AttackMode);
    void SetAttackRate(unsigned int);
    
    // unused SetDecayMode method
    void SetDecayRate(unsigned int);

    void SetSustainMode(SustainMode);
    void SetSustainRate(unsigned int);
    void SetSustainLevel(unsigned int);

    unsigned short ADmask;
    unsigned short unk2;
};

#endif

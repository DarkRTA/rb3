#pragma once
#include "utl/BinStream.h"

class ADSR; // forward dec

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

    void Set(const ADSR &);

    unsigned short mReg1;
    unsigned short mReg2;
};

class ADSR {
public:
    ADSR();
    float GetAttackRate() const;
    float GetReleaseRate() const;
    void Load(BinStream &);
    void SyncPacked();

    /** "Duration of attack in seconds" */
    float mAttackRate; // 0x0
    /** "Duration of decay in seconds" */
    float mDecayRate; // 0x4
    /** "Duration of sustain in seconds" */
    float mSustainRate; // 0x8
    /** "Duration of release in seconds" */
    float mReleaseRate; // 0xc
    /** "Level of sustain volume (0-1)" */
    float mSustainLevel; // 0x10
    /** "Attack mode" */
    Ps2ADSR::AttackMode mAttackMode; // 0x14
    /** "Sustain mode" */
    Ps2ADSR::SustainMode mSustainMode; // 0x18
    /** "Release mode" */
    Ps2ADSR::ReleaseMode mReleaseMode; // 0x1c
    Ps2ADSR mPacked; // 0x20
    bool mSynced; // 0x24
};

BinStream &operator>>(BinStream &, ADSR &);

#include "obj/PropSync_p.h"
bool PropSync(ADSR &, DataNode &, DataArray *, int, PropOp);

#ifndef SYNTH_FXSENDWAH_H
#define SYNTH_FXSENDWAH_H
#include "synth/FxSend.h"

class FxSendWah : public FxSend {
public:
    FxSendWah();
    virtual ~FxSendWah(){}
    OBJ_CLASSNAME(FxSendWah);
    OBJ_SET_TYPE(FxSendWah);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void SetAttackSmoothing(float);
    void SetReleaseSmoothing(float);
    void SetAmount(float);
    void SetProximityEffect(float);
    void SetProximityFocus(float);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mResonance;
    float mUpperFreq;
    float mLowerFreq;
    float mLfoFreq;
    float mMagic;
    float mDistAmount;
    bool mAutoWah;
    float mFrequency;
    float mDump;
    bool mTempoSync;
    Symbol mSyncType;
    float mTempo;
    float mBeatFrac;
};

#endif

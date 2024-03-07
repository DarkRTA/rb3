#ifndef SYNTH_FXSENDSYNAPSE_H
#define SYNTH_FXSENDSYNAPSE_H
#include "synth/FxSend.h"

class FxSendSynapse : public FxSend {
public:
    FxSendSynapse();
    virtual ~FxSendSynapse(){}
    OBJ_CLASSNAME(FxSendSynapse);
    OBJ_SET_TYPE(FxSendSynapse);
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

    float mAmount;
    float mProximityEffect;
    float mProximityFocus;
    float mNote1Hz;
    float mNote2Hz;
    float mNote3Hz;
    bool mUnisonTrio;
    float mAttackSmoothing;
    float mReleaseSmoothing;
};

#endif

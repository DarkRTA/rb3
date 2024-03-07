#ifndef SYNTH_FXSENDEQ_H
#define SYNTH_FXSENDEQ_H
#include "synth/FxSend.h"

class FxSendEQ : public FxSend {
public:
    FxSendEQ();
    virtual ~FxSendEQ();
    OBJ_CLASSNAME(FxSendEQ);
    OBJ_SET_TYPE(FxSendEQ);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mHighFreqCutoff;
    float mHighFreqGain;
    float mMidFreqCutoff;
    float mMidFreqBandwidth;
    float mMidFreqGain;
    float mLowFreqCutoff;
    float mLowFreqGain;
    float mLowPassCutoff;
    float mLowPassReso;
    float mHighPassCutoff;
    float mHighPassReso;
};

#endif

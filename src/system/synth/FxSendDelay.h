#ifndef SYNTH_FXSENDDELAY_H
#define SYNTH_FXSENDDELAY_H
#include "synth/FxSend.h"

class FxSendDelay : public FxSend {
public:
    FxSendDelay();
    virtual ~FxSendDelay();
    OBJ_CLASSNAME(FxSendDelay);
    OBJ_SET_TYPE(FxSendDelay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mDelayTime;
    float mGain;
    float mPingPongPct;
    bool mTempoSync;
    Symbol mSyncType;
    float mTempo;
};

#endif

#ifndef SYNTH_FXSENDFLANGER_H
#define SYNTH_FXSENDFLANGER_H
#include "synth/FxSend.h"

class FxSendFlanger : public FxSend {
public:
    FxSendFlanger();
    virtual ~FxSendFlanger(){}
    OBJ_CLASSNAME(FxSendFlanger);
    OBJ_SET_TYPE(FxSendFlanger);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mDelayMs;
    float mRate;
    int mDepthPct;
    int mFeedbackPct;
    int mOffsetPct;
    bool mTempoSync;
    Symbol mSyncType;
    float mTempo;
};

#endif

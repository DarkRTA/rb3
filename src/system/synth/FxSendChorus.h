#ifndef SYNTH_FXSENDCHORUS_H
#define SYNTH_FXSENDCHORUS_H
#include "synth/FxSend.h"

class FxSendChorus : public FxSend {
public:
    FxSendChorus();
    virtual ~FxSendChorus();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(FxSendChorus);
    OBJ_SET_TYPE(FxSendChorus);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mDelayMs;
    float mRate;
    float mDepth;
    int mFeedbackPct;
    int mOffsetPct;
    bool mTempoSync;
    Symbol mSyncType;
    float mTempo;
};

#endif

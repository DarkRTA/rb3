#ifndef SYNTH_FXSENDREVERB_H
#define SYNTH_FXSENDREVERB_H
#include "synth/FxSend.h"

class FxSendReverb : public FxSend {
public:
    FxSendReverb();
    virtual ~FxSendReverb();
    OBJ_CLASSNAME(FxSendReverb);
    OBJ_SET_TYPE(FxSendReverb);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    Symbol mEnvironmentPreset;
    float mPreDelayMs;
    float mHighCut;
    float mLowCut;
    float mRoomSize;
    float mDamping;
    float mDiffusion;
    float mEarlyLate;
};

#endif

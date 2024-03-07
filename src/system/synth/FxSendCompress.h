#ifndef SYNTH_FXSENDCOMPRESS_H
#define SYNTH_FXSENDCOMPRESS_H
#include "synth/FxSend.h"

class FxSendCompress : public FxSend {
public:
    FxSendCompress();
    virtual ~FxSendCompress();
    OBJ_CLASSNAME(FxSendCompress);
    OBJ_SET_TYPE(FxSendCompress);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mThresholdDB;
    float mRatio;
    float mOutputLevel;
    float mAttack;
    float mRelease;
    float mExpRatio;
    float mExpAttack;
    float mExpRelease;
    float mGateThresholdDB;
};

#endif

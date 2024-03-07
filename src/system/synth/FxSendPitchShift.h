#ifndef SYNTH_FXSENDPITCHSHIFT_H
#define SYNTH_FXSENDPITCHSHIFT_H
#include "synth/FxSend.h"

class FxSendPitchShift : public FxSend {
public:
    FxSendPitchShift();
    virtual ~FxSendPitchShift(){}
    OBJ_CLASSNAME(FxSendPitchShift);
    OBJ_SET_TYPE(FxSendPitchShift);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static unsigned short gRev;
    static unsigned short gAltRev;

    float mRatio;
};

#endif

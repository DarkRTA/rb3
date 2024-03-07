#ifndef SYNTH_FXSENDMETEREFFECT_H
#define SYNTH_FXSENDMETEREFFECT_H
#include "synth/FxSend.h"
#include <vector>

class FxSendMeterEffect : public FxSend {
public:
    FxSendMeterEffect();
    virtual ~FxSendMeterEffect(){}
    OBJ_CLASSNAME(FxSendMeterEffect);
    OBJ_SET_TYPE(FxSendMeterEffect);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    float ChannelData(int);

    static unsigned short gRev;
    static unsigned short gAltRev;

    bool mResetPeaks;
    std::vector<float> mChannels;
};

#endif

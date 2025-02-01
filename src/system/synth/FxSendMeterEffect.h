#pragma once
#include "synth/FxSend.h"
#include "utl/Str.h"
#include <vector>

struct MeterEffectChannelData {
    int unk0;
    float unk4;
    int unk8;
    int unkc;
    class String unk10;
};

/** "meter effect" */
class FxSendMeterEffect : public FxSend {
public:
    FxSendMeterEffect();
    virtual ~FxSendMeterEffect() {}
    OBJ_CLASSNAME(FxSendMeterEffect);
    OBJ_SET_TYPE(FxSendMeterEffect);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    float ChannelData(int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendMeterEffect);
    static void Init() { REGISTER_OBJ_FACTORY(FxSendMeterEffect) }

    bool mResetPeaks; // 0x48
    std::vector<MeterEffectChannelData> mChannels; // 0x4c
};

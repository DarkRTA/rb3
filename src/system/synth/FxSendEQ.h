#pragma once
#include "synth/FxSend.h"

/** "An equalizer effect." */
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

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendEQ);
    static void Init(){
        REGISTER_OBJ_FACTORY(FxSendEQ)
    }

    /** "High frequency cutoff, in Hz". Ranges from 0 to 24000. */
    float mHighFreqCutoff; // 0x48
    /** "High frequency gain, in dB". Ranges from -42 to 42. */
    float mHighFreqGain; // 0x4c
    /** "Mid frequency cutoff, in Hz". Ranges from 0 to 24000. */
    float mMidFreqCutoff; // 0x50
    /** "Mid frequency bandwidth, in Hz". Ranges from 0 to 24000. */
    float mMidFreqBandwidth; // 0x54
    /** "Mid frequency gain, in dB". Ranges from -42 to 42. */
    float mMidFreqGain; // 0x58
    /** "Low frequency cutoff, in Hz". Ranges from 0 to 24000. */
    float mLowFreqCutoff; // 0x5c
    /** "Low frequency gain, in dB". Ranges from -42 to 42. */
    float mLowFreqGain; // 0x60
    /** "Low pass filter cutoff, in Hz". Ranges from 20 to 20000. */
    float mLowPassCutoff; // 0x64
    /** "Low pass filter resonance, in dB". Ranges from -25 to 25. */
    float mLowPassReso; // 0x68
    /** "High pass filter cutoff, in Hz". Ranges from 20 to 20000. */
    float mHighPassCutoff; // 0x6c
    /** "High pass filter resonance, in dB". Ranges from -25 to 25. */
    float mHighPassReso; // 0x70
};

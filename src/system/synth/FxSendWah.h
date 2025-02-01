#pragma once
#include "synth/FxSend.h"

/** "wah-wah effect" */
class FxSendWah : public FxSend {
public:
    FxSendWah();
    virtual ~FxSendWah() {}
    OBJ_CLASSNAME(FxSendWah);
    OBJ_SET_TYPE(FxSendWah);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    void SetAttackSmoothing(float);
    void SetReleaseSmoothing(float);
    void SetAmount(float);
    void SetProximityEffect(float);
    void SetProximityFocus(float);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendWah);
    static void Init() { REGISTER_OBJ_FACTORY(FxSendWah) }

    /** "amount of resonance (1-10)" */
    float mResonance; // 0x48
    /** "high frequency peak of resonant filter (Hz)". Ranges from 100 to 10000. */
    float mUpperFreq; // 0x4c
    /** "low frequency peak of resonant filter (Hz)". Ranges from 100 to 10000. */
    float mLowerFreq; // 0x50
    /** "rate of LFO oscillations (Hz)". Ranges from 0.1 to 10. */
    float mLfoFreq; // 0x54
    /** "magic number (0-1)" */
    float mMagic; // 0x58
    /** "Post wah distortion amount". Ranges from 0 to 1. */
    float mDistAmount; // 0x5c
    bool mAutoWah; // 0x60
    float mFrequency; // 0x64
    /** "blah blah". Ranges from 0 to 1. */
    float mDump; // 0x68
    /** "Sync wah to song tempo?" */
    bool mTempoSync; // 0x6c
    /** "Note value of delay". Sync type options: (sixteenth eighth dotted_eighth quarter
     * dotted_quarter half whole) */
    Symbol mSyncType; // 0x70
    /** "Tempo for delay; can be driven by game code". Ranges from 20 to 300. */
    float mTempo; // 0x74
    float mBeatFrac; // 0x78
};

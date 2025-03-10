#pragma once
#include "synth/FxSend.h"

/** "A chorus effect." */
class FxSendChorus : public FxSend {
public:
    FxSendChorus();
    virtual ~FxSendChorus() {}
    OBJ_CLASSNAME(FxSendChorus);
    OBJ_SET_TYPE(FxSendChorus);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendChorus);
    static void Init() { REGISTER_OBJ_FACTORY(FxSendChorus) }

    /** "Maximum delay time in milliseconds". Ranges from 0 to 100. */
    float mDelayMs; // 0x48
    /** "Rate at which pitch is modulated (Hz)". Ranges from 0 to 10. */
    float mRate; // 0x4c
    /** "Depth of pitch modulation, in centitones". Ranges from 0 to 1000. */
    float mDepth; // 0x50
    /** "Percent of output that is fed back to input". Ranges from 0 to 100. */
    int mFeedbackPct; // 0x54
    /** "LFO phase offset between channels (for wider stereo effect)". Ranges from 0 to
     * 100. */
    int mOffsetPct; // 0x58
    /** "Sync modulation to song tempo?" */
    bool mTempoSync; // 0x5c
    /** "Note value to synchronize modulation to". Sync type options: (sixteenth eighth
     * dotted_eighth quarter dotted_quarter half whole) */
    Symbol mSyncType; // 0x60
    /** "Tempo for modulation; can be driven by game code". Ranges from 20 to 300. */
    float mTempo; // 0x64
};

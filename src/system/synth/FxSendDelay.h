#pragma once
#include "synth/FxSend.h"

/** "A delay effect." */
class FxSendDelay : public FxSend {
public:
    FxSendDelay();
    virtual ~FxSendDelay();
    OBJ_CLASSNAME(FxSendDelay);
    OBJ_SET_TYPE(FxSendDelay);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendDelay);
    static void Init(){
        REGISTER_OBJ_FACTORY(FxSendDelay)
    }

    float mDelayTime; // 0x48
    float mGain; // 0x4c
    /** "Depth of ping pong effect (percent)". Ranges from 0 to 100. */
    float mPingPongPct; // 0x50
    /** "Sync delay to song tempo?" */
    bool mTempoSync; // 0x54
    /** "Note value of delay". Sync type options: (sixteenth eighth dotted_eighth quarter dotted_quarter half whole) */
    Symbol mSyncType; // 0x58
    /** "Tempo for delay; can be driven by game code". Ranges from 20 to 300. */
    float mTempo; // 0x5c
};

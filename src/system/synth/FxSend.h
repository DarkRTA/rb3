#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <vector>

enum SendChannels {
    kSendAll = 0,
    kSendCenter = 1,
    kSendStereo = 2,
};

/** "Base class for all sound FX processors" */
class FxSend : public Hmx::Object {
public:
    FxSend();
    virtual ~FxSend();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(FxSend);
    OBJ_SET_TYPE(FxSend);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetNextSend(FxSend*);
    virtual void Recreate(std::vector<FxSend*>&){}
    virtual void RebuildChain();
    virtual void BuildChainVector(std::vector<FxSend*>&);
    virtual bool CanPushParameters(){ return true; }
    virtual void UpdateMix(){}
    virtual void OnParametersChanged(){}

    bool CheckChain(FxSend*, int);
    void SetStage(int);
    void SetChannels(SendChannels);
    /** "Attach microphone to this send, for testing" */
    void TestWithMic();
    void EnableUpdates(bool);
    FxSend* NextSend() const { return mNextSend; }
    int Stage() const { return mStage; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    /** "The next effect in the chain" */
    ObjOwnerPtr<FxSend> mNextSend; // 0x1c
    /** "The relative order that this send is processed compared to other sends." Ranges from 0 to 9. */
    int mStage; // 0x28
    /** "Bypass the effect and stop it from processing" */
    bool mBypass; // 0x2c
    /** "Gain applied to dry signal (dB)". Ranges from -96.0 to 20.0. */
    float mDryGain; // 0x30
    /** "Gain applied to effect output (dB)" Ranges from -96.0 to 20.0. */
    float mWetGain; // 0x34
    /** "Gain applied to effect input (dB)" Ranges from -96.0 to 20.0. */
    float mInputGain; // 0x38
    /** "Reverb send for this effect". Ranges from -96.0 to 20.0. */
    float mReverbMixDb; // 0x3c
    /** "Enable reverb send" */
    bool mReverbEnable; // 0x40
    bool mEnableUpdates; // 0x41
    /** "Which channels the FX applies to" */
    SendChannels mChannels; // 0x44
};

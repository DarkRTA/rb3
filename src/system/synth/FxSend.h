#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include <vector>

enum SendChannels {
    kSendAll = 0,
    kSendCenter = 1,
    kSendStereo = 2,
};

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
    void TestWithMic();
    void EnableUpdates(bool);
    FxSend* NextSend() const { return mNextSend; }
    int Stage() const { return mStage; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjOwnerPtr<FxSend> mNextSend; // 0x1c
    int mStage; // 0x28
    bool mBypass; // 0x2c
    float mDryGain; // 0x30
    float mWetGain; // 0x34
    float mInputGain; // 0x38
    float mReverbMixDb; // 0x3c
    bool mReverbEnable; // 0x40
    bool mEnableUpdates; // 0x41
    SendChannels mChannels; // 0x44
};

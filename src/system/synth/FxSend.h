#ifndef SYNTH_FXSEND_H
#define SYNTH_FXSEND_H
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

    void operator delete(void* v){
        _MemFree(v);
    }

    DECLARE_REVS;

    ObjOwnerPtr<FxSend, class ObjectDir> mNextSend;
    int mStage;
    bool mBypass;
    float mDryGain;
    float mWetGain;
    float mInputGain;
    float mReverbMixDb;
    // one of these bools is mEnableUpdates
    bool mReverbEnable;
    bool mEnableUpdates;
    SendChannels mChannels;
};

#endif

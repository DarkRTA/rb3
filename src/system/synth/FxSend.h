#ifndef SYNTH_FXSEND_H
#define SYNTH_FXSEND_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

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

    void operator delete(void* v){
        _MemFree(v);
    }

    ObjOwnerPtr<FxSend, ObjectDir> mNextSend;
    int mStage;
    bool mBypass;
    float mDryGain;
    float mWetGain;
    float mInputGain;
    float mReverbMixDb;
    bool mEnableUpdates;
    bool unk41;
    SendChannels mChannels;
};

#endif

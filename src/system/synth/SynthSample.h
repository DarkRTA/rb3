#ifndef SYNTH_SYNTHSAMPLE_H
#define SYNTH_SYNTHSAMPLE_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "synth/SampleData.h"
#include "utl/Loader.h"

class SampleInst;

class SynthSample : public Hmx::Object {
public:

    enum SyncType {
        sync0, sync1, sync2, sync3
    };

    SynthSample();
    virtual ~SynthSample();
    OBJ_CLASSNAME(SynthSample);
    OBJ_SET_TYPE(SynthSample);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual SampleInst* NewInst() const { return 0; }
    virtual float LengthMs() const { return 0.0f; }
    virtual void Sync(SyncType);

    static void* SampleAlloc(int, const char*);
    static void SampleFree(void*);
    static void Init();
    NEW_OBJ(SynthSample);

    int GetSampleRate() const;
    SampleData::Format GetFormat() const;
    bool GetIsLooped() const;
    int GetLoopStartSamp() const;
    int GetPlatformSize(Platform);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    FilePath mFile; // 0x1c
    bool mIsLooped; // 0x28
    int mLoopStartSamp; // 0x2c
    int mLoopEndSamp; // 0x30
    SampleData mSampleData; // 0x34
    FileLoader* mFileLoader; // 0x50 - ptr to some class
};

#endif

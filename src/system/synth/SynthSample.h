#ifndef SYNTH_SYNTHSAMPLE_H
#define SYNTH_SYNTHSAMPLE_H
#include "obj/Object.h"
#include "utl/FilePath.h"

class SynthSample : public Hmx::Object {
public:

    enum SyncType {
        a, b, c
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
    virtual int NewInst() const;
    virtual float LengthMs() const;
    virtual void Sync(SyncType);

    FilePath unk1c;
};

#endif

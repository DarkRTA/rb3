#ifndef SYNTH_BINKCLIP_H
#define SYNTH_BINKCLIP_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"

class BinkClip : public Hmx::Object, public SynthPollable {
public:
    BinkClip();
    virtual ~BinkClip();
    OBJ_CLASSNAME(BinkClip);
    OBJ_SET_TYPE(BinkClip);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    FilePath mFilePath;
};

#endif // SYNTH_BINKCLIP_H
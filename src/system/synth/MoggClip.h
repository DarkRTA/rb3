#ifndef SYNTH_MOGGCLIP_H
#define SYNTH_MOGGCLIP_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"

class MoggClip : public Hmx::Object, public SynthPollable {
public:
    MoggClip();
    virtual ~MoggClip();
    OBJ_CLASSNAME(MoggClip);
    OBJ_SET_TYPE(MoggClip);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual const char* GetSoundDisplayName();
    virtual void SynthPoll();

    FilePath mFilePath;
    float unk34;
};

#endif

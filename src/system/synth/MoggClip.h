#ifndef SYNTH_MOGGCLIP_H
#define SYNTH_MOGGCLIP_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "synth/Faders.h"

class Stream;

class MoggClip : public Hmx::Object, public SynthPollable {
public:

    struct PanInfo {
        PanInfo(int, float);
        int unk0;
        float unk4;
    };

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
    float mVolume;
    bool mLoop;
    float unk3c;
    Stream* unk40; // StandardStream*
    float unk44;
    int unk48;
    int unk4c;
    int unk50;
    std::vector<Fader*> vec54;
    std::vector<PanInfo> unk5c;
    Fader* unk64;
    bool unk68;
    bool unk69;
    bool unk6a;
    int mLoopStart; // loop start sample
    int mLoopEnd; // loop end sample
};

#endif

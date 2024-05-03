#ifndef SYNTH_MOGGCLIP_H
#define SYNTH_MOGGCLIP_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "synth/Faders.h"

class StandardStream;
class FileLoader;

class MoggClip : public Hmx::Object, public SynthPollable {
public:

    struct PanInfo {
        PanInfo(int, float);
        int unk0; // channel
        float unk4; // panning
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

    void LoadFile(BinStream*);
    void UnloadData();
    bool EnsureLoaded();
    void Play();
    void Pause(bool);
    void Stop();
    void KillStream();
    void SetVolume(float);
    void SetLoop(bool);
    void SetLoopStart(int);
    void SetLoopEnd(int);
    void SetPan(int, float);
    void UpdateFaders();
    void UpdatePanInfo();
    void SetFile(const char*);
    void SetControllerVolume(float);
    void SetupPanInfo(float, float, bool);

    FilePath mFilePath;
    float mVolume;
    bool mLoop;
    float mControllerVolume;
    StandardStream* mStream;
    float unk44;
    void* unk48;
    int unk4c;
    FileLoader* mFileLoader;
    std::vector<Fader*> mFaders;
    std::vector<PanInfo> mPanInfos;
    Fader* mFader;
    bool unk68;
    bool unk69;
    bool unk6a;
    int mLoopStart;
    int mLoopEnd;
};

#endif

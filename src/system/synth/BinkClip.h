#ifndef SYNTH_BINKCLIP_H
#define SYNTH_BINKCLIP_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "synth/Faders.h"
#include "synth/StandardStream.h"
#include "utl/FilePath.h"

class BinkClip : public Hmx::Object, public SynthPollable {
public:
    struct PanInfo {
        PanInfo(int, float);
        int chan;
        float pan;
    };

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
    virtual void SynthPoll();

    void KillStream();
    void UnloadData();
    void Stop();
    void LoadFile(BinStream*);
    bool EnsureLoaded();
    void Play();
    void Pause(bool);
    void SetLoop(bool);
    void UpdateVolume();
    void UpdateFaders();
    void UpdatePanInfo();
    bool IsStreaming() const;
    void SetFile(const char*);
    void SetVolume(float);
    void AddFader(Fader*);
    void RemoveFader(Fader*);
    void SetPan(int, float);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    FilePath mFile; // 0x28
    float mVolume; // 0x34
    bool mLoop; // 0x38
    bool mPreload; // 0x39
    StandardStream* mStream; // 0x3c
    float mPlaybackVolumeOffset; // 0x40
    void* mData; // 0x44
    int mSize; // 0x48
    FileLoader* mLoader; // 0x4c
    std::vector<Fader*> mFaders; // 0x50
    std::vector<PanInfo> mPanInfo; // 0x58
    Fader* mFadeOutFader; // 0x60
    bool mFadingOut; // 0x64
    bool mUnloadWhenFinishedPlaying; // 0x65
    bool mPlaying; // 0x66
    Loader* mStreamLoader; // 0x68
};

#endif // SYNTH_BINKCLIP_H
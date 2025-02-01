#pragma once
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "synth/Faders.h"

class StandardStream;
class FileLoader;

/** "Allows dynamic playback of Mogg-based audio clips, most notably crowd audio loops."
 */
class MoggClip : public Hmx::Object, public SynthPollable {
public:
    struct PanInfo {
        PanInfo(int, float);
        int channel;
        float panning;
    };

    MoggClip();
    virtual ~MoggClip();
    OBJ_CLASSNAME(MoggClip);
    OBJ_SET_TYPE(MoggClip);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual const char *GetSoundDisplayName();
    virtual void SynthPoll();

    void LoadFile(BinStream *);
    void UnloadData();
    bool EnsureLoaded();
    /** "Play the audio clip." */
    void Play();
    void Pause(bool);
    /** "Stop the audio clip." */
    void Stop();
    void KillStream();
    void SetVolume(float);
    void SetLoop(bool);
    void SetLoopStart(int);
    void SetLoopEnd(int);
    void SetPan(int, float);
    void UpdateFaders();
    void UpdatePanInfo();
    void SetFile(const char *);
    void SetControllerVolume(float);
    void SetupPanInfo(float, float, bool);

    bool HasStream() const { return mStream; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(MoggClip);
    static void Init() { REGISTER_OBJ_FACTORY(MoggClip) }

    /** "The mogg audio file to be played." */
    FilePath mFilePath; // 0x28
    /** "Volume in dB (0 is full volume, -96 is silence)." */
    float mVolume; // 0x34
    /** "If true, this audio clip should loop during playback." */
    bool mLoop; // 0x38
    float mControllerVolume; // 0x3c
    StandardStream *mStream; // 0x40
    float unk44; // 0x44
    void *unk48; // 0x48
    int unk4c; // 0x4c
    FileLoader *mFileLoader; // 0x50
    std::vector<Fader *> mFaders; // 0x54
    std::vector<PanInfo> mPanInfos; // 0x5c
    Fader *mFader; // 0x64
    bool unk68; // 0x68
    bool unk69; // 0x69
    bool unk6a; // 0x6a
    /** "Start of the loop, in samples. Ignored if \qlooped\q is unchecked." */
    int mLoopStart; // 0x6c
    /** "End of the loop, in samples.  Use -1 for the end of the sample." */
    int mLoopEnd; // 0x70
};

#pragma once
#include "obj/Object.h"
#include "synth/Faders.h"
#include "synth/Stream.h"
#include "math/Rand.h"
#include "meta/MetaMusicScene.h"
#include "utl/MemMgr.h"
#include "utl/Loader.h"

class MetaMusicLoader;
typedef void(MetaMusicLoader::*MetaMusicLoaderStateFunc)(void);

class MetaMusicLoader : public Loader {
public:
    MetaMusicLoader(File *f, int & bytes, unsigned char * buf, int size);
    virtual ~MetaMusicLoader() {}
    virtual const char *DebugText() { return "MetaMusicLoader"; }
    virtual bool IsLoaded() const;
    virtual const char *StateName() const { return "MetaMusicLoader"; }
    virtual void PollLoading();

    void DoneLoading();
    void LoadFile();
    void OpenFile();

    File* mFile; // 0x18
    int& mBytesRead; // 0x1c
    unsigned char* mBuf; // 0x20
    int mBufSize; // 0x24
    MetaMusicLoaderStateFunc mState; // 0x28
};

class MetaMusic : public Hmx::Object {
public:
    MetaMusic(const char *);
    virtual ~MetaMusic();
    virtual DataNode Handle(DataArray *, bool);

    int ChooseStartMs() const;
    bool IsFading() const;
    bool IsPlaying() const;
    bool Loaded();
    void Mute();
    void UnloadStreamFx();
    void UnMute();
    void Stop();
    void Start();
    void AddFader(Fader*);
    void SetScene(MetaMusicScene*);
    void LoadStreamFx();
    void Load(const char*, float, bool, bool);
    void Poll();
    void UpdateMix();

    Stream *mStream; // 0x1c
    bool mLoop; // 0x20
    float mFadeTime; // 0x24
    float mVolume; // 0x28
    bool mPlayFromBuffer; // 0x2c
    bool mRndHeap; // 0x2d
    String mFilename; // 0x30
    MemHandle *mBufferH; // 0x3c
    unsigned char *mBuf; // 0x40
    File *mFile; // 0x44
    Symbol mExt; // 0x48
    int mBufSize; // 0x4c
    int mBytesRead; // 0x50
    Fader *mFader; // 0x54
    Fader *mFaderMute; // 0x58
    ObjPtrList<Fader> mExtraFaders; // 0x5c
    MetaMusicLoader *mLoader; // 0x6c
    std::vector<ObjDirPtr<ObjectDir> > unk70; // 0x70
    bool unk78; // 0x78
    DataArray* unk7c; // 0x7c
    DataArray* unk80; // 0x80
    int unk84; // 0x84
    const char *unk88; // 0x88
    bool unk8c; // 0x8c
    std::vector<int> mStartTimes; // 0x90 - basing this off of the ChooseStartMs function
};

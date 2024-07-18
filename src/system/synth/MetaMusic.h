#ifndef SYNTH_METAMUSIC_H
#define SYNTH_METAMUSIC_H
#include "obj/Object.h"
#include "synth/Faders.h"
#include "synth/Stream.h"
#include "utl/MemMgr.h"
#include "utl/Loader.h"

class MetaMusicLoader : public Loader {
public:
    MetaMusicLoader(File*, int&, unsigned char*, int);
    virtual ~MetaMusicLoader(){}
    virtual const char* DebugText(){ return "MetaMusicLoader"; }
    virtual bool IsLoaded() const;
    virtual const char* StateName() const { return "MetaMusicLoader"; }
    virtual void PollLoading();
};

class MetaMusic : public Hmx::Object {
public:
    MetaMusic(const char*);
    virtual ~MetaMusic();
    virtual DataNode Handle(DataArray*, bool);

    void UnloadStreamFx();

    Stream* mStream; // 0x1c
    bool mLoop; // 0x20
    float mFadeTime; // 0x24
    float mVolume; // 0x28
    bool mPlayFromBuffer; // 0x2c
    bool mRndHeap; // 0x2d
    String mFilename; // 0x30
    MemHandle* mBufferH; // 0x3c
    unsigned char* mBuf; // 0x40
    File* mFile; // 0x44
    Symbol mExt; // 0x48
    int mBufSize; // 0x4c
    int mBytesRead; // 0x50
    Fader* mFader; // 0x54
    Fader* mFaderMute; // 0x58
    ObjPtrList<Fader, ObjectDir> mExtraFaders; // 0x5c
    MetaMusicLoader* mLoader; // 0x6c
    std::vector<ObjDirPtr<ObjectDir> > unk70;
    bool unk78;
    int unk7c;
    int unk80;
    int unk84;
    const char* unk88;
    bool unk8c;
    std::vector<int> unk90;
};

#endif
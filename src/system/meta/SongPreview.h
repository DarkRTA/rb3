#ifndef METABAND_SONGPREVIEW_H
#define METABAND_SONGPREVIEW_H
#include "os/ContentMgr.h"
#include "obj/Object.h"
#include "meta/SongMgr.h"
#include "synth/Stream.h"
#include "synth/Faders.h"

class SongPreview : public ContentMgr::Callback, public Hmx::Object {
public:
    enum State {
        kIdle = 0,
        kMountingSong = 1,
        kPreparingSong = 2,
        kDeletingSong = 3,
        kPlayingSong = 4,
        kFadingOutSong = 5,
    };

    SongPreview(const SongMgr&);
    virtual ~SongPreview();
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentFailed(const char*);
    virtual const char* ContentDir(){ return 0; }
    virtual DataNode Handle(DataArray*, bool);

    void Init();
    void Terminate();
    void DetachFader(Fader*);
    void DetachFaders();
    void Start(Symbol);
    void PreparePreview();
    void Poll();
    void PrepareFaders(const SongInfo*);
    void PrepareSong(Symbol);

    DataNode OnStart(DataArray*);
    void SetMusicVol(float);
    void SetCrowdSingVol(float);

    const SongMgr& mSongMgr; // 0x20
    Stream* mStream; // 0x24
    Fader* mFader; // 0x28
    Fader* mMusicFader; // 0x2c
    Fader* mCrowdSingFader; // 0x30
    int unk34; // 0x34
    float mAttenuation; // 0x38
    float mFadeTime; // 0x3c
    bool mRestart; // 0x40
    bool mLoopForever; // 0x41
    State mState; // 0x44
    Symbol mSong; // 0x48
    Symbol mSongContent; // 0x4c
    float mStartMs; // 0x50
    float mEndMs; // 0x54
    float mStartPreviewMs; // 0x58
    float mEndPreviewMs; // 0x5c
    int unk60; // 0x60
    bool unk64; // 0x64
    float mPreviewRequestedMs; // 0x68
    Symbol unk6c; // 0x6c
    bool unk70; // 0x70
    bool unk71; // 0x71
    bool unk72; // 0x72
    bool mSecurePreview; // 0x73
};

#endif
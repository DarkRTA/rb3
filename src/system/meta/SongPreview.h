#ifndef METABAND_SONGPREVIEW_H
#define METABAND_SONGPREVIEW_H
#include "os/ContentMgr.h"
#include "obj/Object.h"
#include "meta/SongMgr.h"
#include "synth/Stream.h"
#include "synth/Faders.h"

class SongPreview : public ContentMgr::Callback, public Hmx::Object {
public:
    SongPreview(const SongMgr&);
    virtual ~SongPreview();
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentFailed(const char*);
    virtual const char* ContentDir(){ return 0; }
    virtual DataNode Handle(DataArray*, bool);

    void Init();
    void Terminate();
    void DetachFaders();
    void Start(Symbol);

    DataNode OnStart(DataArray*);
    void SetMusicVol(float);
    void SetCrowdSingVol(float);

    SongMgr& mSongMgr; // 0x20
    Stream* mStream; // 0x24
    Fader* mFader; // 0x28
    Fader* mMusicFader; // 0x2c
    Fader* mCrowdSingFader; // 0x30
    int unk34;
    float mAttenuation;
    float mFadeTime;
    bool unk40;
    bool mLoopForever;
    int unk44;
    Symbol unk48;
    Symbol unk4c;
    float unk50;
    float unk54;
    float unk58;
    float unk5c;
    int unk60;
    bool unk64;
    float unk68;
    Symbol unk6c;
    bool unk70;
    bool unk71;
    bool unk72;
    bool unk73;
};

#endif
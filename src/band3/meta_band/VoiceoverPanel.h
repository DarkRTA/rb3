#pragma once
#include "os/ContentMgr.h"
#include "synth/BinkClip.h"
#include "synth/Faders.h"
#include "ui/UIPanel.h"

class VoiceoverPanel : public UIPanel, public ContentMgr::Callback {
public:
    VoiceoverPanel();
    OBJ_CLASSNAME(VoiceoverPanel);
    OBJ_SET_TYPE(VoiceoverPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~VoiceoverPanel();
    virtual void Exit();
    virtual void Poll();
    virtual void Unload();
    virtual void PollForLoading();
    virtual const char *ContentDir();
    virtual void ContentMounted(const char *, const char *);
    virtual void ContentFailed(const char *);
    virtual bool ShouldHandleFadeOutOnExit() const;
    virtual bool ShouldFade() { return true; }

    void FadeOutVoiceover();
    void UpdateVoiceoverState();
    void SetVoiceoverFile(const char *, Symbol);
    void SetVoiceoverSymbol(Symbol);
    void PlayVoiceover();
    void SetVolumeOffsetSymbol(Symbol);
    void UpdateVolumeOffset();

    BinkClip *mVoiceOver; // 0x3c
    Fader *mFader; // 0x40
    Symbol mVolumeOffsetSymbol; // 0x44
    bool mWaitingForLoad; // 0x48
    bool mWaitingForMount; // 0x49
    bool mLoadingFailed; // 0x4a
    Symbol mDLCName; // 0x4c
    String mDLCVoiceoverPath; // 0x50
};
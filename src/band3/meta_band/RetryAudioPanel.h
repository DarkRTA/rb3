#pragma once
#include "meta_band/VoiceoverPanel.h"

class RetryAudioPanel : public VoiceoverPanel {
public:
    RetryAudioPanel();
    OBJ_CLASSNAME(RetryAudioPanel);
    OBJ_SET_TYPE(RetryAudioPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RetryAudioPanel();
    virtual void Enter();
    virtual void Load();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual bool ShouldFade() { return false; }

    Symbol RandomVOContextItem();

    bool mFinished; // 0x5c
};
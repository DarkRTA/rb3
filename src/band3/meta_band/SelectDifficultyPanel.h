#pragma once
#include "meta_band/MetaPerformer.h"
#include "os/ContentMgr.h"
#include "ui/UIPanel.h"

class SelectDifficultyPanel : public UIPanel, public ContentMgr::Callback {
public:
    SelectDifficultyPanel();
    OBJ_CLASSNAME(SelectDifficultyPanel);
    OBJ_SET_TYPE(SelectDifficultyPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SelectDifficultyPanel() {}
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual bool IsLoaded() const;
    virtual void PollForLoading();
    virtual void FinishLoad();
    virtual void ContentMounted(const char *, const char *);
    virtual const char *ContentDir() { return nullptr; }

    void PushSongDetailsToScreen(const MetaPerformer *);
    int GetNumSongs() const;
    bool IsBattle() const;

    float mMarqueeRotationMs; // 0x3c
    Timer mMarqueeTimer; // 0x40
    unsigned int mCurrentSongIx; // 0x70
    int unk74; // 0x74
};
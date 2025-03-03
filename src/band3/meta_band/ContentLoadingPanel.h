#pragma once
#include "os/ContentMgr.h"
#include "ui/UILabel.h"
#include "ui/UIPanel.h"
#include "ui/UITrigger.h"

class ContentLoadingPanel : public UIPanel, public ContentMgr::Callback {
public:
    ContentLoadingPanel();
    OBJ_CLASSNAME(ContentLoadingPanel);
    OBJ_SET_TYPE(ContentLoadingPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~ContentLoadingPanel();
    virtual void Poll();
    virtual void FinishLoad();

    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentMountBegun(int);
    virtual void ContentMounted(const char *, const char *);
    virtual void ContentFailed(const char *);
    virtual void ContentDone();
    virtual const char *ContentDir() { return nullptr; }

    void SetBlocking(bool);
    void ShowIfPossible();
    void UpdateMeterValues();

    int unk3c; // 0x3c
    int unk40; // 0x40
    int unk44; // 0x44
    UILabel *mProgressLabel; // 0x48
    UILabel *mMessageLabel; // 0x4c
    UITrigger *mFindingTrig; // 0x50
    UITrigger *mLoadingTrig; // 0x54
};
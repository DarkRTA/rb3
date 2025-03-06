#pragma once
#include "os/ContentMgr.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"

class ContentDeletePanel : public UIPanel, public ContentMgr::Callback {
public:
    ContentDeletePanel();
    OBJ_CLASSNAME(ContentDeletePanel);
    OBJ_SET_TYPE(ContentDeletePanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~ContentDeletePanel() {}
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual const char *ContentDir() { return nullptr; }
    virtual void ContentFailed(const char *);

    void SetupDeletion(int, bool);

    DataNode OnMsg(const UITransitionCompleteMsg &);
    NEW_OBJ(ContentDeletePanel);
    static void Init() { REGISTER_OBJ_FACTORY(ContentDeletePanel); }

    bool unk3c;
    int mContent; // 0x40
    bool unk44;
    bool unk45;
    bool mDeleteFailed; // 0x46
    String mContentNames[2]; // 0x48, 0x54
};
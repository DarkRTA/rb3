#pragma once
#include "meta_band/SaveLoadManager.h"
#include "ui/UIPanel.h"

class SaveLoadStatusPanel : public UIPanel {
public:
    SaveLoadStatusPanel();
    OBJ_CLASSNAME(SaveLoadStatusPanel);
    OBJ_SET_TYPE(SaveLoadStatusPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~SaveLoadStatusPanel();
    virtual void Draw();
    virtual void Unload();
    virtual void FinishLoad();

    void CancelDeactivation();
    void QueueDeactivation();
    void PollDeactivation();

    DataNode OnMsg(const SaveLoadMgrStatusUpdateMsg &);

    bool unk38;
    int unk3c;
    Timer unk40;
    bool unk70;
    bool unk71;
    int unk74;
    Timer unk78;
};
#pragma once
#include "meta/DeJitterPanel.h"

class ClosetPanel : public DeJitterPanel {
public:
    ClosetPanel();
    OBJ_CLASSNAME(ClosetPanel);
    OBJ_SET_TYPE(ClosetPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~ClosetPanel(){}
    virtual void Draw();
    virtual void Enter();
    virtual void Exit();
    virtual bool Exiting() const;
    virtual void Poll();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();

    int unk88;
    int unk8c;
    int unk90;
    int unk94;
};

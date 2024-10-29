#pragma once
#include "ui/UIPanel.h"

class MainHubMessageProvider;

class MainHubPanel : public UIPanel {
public:
    MainHubPanel();
    OBJ_CLASSNAME(MainHubPanel);
    OBJ_SET_TYPE(MainHubPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~MainHubPanel();
    virtual void Enter();
    virtual void Exit();
    virtual void Poll();
    virtual void Unload();
};

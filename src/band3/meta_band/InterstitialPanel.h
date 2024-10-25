#pragma once
#include "meta/DeJitterPanel.h"

class InterstitialPanel : public DeJitterPanel {
public:
    InterstitialPanel();
    OBJ_CLASSNAME(InterstitialPanel);
    OBJ_SET_TYPE(InterstitialPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~InterstitialPanel(){}
    virtual void Draw();
    virtual void Enter();    
    virtual bool Exiting() const;
    virtual void Load();
    virtual void Unload();

    void SetCamshotDone();
    
    bool mCamshotDone; // 0x85
    int unk88; // 0x88
    bool mShowing; // 0x8c
};

class BackdropPanel : public DeJitterPanel {
public:
    BackdropPanel();
    OBJ_CLASSNAME(BackdropPanel);
    OBJ_SET_TYPE(BackdropPanel);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~BackdropPanel(){}
    virtual void Enter();
    virtual void Exit(); 
    virtual bool Exiting() const;

    void SetOutroDone();
    
    bool mOutroDone; // 0x85
};